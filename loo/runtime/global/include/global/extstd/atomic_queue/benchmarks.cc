/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
#include "cpu_base_frequency.h"
#include "atomic_queue_mutex.h"
#include "atomic_queue.h"
#include "moodycamel.h"
#include "barrier.h"

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>

#include <tbb/concurrent_queue.h>
#include <tbb/spin_mutex.h>

#include <algorithm>
#include <stdexcept>
#include <clocale>
#include <cstdint>
#include <cstdlib>
#include <thread>
#include <future>
#include <limits>
#include <vector>

#include <emmintrin.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using std::uint64_t;

using namespace ::atomic_queue;

template<class T>
using Type = std::common_type<T>; // Similar to boost::type<>.

namespace {

using sum_t = long long;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double const CPU_FREQ = cpu_base_frequency();

template<class T>
inline double to_seconds(T tsc) {
    return tsc / CPU_FREQ * 1e-9;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Queue>
struct BoostSpScAdapter : Queue {
    using T = typename Queue::value_type;

    void push(T element) {
        while(!this->Queue::push(element))
            _mm_pause();
    }

    T pop() {
        T element;
        while(!this->Queue::pop(element))
            _mm_pause();
        return element;
    }
};

template<class Queue>
struct BoostQueueAdapter : BoostSpScAdapter<Queue> {
    using T = typename Queue::value_type;

    void push(T element) {
        while(!this->Queue::bounded_push(element))
            _mm_pause();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Queue, size_t Capacity>
struct TbbAdapter : RetryDecorator<Queue> {
    TbbAdapter() {
        this->set_capacity(Capacity);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Queue, size_t Capacity>
struct CapacityToConstructor : Queue {
    CapacityToConstructor()
        : Queue(Capacity)
    {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Queue>
void throughput_producer(unsigned N, Queue* queue, std::atomic<uint64_t>* t0, Barrier* barrier) {
    barrier->wait();
    // The first producer saves the start time.
    uint64_t expected = 0;
    t0->compare_exchange_strong(expected, __builtin_ia32_rdtsc(), std::memory_order_acq_rel, std::memory_order_relaxed);

    for(unsigned n = 1, stop = N + 1; n <= stop; ++n)
        queue->push(n);
}

template<class Queue>
void throughput_consumer_impl(unsigned N, Queue* queue, sum_t* consumer_sum, std::atomic<unsigned>* last_consumer, uint64_t* t1) {
    unsigned const stop = N + 1;
    sum_t sum = 0;

    for(;;) {
        unsigned n = queue->pop();
        if(n == stop)
            break;
        sum += n;
    }

    // The last consumer saves the end time.
    auto t = __builtin_ia32_rdtsc();
    if(1 == last_consumer->fetch_sub(1, std::memory_order_acq_rel))
        *t1 = t;

    *consumer_sum = sum;
}

template<class Queue>
void throughput_consumer(unsigned N, Queue* queue, sum_t* consumer_sum, std::atomic<unsigned>* last_consumer, uint64_t* t1, Barrier* barrier) {
    barrier->wait();
    throughput_consumer_impl(N, queue, consumer_sum, last_consumer, t1);
}

template<class Queue>
uint64_t benchmark_throughput(unsigned N, unsigned thread_count, bool alternative_placement, sum_t* consumer_sums) {
    Queue queue;
    std::atomic<uint64_t> t0{0};
    uint64_t t1 = 0;
    std::atomic<unsigned> last_consumer{thread_count};

    Barrier barrier;
    std::vector<std::thread> threads(thread_count * 2 - 1);
    if(alternative_placement) {
        for(unsigned i = 0; i < thread_count; ++i) {
            threads[i] = std::thread(throughput_producer<Queue>, N, &queue, &t0, &barrier);
            if(i != thread_count - 1) // This thread is the last consumer.
                threads[thread_count + i] = std::thread(throughput_consumer<Queue>, N, &queue, consumer_sums + i, &last_consumer, &t1, &barrier);
        }
    }
    else {
        for(unsigned i = 0; i < thread_count; ++i)
            threads[i] = std::thread(throughput_producer<Queue>, N, &queue, &t0, &barrier);
        for(unsigned i = 0; i < thread_count - 1; ++i) // This thread is the last consumer.
            threads[thread_count + i] = std::thread(throughput_consumer<Queue>, N, &queue, consumer_sums + i, &last_consumer, &t1, &barrier);
    }

    barrier.release(thread_count * 2 - 1);
    throughput_consumer_impl(N, &queue, consumer_sums + (thread_count - 1), &last_consumer, &t1); // Use this thread for the last consumer.

    for(auto& t: threads)
        t.join();

    return t1 - t0.load(std::memory_order_relaxed);
}

template<class Queue>
void run_throughput_benchmark(char const* name, unsigned M, unsigned thread_count_min, unsigned thread_count_max) {
    int constexpr RUNS = 3;
    std::vector<sum_t> consumer_sums(thread_count_max);

    for(bool alternative_placement : {false, true}) {
        for(unsigned threads = thread_count_min; threads <= thread_count_max; ++threads) {
            unsigned const N = M / threads;

            sum_t const expected_sum = (N + 1) / 2. * N;
            double const expected_sum_inv = 1. / expected_sum;

            uint64_t min_time = std::numeric_limits<uint64_t>::max();
            for(unsigned run = RUNS; run--;) {
                uint64_t time = benchmark_throughput<Queue>(N, threads, alternative_placement, consumer_sums.data());
                min_time = std::min(min_time, time);

                // Calculate the checksum.
                sum_t total_sum = 0;
                for(unsigned i = 0; i < threads; ++i) {
                    auto consumer_sum = consumer_sums[i];
                    total_sum += consumer_sum;

                    // Verify that no consumer was starved.
                    auto consumer_sum_frac = consumer_sum * expected_sum_inv;
                    if(consumer_sum_frac < .1)
                        std::fprintf(stderr, "%s: producers: %u: consumer %u received too few messages: %.2lf%% of expected.\n", name, threads, i, consumer_sum_frac);
                }

                // Verify that all messages were received exactly once: no duplicates, no omissions.
                if(auto diff = total_sum - expected_sum * threads)
                    std::fprintf(stderr, "%s: wrong checksum error: producers: %u, expected_sum: %'lld, diff: %'lld.\n", name, threads, expected_sum * threads, diff);
            }

            double min_seconds = to_seconds(min_time);
            unsigned msg_per_sec = N * threads / min_seconds;
            std::printf("%30s,%2u,%c: %'11u msg/sec\n", name, threads, alternative_placement ? 'i' : 's' , msg_per_sec);
        }
    }
}

template<class Queue>
void run_throughput_benchmark(char const* name, Type<Queue>) {
    unsigned const thread_count_max = std::thread::hardware_concurrency() / 2;
    run_throughput_benchmark<Queue>(name, 1000000, 1, thread_count_max);
}

template<class... Args>
void run_throughput_benchmark(char const* name, Type<BoostSpScAdapter<boost::lockfree::spsc_queue<Args...>>>) {
    using Queue = BoostSpScAdapter<boost::lockfree::spsc_queue<Args...>>;
    run_throughput_benchmark<Queue>(name, 1000000, 1, 1); // spsc_queue can only handle 1 producer and 1 consumer.
}

void run_throughput_benchmarks() {
    std::printf("---- Running throughput benchmarks (higher is better) ----\n");

    int constexpr CAPACITY = 65536;

    run_throughput_benchmark("boost::lockfree::spsc_queue", Type<BoostSpScAdapter<boost::lockfree::spsc_queue<unsigned, boost::lockfree::capacity<CAPACITY>>>>{});
    run_throughput_benchmark("boost::lockfree::queue", Type<BoostQueueAdapter<boost::lockfree::queue<unsigned, boost::lockfree::capacity<CAPACITY - 2>>>>{});

    run_throughput_benchmark("pthread_spinlock", Type<RetryDecorator<AtomicQueueSpinlock<unsigned, CAPACITY>>>{});
    // run_throughput_benchmark("FairSpinlock", Type<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, FairSpinlock>>>{});
    // run_throughput_benchmark("UnfairSpinlock", Type<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, UnfairSpinlock>>>{});

    run_throughput_benchmark("moodycamel::ConcurrentQueue", Type<MoodyCamelQueue<unsigned, CAPACITY>>{});

    run_throughput_benchmark("tbb::spin_mutex", Type<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, tbb::spin_mutex>>>{});
    run_throughput_benchmark("tbb::speculative_spin_mutex", Type<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, tbb::speculative_spin_mutex>>>{});
    run_throughput_benchmark("tbb::concurrent_bounded_queue", Type<TbbAdapter<tbb::concurrent_bounded_queue<unsigned>, CAPACITY>>{});

    run_throughput_benchmark("AtomicQueue", Type<RetryDecorator<AtomicQueue<unsigned, CAPACITY>>>{});
    run_throughput_benchmark("AtomicQueueB", Type<RetryDecorator<CapacityToConstructor<AtomicQueueB<unsigned>, CAPACITY>>>{});
    run_throughput_benchmark("OptimistAtomicQueue", Type<AtomicQueue<unsigned, CAPACITY>>{});
    run_throughput_benchmark("OptimistAtomicQueueB", Type<CapacityToConstructor<AtomicQueueB<unsigned>, CAPACITY>>{});

    run_throughput_benchmark("AtomicQueue2", Type<RetryDecorator<AtomicQueue2<unsigned, CAPACITY>>>{});
    run_throughput_benchmark("AtomicQueueB2", Type<RetryDecorator<CapacityToConstructor<AtomicQueueB2<unsigned>, CAPACITY>>>{});
    run_throughput_benchmark("OptimistAtomicQueue2", Type<AtomicQueue2<unsigned, CAPACITY>>{});
    run_throughput_benchmark("OptimistAtomicQueueB2", Type<CapacityToConstructor<AtomicQueueB2<unsigned>, CAPACITY>>{});

    // run_throughput_benchmark<RetryDecorator<AtomicQueueSpinlockHle<unsigned, CAPACITY>>>("SpinlockHle");

    std::printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Queue, bool Sender>
uint64_t ping_pong_thread(Barrier* barrier, Queue* q1, Queue* q2, unsigned N) {
    barrier->wait();

    uint64_t t0 = __builtin_ia32_rdtsc();
    for(unsigned i = 1, j = 0; j < N; ++i) {
        if(Sender) {
            q1->push(i);
            j = q2->pop();
        }
        else {
            j = q1->pop();
            q2->push(i);
        }
    }
    uint64_t t1 = __builtin_ia32_rdtsc();

    return t1 - t0;
}

template<class Queue>
inline std::array<uint64_t, 2> ping_pong_benchmark(unsigned N) {
    Queue q1, q2;
    Barrier barrier;
    auto time1 = std::async(std::launch::async, ping_pong_thread<Queue, false>, &barrier, &q1, &q2, N);
    auto time2 = std::async(std::launch::async, ping_pong_thread<Queue,  true>, &barrier, &q1, &q2, N);
    barrier.release(2);
    return {time1.get(), time2.get()};
}

template<class Queue>
void run_ping_pong_benchmark(char const* name) {
    int constexpr N = 100000;
    int constexpr RUNS = 10;

    // Select the best of RUNS runs.
    std::array<uint64_t, 2> best_times = {std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max()};
    for(unsigned run = RUNS; run--;) {
        auto times = ping_pong_benchmark<Queue>(N);
        if(best_times[0] + best_times[1] > times[0] + times[1])
            best_times = times;
    }

    auto avg_time = (best_times[0] + best_times[1]) / (2 * 1e9 * CPU_FREQ);
    auto round_trip_time = avg_time / N;
    std::printf("%30s: %.9f sec/round-trip\n", name, round_trip_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void run_ping_pong_benchmarks() {
    std::printf("---- Running ping-pong benchmarks (lower is better) ----\n");

    // This benchmarks doesn't require queue capacity greater than 1, however, capacity of 1 elides
    // some instructions completely because of (x % 1) is always 0. Use something greater than 1 to
    // preclude aggressive optimizations.
    constexpr unsigned CAPACITY = 8;

    run_ping_pong_benchmark<BoostSpScAdapter<boost::lockfree::spsc_queue<unsigned, boost::lockfree::capacity<CAPACITY>>>>("boost::lockfree::spsc_queue");
    run_ping_pong_benchmark<BoostQueueAdapter<boost::lockfree::queue<unsigned, boost::lockfree::capacity<CAPACITY>>>>("boost::lockfree::queue");

    run_ping_pong_benchmark<RetryDecorator<AtomicQueueSpinlock<unsigned, CAPACITY>>>("pthread_spinlock");
    // run_ping_pong_benchmark<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, FairSpinlock>>>("FairSpinlock");
    // run_ping_pong_benchmark<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, UnfairSpinlock>>>("UnfairSpinlock");

    run_ping_pong_benchmark<MoodyCamelQueue<unsigned, CAPACITY>>("moodycamel::ConcurrentQueue");

    run_ping_pong_benchmark<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, tbb::spin_mutex>>>("tbb::spin_mutex");
    run_ping_pong_benchmark<RetryDecorator<AtomicQueueMutex<unsigned, CAPACITY, tbb::speculative_spin_mutex>>>("tbb::speculative_spin_mutex");
    run_ping_pong_benchmark<TbbAdapter<tbb::concurrent_bounded_queue<unsigned>, CAPACITY>>("tbb::concurrent_bounded_queue");

    run_ping_pong_benchmark<RetryDecorator<AtomicQueue <unsigned, CAPACITY>>>("AtomicQueue");
    run_ping_pong_benchmark<RetryDecorator<CapacityToConstructor<AtomicQueueB<unsigned>, CAPACITY>>>("AtomicQueueB");
    run_ping_pong_benchmark<AtomicQueue <unsigned, CAPACITY>>("OptimistAtomicQueue");
    run_ping_pong_benchmark<CapacityToConstructor<AtomicQueueB<unsigned>, CAPACITY>>("OptimistAtomicQueueB");
    run_ping_pong_benchmark<RetryDecorator<AtomicQueue2<unsigned, CAPACITY>>>("AtomicQueue2");
    run_ping_pong_benchmark<RetryDecorator<CapacityToConstructor<AtomicQueueB2<unsigned>, CAPACITY>>>("AtomicQueueB2");
    run_ping_pong_benchmark<AtomicQueue2<unsigned, CAPACITY>>("OptimistAtomicQueue2");
    run_ping_pong_benchmark<CapacityToConstructor<AtomicQueueB2<unsigned>, CAPACITY>>("OptimistAtomicQueueB2");

    // run_ping_pong_benchmark<RetryDecorator<AtomicQueueSpinlockHle<unsigned, CAPACITY>>>("SpinlockHle");

    std::printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    std::setlocale(LC_NUMERIC, "");

    run_throughput_benchmarks();
    run_ping_pong_benchmarks();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
