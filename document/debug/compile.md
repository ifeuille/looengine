
1.error C2059 4430
https://social.msdn.microsoft.com/Forums/en-US/0c7b7b85-4064-4bfe-b16e-cd52bfba91fd/error-c2146-c4430-c2059?forum=vcgeneral
头文件包含顺序有问题
.cpp一般先包含自己的.h就没问题了

2.c++ constexpr
需要c++17
LOO_FORCEINLINE int ReadIntScalar (const StaticArray<uint, 4> &data)
{
    const uint	value = ReadUIntScalar< Bits, OffsetBits > (data);

    if constexpr (Bits == 0)
        return 0;
    else
        if constexpr (Bits == 32)
            return int (value);
        else
            return (value >> (Bits - 1)) ? -int (value) : int (value);	// TODO: check
}

改为如下形式，就可以c++11实现了
struct ReadIntScalar
{
    const uint Bits;
    const uint OffsetBits;
    ReadIntScalar (const uint& bits, const uint& offsetBits) :Bits (bits), OffsetBits (offsetBits) {}
    LOO_FORCEINLINE int operator()(const StaticArray<uint, 4> &data)
    {
        const uint	value = ReadUIntScalar(Bits,OffsetBits) (data);

        if (Bits == 0)
            return 0;
        else if (Bits == 32)
            return int (value);
        else
            return (value >> (Bits - 1)) ? -int (value) : int (value);	// TODO: check
    }
};

3.visit，variant引发得编译问题
其一：非标准visit不支持lambda
改为struct operator()实现
其二：error C3849: 类型“const Visitor”的表达式中的函数样式调用会丢失所有 8 个可用运算符重载的 const 和/或 volatile 限定符
原因是nonstd variant visit实现使用了 const VIsitor
改为struct operator() const实现


4.core.dll,exe
vulkandll在exe里initilize和load得，core.dll里访问不到，在core.dll里另外load,initilize一份就ok了
