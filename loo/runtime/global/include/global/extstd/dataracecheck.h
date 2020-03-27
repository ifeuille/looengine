
#pragma once
#include "global/global.h"
#include "global/template/hash.h"
#include "global/mutex.h"
#ifdef LOO_ENABLE_DATA_RACE_CHECK

#include <atomic>
#include <mutex>
#include <thread>

namespace loo
{

	//
	// Data Race Check
	//

	struct DataRaceCheck
	{
		// variables
	private:
		mutable std::atomic<size_t>		_state = 0;


		// methods
	public:
		DataRaceCheck () {}

		ND_ bool  Lock () const
		{
			const size_t	id = size_t (HashOf (std::this_thread::get_id ()));
			size_t			curr = _state.load (std::memory_order_acquire);

			if (curr == id)
				return true;	// recursive lock

			curr = 0;
			bool	locked = _state.compare_exchange_strong (curr, id,std::memory_order_relaxed);
			CHECK (curr == 0);		// locked by another thread - race condition detected!
			CHECK (locked);
			return true;
		}

		void  Unlock () const
		{
			_state.store (0, std::memory_order_relaxed);
		}
	};



	//
	// Read/Write Data Race Check
	//

	struct RWDataRaceCheck
	{
		// variables
	private:
		mutable std::recursive_mutex	_lockWrite;
		mutable std::atomic<int>		_readCounter = 0;


		// methods
	public:
		RWDataRaceCheck () {}


		ND_ bool  LockExclusive ()const 
		{
			bool	locked = _lockWrite.try_lock ();
			CHECK (locked);	// locked by another thread - race condition detected!

			int		expected = _readCounter.load (std::memory_order_acquire);
			CHECK (expected <= 0);	// has read lock(s) - race condition detected!

			_readCounter.compare_exchange_strong (expected, expected - 1, std::memory_order_relaxed);
			CHECK (expected <= 0);	// has read lock(s) - race condition detected!
			return true;
		}

		void  UnlockExclusive ()const
		{
			_readCounter.fetch_add (1, std::memory_order_relaxed);
			_lockWrite.unlock ();
		}


		ND_ bool  LockShared () const
		{
			int		expected = 0;
			bool	locked = false;
			do {
				locked = _readCounter.compare_exchange_weak (expected, expected + 1, std::memory_order_relaxed);

				// if has exclusive lock in current thread
				if (expected < 0 and _lockWrite.try_lock ())
				{
					_lockWrite.unlock ();
					return false;	// don't call 'UnlockShared'
				}
				CHECK (expected >= 0);	// has write lock(s) - race condition detected!
			} while (not locked);

			return true;
		}

		void  UnlockShared () const
		{
			_readCounter.fetch_sub (1, std::memory_order_relaxed);
		}
	};

}	// loo

namespace std
{
	template <>
	struct unique_lock< loo::DataRaceCheck >
	{
	private:
		loo::DataRaceCheck &	_lock;
		bool					_locked = false;

	public:
		explicit unique_lock (loo::DataRaceCheck &ref) : _lock{ ref }
		{
			_locked = _lock.Lock ();
		}

		unique_lock (const unique_lock &) = delete;
		unique_lock (unique_lock &&) = delete;

		~unique_lock ()
		{
			if (_locked)
				_lock.Unlock ();
		}
	};

	template <>
	struct unique_lock< const loo::DataRaceCheck > :
		unique_lock< loo::DataRaceCheck >
	{
		explicit unique_lock (const loo::DataRaceCheck &ref) :
			unique_lock< loo::DataRaceCheck >{ const_cast<loo::DataRaceCheck &>(ref) }
		{}
	};


	template <>
	struct unique_lock< loo::RWDataRaceCheck >
	{
	private:
		const loo::RWDataRaceCheck &	_lock;
		bool					_locked = false;

	public:
		explicit unique_lock (const loo::RWDataRaceCheck &ref) : _lock{ ref }
		{
			_locked = _lock.LockExclusive ();
		}

		unique_lock (const unique_lock &) = delete;
		unique_lock (unique_lock &&) = delete;

		~unique_lock ()
		{
			if (_locked)
				_lock.UnlockExclusive ();
		}
	};

	template <>
	struct unique_lock< const loo::RWDataRaceCheck > :
		unique_lock< loo::RWDataRaceCheck >
	{
		explicit unique_lock (const loo::RWDataRaceCheck &ref) :
			unique_lock< loo::RWDataRaceCheck >{ const_cast<loo::RWDataRaceCheck &>(ref) }
		{}
	};


	template <>
	struct shared_lock< loo::RWDataRaceCheck >
	{
	private:
		const loo::RWDataRaceCheck &	_lock;
		bool					_locked = false;

	public:
		explicit shared_lock (const loo::RWDataRaceCheck &ref) : _lock{ ref }
		{
			_locked = _lock.LockShared ();
		}

		shared_lock (const shared_lock &) = delete;
		shared_lock (shared_lock &&) = delete;

		~shared_lock ()
		{
			if (_locked)
				_lock.UnlockShared ();
		}
	};

	template <>
	struct shared_lock< const loo::RWDataRaceCheck > :
		shared_lock< loo::RWDataRaceCheck >
	{
		explicit shared_lock (const loo::RWDataRaceCheck &ref) :
			shared_lock< loo::RWDataRaceCheck >{ const_cast<loo::RWDataRaceCheck &>(ref) }
		{}
	};

}	// std

namespace loo
{

	//
	// Value with Data Race Check
	//

	template <typename T>
	struct DRCValue
	{
		// types
	private:
		struct Pointer
		{
		private:
			DRCValue<T> *	_ptr;

			Pointer (DRCValue<T> *ptr) : _ptr{ ptr } {}
			void _Lock () { if (_ptr) _ptr->_drCheck.LockExclusive (); }
			void _Unlock () { if (_ptr) _ptr->_drCheck.UnlockExclusive (); }

		public:
			Pointer (const Pointer &other) { _ptr = other._ptr;  _Lock (); }
			Pointer (Pointer &&other) { _ptr = other._ptr;  other._ptr = null; }
			~Pointer () { _Unlock (); }

			Pointer&  operator = (const Pointer &rhs) { _Unlock ();  _ptr = rhs._ptr;  _Lock ();  return *this; }
			Pointer&  operator = (Pointer &&rhs) { _Unlock ();  _ptr = rhs._ptr;  rhs._ptr = null;  return *this; }

			ND_ T *	operator -> () { return &_ptr->_value; }
			ND_ T&	operator * () { return _ptr->_value; }
		};


		struct CPointer
		{
		private:
			DRCValue<T> *	_ptr;

			CPointer (DRCValue<T> *ptr) : _ptr{ ptr } {}
			void _Lock () { if (_ptr) _ptr->_drCheck.LockShared (); }
			void _Unlock () { if (_ptr) _ptr->_drCheck.UnlockShared (); }

		public:
			CPointer (const CPointer &other) { _ptr = other._ptr;  _Lock (); }
			CPointer (CPointer &&other) { _ptr = other._ptr;  other._ptr = null; }
			~CPointer () { _Unlock (); }

			CPointer&  operator = (const CPointer &rhs) { _Unlock ();  _ptr = rhs._ptr;  _Lock ();  return *this; }
			CPointer&  operator = (CPointer &&rhs) { _Unlock ();  _ptr = rhs._ptr;  rhs._ptr = null;  return *this; }

			ND_ T const*  operator -> ()	const { return &_ptr->_value; }
			ND_ T const&  operator * ()		const { return _ptr->_value; }
		};


		// variables
	private:
		T					_value;
		RWDataRaceCheck		_drCheck;


		// methods
	public:
		DRCValue () {}
		DRCValue (const T &value) : _value{ value } {}
		DRCValue (T &&value) : _value{ value } {}
		~DRCValue () { EXLOCK (RWDataRaceCheck,_drCheck); }

		DRCValue&  operator = (const T &rhs) { EXLOCK (RWDataRaceCheck, _drCheck);  _value = rhs;  return *this; }
		DRCValue&  operator = (T &&rhs) { EXLOCK (RWDataRaceCheck, _drCheck);  _value = std::move (rhs);  return *this; }

		DRCValue (const DRCValue &) = delete;
		DRCValue (DRCValue &&) = delete;
		DRCValue&  operator = (const DRCValue &) = delete;
		DRCValue&  operator = (DRCValue &&) = delete;

		ND_ Pointer   operator -> () { return Pointer{ this }; }
		ND_ CPointer  operator -> ()		const { return CPointer{ this }; }
	};


}	// loo


#else

namespace loo
{

	//
	// Data Race Check
	//
	struct DataRaceCheck
	{
		void lock () const {}
		void unlock () const {}
	};


	//
	// Read/Write Data Race Check
	//
	struct RWDataRaceCheck
	{
		void lock () const {}
		void unlock () const {}

		void lock_shared () const {}
		void unlock_shared () const {}
	};


	//
	// Value with Data Race Check
	//
	template <typename T>
	struct DRCValue
	{
		T		_value;

		DRCValue () {}
		DRCValue (const T &val) : _value{ val } {}
		DRCValue (T &&val) : _value{ std::move (val) } {}

		ND_ T *			operator -> () { return &_value; }
		ND_ T &			operator *  () { return _value; }
		ND_ T const*	operator -> ()	const { return &_value; }
		ND_ T &			operator *  ()	const { return _value; }
	};


}	// loo

#endif	// LOO_ENABLE_DATA_RACE_CHECK

