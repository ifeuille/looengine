// Copyright 2018-2019 Martin Moene
//
// type, strong types for C++98 and later.
// For more information see https://github.com/martinmoene/type
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NONSTD_TYPE_HPP_INCLUDED
#define NONSTD_TYPE_HPP_INCLUDED

#define type_MAJOR  0
#define type_MINOR  1
#define type_PATCH  0

#define type_VERSION  type_STRINGIFY(type_MAJOR) "." type_STRINGIFY(type_MINOR) "." type_STRINGIFY(type_PATCH)

#define type_STRINGIFY(  x )  type_STRINGIFY_( x )
#define type_STRINGIFY_( x )  #x

// nonstd type configuration:

// (none)

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   type_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define type_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define type_CPLUSPLUS  __cplusplus
# endif
#endif

#define type_CPP98_OR_GREATER  ( type_CPLUSPLUS >= 199711L )
#define type_CPP11_OR_GREATER  ( type_CPLUSPLUS >= 201103L )
#define type_CPP11_OR_GREATER_ ( type_CPLUSPLUS >= 201103L )
#define type_CPP14_OR_GREATER  ( type_CPLUSPLUS >= 201402L )
#define type_CPP17_OR_GREATER  ( type_CPLUSPLUS >= 201703L )
#define type_CPP20_OR_GREATER  ( type_CPLUSPLUS >= 202000L )

// half-open range [lo..hi):
#define type_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Compiler versions:
//
// MSVC++ 6.0  _MSC_VER == 1200 (Visual Studio 6.0)
// MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio .NET 2002)
// MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio .NET 2003)
// MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
// MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
// MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
// MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
// MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)

#if defined(_MSC_VER ) && !defined(__clang__)
# define type_COMPILER_MSVC_VER      (_MSC_VER )
# define type_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define type_COMPILER_MSVC_VER      0
# define type_COMPILER_MSVC_VERSION  0
#endif

#define type_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined(__clang__)
# define type_COMPILER_CLANG_VERSION  type_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
# define type_COMPILER_CLANG_VERSION    0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define type_COMPILER_GNUC_VERSION  type_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define type_COMPILER_GNUC_VERSION    0
#endif

// Presence of language and library features:

#ifdef _HAS_CPP0X
# define type_HAS_CPP0X  _HAS_CPP0X
#else
# define type_HAS_CPP0X  0
#endif

// Unless defined otherwise below, consider VC14 as C++11 for type:

#if type_COMPILER_MSVC_VER >= 1900
# undef  type_CPP11_OR_GREATER
# define type_CPP11_OR_GREATER  1
#endif

#define type_CPP11_90   (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1500)
#define type_CPP11_100  (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1600)
#define type_CPP11_110  (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1700)
#define type_CPP11_120  (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1800)
#define type_CPP11_140  (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1900)
#define type_CPP11_141  (type_CPP11_OR_GREATER_ || type_COMPILER_MSVC_VER >= 1910)

#define type_CPP14_000  (type_CPP14_OR_GREATER)
#define type_CPP17_000  (type_CPP17_OR_GREATER)

// Presence of C++11 language features:

#define type_HAVE_CONSTEXPR_11          type_CPP11_140
#define type_HAVE_EXPLICIT_CONVERSION   type_CPP11_140
#define type_HAVE_IS_DELETE             type_CPP11_140
#define type_HAVE_NOEXCEPT              type_CPP11_140

// Presence of C++14 language features:

#define type_HAVE_CONSTEXPR_14          type_CPP14_000

// Presence of C++17 language features:

// no flag

// Presence of C++ library features:

#define type_HAVE_STD_HASH              type_CPP11_120

// C++ feature usage:

#if type_HAVE_CONSTEXPR_11
# define type_constexpr  constexpr
#else
# define type_constexpr  /*constexpr*/
#endif

#if type_HAVE_CONSTEXPR_14
# define type_constexpr14  constexpr
#else
# define type_constexpr14  /*constexpr*/
#endif

#if type_HAVE_EXPLICIT_CONVERSION
# define type_explicit  explicit
#else
# define type_explicit  /*explicit*/
#endif

#if type_HAVE_IS_DELETE
# define type_is_delete = delete
#else
# define type_is_delete
#endif

#if type_HAVE_NOEXCEPT
# define type_noexcept  noexcept
#else
# define type_noexcept  /*noexcept*/
#endif

// Additional includes:

#if type_CPP11_OR_GREATER
# include <functional>      // std::hash<>
# include <utility>         // std::move(), std::swap()
# include <type_traits>     // std::is_same<>
#else
# include <algorithm>       // std::swap()
#endif

// Method enabling

#if type_CPP11_OR_GREATER

#define type_REQUIRES_0(...) \
    template< bool B = (__VA_ARGS__), typename std::enable_if<B, int>::type = 0 >

#define type_REQUIRES_T(...) \
    , typename = typename std::enable_if< (__VA_ARGS__), nonstd::types::detail::enabler >::type

#define type_REQUIRES_R(R, ...) \
    typename std::enable_if< (__VA_ARGS__), R>::type

#define type_REQUIRES_A(...) \
    , typename std::enable_if< (__VA_ARGS__), void*>::type = nullptr

#endif

/**
 * define a type's tag: used to prevent locally-defined struct in C++98.
 */
#if ! type_CPP11_OR_GREATER
# define type_DECLARE_TAG( type_type )  struct type_type##_tag;
#else
# define type_DECLARE_TAG( type_type )  /*tag*/
#endif

/**
 * define a default-constructible type.
 */
#define type_DEFINE_TYPE( type_name, type_type, underlying_type ) \
    typedef ::nonstd::type_type<underlying_type, struct type_name##_tag> type_name;

/**
 * define a non-default-constructible type.
 */
#define type_DEFINE_TYPE_ND( type_name, type_type, underlying_type ) \
    typedef ::nonstd::type_type<underlying_type, struct type_name##_tag, ::nonstd::no_default_t> type_name;

/**
 * define a default-constructible sub-type.
 */
#define type_DEFINE_SUBTYPE( sub, super ) \
    struct sub : super { \
        type_constexpr explicit sub(underlying_type const & x = underlying_type() ) : super(x) {} \
    };

/**
 * define a non-default-constructible sub-type.
 */
#define type_DEFINE_SUBTYPE_ND( sub, super ) \
    struct sub : super { \
        type_constexpr explicit sub(underlying_type const & x) : super(x) {} \
    };

/**
 * define a function for given type, non-constexpr.
 */
#define type_DEFINE_FUNCTION( type_type, type_function, function ) \
    inline type_type type_function( type_type const & x )   \
    {   \
        return type_type( function( x.get() ) );    \
    }

/**
 * define a function for given type, constexpr.
 */
#define type_DEFINE_FUNCTION_CE( type_type, type_function, function ) \
    inline type_constexpr14 type_type type_function( type_type const & x )   \
    {   \
        return type_type( function( x.get() ) );    \
    }

/**
 * implementation namespace
 */
namespace nonstd { namespace types {

namespace detail {

#if type_CPP11_OR_GREATER
enum class enabler{};
#endif
}

// EqualityComparable, comparison functions based on operator==() and operator<():

template< typename T, typename U = T > struct is_eq   { friend type_constexpr14 bool operator==( T const & x, U const & y ) { return x.get() == y.get(); } };
template< typename T, typename U = T > struct is_lt   { friend type_constexpr14 bool operator< ( T const & x, U const & y ) { return x.get() <  y.get(); } };

template< typename T, typename U = T > struct is_ne   { friend type_constexpr14 bool operator!=( T const & x, U const & y ) { return ! ( x == y ); } };
template< typename T, typename U = T > struct is_lteq { friend type_constexpr14 bool operator> ( T const & x, U const & y ) { return     y <  x;   } };
template< typename T, typename U = T > struct is_gt   { friend type_constexpr14 bool operator<=( T const & x, U const & y ) { return ! ( y <  x ); } };
template< typename T, typename U = T > struct is_gteq { friend type_constexpr14 bool operator>=( T const & x, U const & y ) { return ! ( x <  y ); } };

// Logical operations:

template< typename R, typename T = R > struct logical_not{ friend type_constexpr14 R operator!( T const & x ) { return R( ! x.get() ); } };

template< typename R, typename T = R, typename U = R > struct logical_and{ friend type_constexpr14 R operator&&( T const & x, U const & y ) { return R( x.get() && y.get() ); } };
template< typename R, typename T = R, typename U = R > struct logical_or { friend type_constexpr14 R operator||( T const & x, U const & y ) { return R( x.get() || y.get() ); } };

// Arithmetic operations based on operator X=():

template< typename R, typename T = R, typename U = R > struct plus       { friend type_constexpr14 R operator+( T x, U const & y ) { return x += y; } };
template< typename R, typename T = R, typename U = R > struct plus2      { friend type_constexpr14 R operator+( T const & x, U y ) { return y += x; } };
template< typename R, typename T = R, typename U = R > struct minus      { friend type_constexpr14 R operator-( T x, U const & y ) { return x -= y; } };
template< typename R, typename T = R, typename U = R > struct multiplies { friend type_constexpr14 R operator*( T x, U const & y ) { return x *= y; } };
template< typename R, typename T = R, typename U = R > struct multiplies2{ friend type_constexpr14 R operator*( T const & x, U y ) { return y *= x; } };
template< typename R, typename T = R, typename U = R > struct divides    { friend type_constexpr14 R operator/( T x, U const & y ) { return x /= y; } };
template< typename R, typename T = R, typename U = R > struct modulus    { friend type_constexpr14 R operator%( T x, U const & y ) { return x %= y; } };

// Bitwise operations based on operator X=():

//template< typename R, typename T = R > struct bit_not{ friend type_constexpr14 R operator~( T const & x ) { return ~x; }; };

template< typename R, typename T = R, typename U = R > struct bit_and { friend type_constexpr14 R operator&( T x, U const & y ) { return x &= y; } };
template< typename R, typename T = R, typename U = R > struct bit_or  { friend type_constexpr14 R operator|( T x, U const & y ) { return x |= y; } };
template< typename R, typename T = R, typename U = R > struct bit_xor { friend type_constexpr14 R operator^( T x, U const & y ) { return x ^= y; } };

template< typename R, typename T = R > struct bit_shl { friend type_constexpr14 R operator<<( T x, int const n ) { return x <<= n; } };
template< typename R, typename T = R > struct bit_shr { friend type_constexpr14 R operator>>( T x, int const n ) { return x >>= n; } };

/**
 * disallow default construction.
 */
struct no_default_t{};

/**
 * data base class.
 */
template< typename T, typename D = T >
struct data
{
    typedef T underlying_type;

    type_constexpr data()
        : value()
    {}

#if  type_CPP11_OR_GREATER
    type_constexpr explicit data( T v )
        : value( std::move(v) )
    {}
#else
    type_constexpr explicit data( T const & v )
        : value( v )
    {}
#endif

#if type_CPP11_OR_GREATER
    type_constexpr14 T        & get() &       { return value; }
    type_constexpr14 T const  & get() const & { return value; }

    type_constexpr14 T       && get() &&       { return std::move(value); }
    type_constexpr14 T const && get() const && { return std::move(value); }
#else
    type_constexpr14 T        & get()       { return value; }
    type_constexpr14 T const  & get() const { return value; }
#endif

    void swap( data & other )
    {
        using std::swap;
        swap( this->value, other.value );
    }

private:
    underlying_type value;
};

/**
 * type, no operators.
 */
template< typename T, typename Tag, typename D = T >
struct type : data<T,D>
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0((
        ! std::is_same<D, no_default_t>::value
    ))
#endif
    type_constexpr type()
        : data<T,D>()
    {}

#if  type_CPP11_OR_GREATER
    type_constexpr explicit type( T v )
        : data<T,D>( std::move(v) )
    {}
#else
    type_constexpr explicit type( T const & v )
        : data<T,D>( v )
    {}
#endif
};

/**
 * boolean.
 */
template< typename Tag, typename D = bool >
struct boolean
    : type < bool,Tag,D >
    , is_eq< boolean<Tag,D> >
    , is_ne< boolean<Tag,D> >
    , logical_not< boolean<Tag,D> >
{
private:
    // explicit boolean operator return type.

    typedef void ( boolean::*bool_type )() const;

    // address of method used as 'boolean',

    void ERROR_this_type_does_not_support_comparisons() const {}

public:
    // default/initializing constructor.

#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr boolean()
        : type<bool,Tag,D>()
    {}

    type_constexpr explicit boolean( bool value )
        : type<bool,Tag,D>( value )
    {}

    // safe conversion to 'boolean';

#if type_HAVE_EXPLICIT_CONVERSION
    type_constexpr explicit operator bool() const
    {
        return this->get();
    }
#else
    type_constexpr operator bool_type() const
    {
        return this->get() ? &boolean::ERROR_this_type_does_not_support_comparisons : 0;
    }
#endif
};

/**
 * logical, ...
 */
template< typename T, typename Tag, typename D = T >
struct logical
    : type< T,Tag,D >
    , logical_not< type<T,Tag,D> >
    , logical_and< type<T,Tag,D> >
    , logical_or < type<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr logical()
        : type<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit logical( T v  )
        : type<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit logical( T const & v  )
        : type<T,Tag,D>( v )
    {}
#endif
};

/**
 * equality, EqualityComparable.
 */
template< typename T, typename Tag, typename D = T >
struct equality
    : type<T,Tag,D>
    , is_eq< equality<T,Tag,D> >
    , is_ne< equality<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr equality()
        : type<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit equality( T v  )
        : type<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit equality( T const & v  )
        : type<T,Tag,D>( v )
    {}
#endif
};

/**
 * bits, EqualityComparable and bitwise operators.
 */
template< typename T, typename Tag, typename D = T >
struct bits
    : equality< T,Tag,D >
//  , bit_not < bits<T,Tag,D> >
    , bit_and < bits<T,Tag,D> >
    , bit_or  < bits<T,Tag,D> >
    , bit_xor < bits<T,Tag,D> >
    , bit_shl < bits<T,Tag,D> >
    , bit_shr < bits<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr bits()
        : equality<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit bits( T v )
        : equality<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit bits( T const & v )
        : equality<T,Tag,D>( v )
    {}
#endif

    type_constexpr14 bits   operator~ () { return bits( static_cast<T>( ~this->get() ) ); }

    type_constexpr14 bits & operator^=( bits const & other ) { this->get() = this->get() ^ other.get(); return *this; }
    type_constexpr14 bits & operator&=( bits const & other ) { this->get() = this->get() & other.get(); return *this; }
    type_constexpr14 bits & operator|=( bits const & other ) { this->get() = this->get() | other.get(); return *this; }

    type_constexpr14 bits & operator<<=( int const n ) { this->get() <<= n; return *this; }
    type_constexpr14 bits & operator>>=( int const n ) { this->get() >>= n; return *this; }
};

/**
 * ordered, LessThanComparable.
 */
template< typename T, typename Tag, typename D = T >
struct ordered
    : equality<T,Tag,D>
    , is_lt   < ordered<T,Tag,D> >
    , is_gt   < ordered<T,Tag,D> >
    , is_lteq < ordered<T,Tag,D> >
    , is_gteq < ordered<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr ordered()
        : equality<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit ordered( T v )
        : equality<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit ordered( T const & v )
        : equality<T,Tag,D>( v )
    {}
#endif
};

/**
 * numeric, LessThanComparable and ...
 */
template< typename T, typename Tag, typename D = T >
struct numeric
    : ordered   < T,Tag,D >
    , plus      < numeric<T,Tag,D> >
    , minus     < numeric<T,Tag,D> >
    , multiplies< numeric<T,Tag,D> >
    , divides   < numeric<T,Tag,D> >
    , modulus   < numeric<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr numeric()
        : ordered<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit numeric( T v )
        : ordered<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit numeric( T const & v )
        : ordered<T,Tag,D>( v )
    {}
#endif

    type_constexpr14 numeric operator+() const { return *this; }
    type_constexpr14 numeric operator-() const { return numeric( -this->get() ); }

    type_constexpr14 numeric & operator++() { return ++this->get(), *this; }
    type_constexpr14 numeric & operator--() { return --this->get(), *this; }

    type_constexpr14 numeric   operator++( int ) { numeric tmp(*this); ++*this; return tmp; }
    type_constexpr14 numeric   operator--( int ) { numeric tmp(*this); --*this; return tmp; }

    type_constexpr14 numeric & operator+=( numeric const & other ) { this->get() += other.get(); return *this; }
    type_constexpr14 numeric & operator-=( numeric const & other ) { this->get() -= other.get(); return *this; }
    type_constexpr14 numeric & operator*=( numeric const & other ) { this->get() *= other.get(); return *this; }
    type_constexpr14 numeric & operator/=( numeric const & other ) { this->get() /= other.get(); return *this; }
    type_constexpr14 numeric & operator%=( numeric const & other ) { this->get() %= other.get(); return *this; }
};

/**
 * quantity, keep dimension.
 */
template< typename T, typename Tag, typename D = T >
struct quantity
    : ordered    < T,Tag,D >
    , plus       < quantity<T,Tag,D> >
    , minus      < quantity<T,Tag,D> >
    , modulus    < quantity<T,Tag,D> >
    , multiplies < quantity<T,Tag,D>,    quantity<T,Tag,D>, T >
    , multiplies2< quantity<T,Tag,D>, T, quantity<T,Tag,D>    >
    , divides    < quantity<T,Tag,D>,    quantity<T,Tag,D>, T >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr quantity()
        : ordered<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit quantity( T v )
        : ordered<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit quantity( T const & v )
        : ordered<T,Tag,D>( v )
    {}
#endif

    type_constexpr14 quantity operator+() const { return *this; }
    type_constexpr14 quantity operator-() const { return quantity( -this->get() ); }

    type_constexpr14 quantity & operator+=( quantity const & other ) { this->get() += other.get(); return *this; }
    type_constexpr14 quantity & operator-=( quantity const & other ) { this->get() -= other.get(); return *this; }

    type_constexpr14 quantity & operator*=( T const & y ) { return this->get() *= y, *this; }
    type_constexpr14 quantity & operator/=( T const & y ) { return this->get() /= y, *this; }

    type_constexpr14 T operator/( quantity const & y ) { return this->get() / y.get(); }
};

/**
 * offset for address calculations.
 *
 * offset + offset  => offset
 * offset - offset  => offset
 */
template< typename T, typename Tag, typename D = T >
struct offset
    : ordered< T,Tag,D >
    , plus   < offset<T,Tag,D> >
    , minus  < offset<T,Tag,D> >
{
#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr offset()
        : ordered<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit offset( T v )
        : ordered<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit offset( T const & v )
        : ordered<T,Tag,D>( v )
    {}
#endif

    type_constexpr14 offset & operator+=( offset const & y ) { this->get() += y.get(); return *this; }
    type_constexpr14 offset & operator-=( offset const & y ) { this->get() -= y.get(); return *this; }
};

/**
 * address
 *
 * address + address => error
 * address - address => offset
 * address + offset  => address
 * address - offset  => address
 *  offset + address => address
 *  offset - address => error
 *  offset + offset  => offset
 *  offset - offset  => offset
 */
template< typename T, typename O, typename Tag, typename D = T >
struct address
    : ordered< T,Tag,D >
    , plus < address<T,O,Tag,D>, address<T,O,Tag,D>, offset <  O,Tag,O> >
    , plus2< address<T,O,Tag,D>, offset <  O,Tag,O>, address<T,O,Tag,D> >
    , minus< address<T,O,Tag,D>, address<T,O,Tag,D>, offset <  O,Tag,O> >
{
    typedef offset<O,Tag,O> offset_type;

#if type_CPP11_OR_GREATER
    type_REQUIRES_0(
        ! std::is_same<D, no_default_t>::value
    )
#endif
    type_constexpr address()
        : ordered<T,Tag,D>()
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit address( T v )
        : ordered<T,Tag,D>( std::move(v) )
    {}
#else
    type_constexpr explicit address( T const & v )
        : ordered<T,Tag,D>( v )
    {}
#endif

    type_constexpr14 address & operator+=( offset_type const & y ) { this->get() += y.get(); return *this; }
    type_constexpr14 address & operator-=( offset_type const & y ) { this->get() -= y.get(); return *this; }

    friend type_constexpr14 offset_type operator-( address const & x, address const & y ) { return offset_type( x.get() - y.get() ); }
};

// swap values.

template < typename T, typename Tag, typename D >
inline type_constexpr14 void swap( type<T,Tag,D> & x, type<T,Tag,D> & y )
{
    x.swap( y );
}

// the underlying value.

#if type_CPP11_OR_GREATER

template< typename T, typename Tag, typename D >
inline type_constexpr14 typename type<T,Tag,D>::underlying_type &&
to_value( type<T,Tag,D> && v )
{
    return std::move( v ).get();
}

#endif

template< typename T, typename Tag, typename D >
inline type_constexpr14 typename type<T,Tag,D>::underlying_type const &
to_value( type<T,Tag,D> const & v )
{
    return v.get();
}

}}  // namespace nonstd::types

#if type_HAVE_STD_HASH

namespace std {

template< typename T, typename Tag, typename D >
struct hash< nonstd::types::type<T,Tag,D> >
{
public:
    std::size_t operator()( nonstd::types::type<T,Tag,D> const & v ) const type_noexcept
    {
        return std::hash<T>()( v.get() );
    }
};

}  // namespace std

namespace nonstd { namespace types {

template< typename T, typename Tag, typename D >
std::size_t make_hash( type<T,Tag,D> const & v ) type_noexcept
{
    return std::hash<type<T,Tag,D>>()( v );
}

}}

#endif // type_HAVE_STD_HASH

// make type available in namespace nonstd:

namespace nonstd {

using types::no_default_t;

using types::type;
using types::bits;
using types::boolean;
using types::logical;
using types::equality; // equal
using types::ordered;
using types::numeric;
using types::quantity;

using types::offset;
using types::address;

using types::swap;
using types::to_value;

#if type_HAVE_STD_HASH
using types::make_hash;
#endif
} // namespace nonstd

// stream output.

#if 0

#include <ostream>

namespace nonstd {

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, type<T,Tag,D> v )
{
    return os << v.get();
}

}  // namespace nonstd::types

#endif

#include <bitset>

namespace loo
{
	using uint = uint32_t;

	using String = std::string;
	template <typename T>	using BasicString = std::basic_string< T >;

	template <typename T>	using Array = std::vector< T >;

	template <typename T>	using UniquePtr = std::unique_ptr< T >;

	template <typename T>	using SharedPtr = std::shared_ptr< T >;
	template <typename T>	using WeakPtr = std::weak_ptr< T >;

	template <typename T>	using Deque = std::deque< T >;

	template <size_t N>		using BitSet = std::bitset< N >;

	template <typename...T>	using Tuple = std::tuple< T... >;


	template <typename T,
		size_t ArraySize>
		using StaticArray = std::array< T, ArraySize >;


	template <typename FirstT,
		typename SecondT>
		using Pair = std::pair< FirstT, SecondT >;


	template <typename T,
		typename Hasher = std::hash<T>>
		using HashSet = std::unordered_set< T, Hasher >;


	template <typename Key,
		typename Value,
		typename Hasher = std::hash<Key>>
		using HashMap = std::unordered_map< Key, Value, Hasher >;


#	ifdef LOO_OPTIMAL_MEMORY_ORDER
	static constexpr std::memory_order	memory_order_acquire = std::memory_order_acquire;
	static constexpr std::memory_order	memory_order_release = std::memory_order_release;
	static constexpr std::memory_order	memory_order_acq_rel = std::memory_order_acq_rel;
	static constexpr std::memory_order	memory_order_relaxed = std::memory_order_relaxed;
#	else
	static constexpr std::memory_order	memory_order_acquire = std::memory_order_seq_cst;
	static constexpr std::memory_order	memory_order_release = std::memory_order_seq_cst;
	static constexpr std::memory_order	memory_order_acq_rel = std::memory_order_seq_cst;
	static constexpr std::memory_order	memory_order_relaxed = std::memory_order_seq_cst;
#	endif	// LOO_OPTIMAL_MEMORY_ORDER


}	// 


#endif // NONSTD_TYPE_HPP_INCLUDED
