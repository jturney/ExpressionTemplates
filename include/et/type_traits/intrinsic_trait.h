#ifndef intrinsics_traits_h
#define intrinsics_traits_h

#include <boost/type_traits/remove_cv.hpp>
#include <et/config.h>
#include <et/types/sse.h>
#include <et/types/avx.h>
#include <et/type_traits/alignment_trait.h>

namespace et {

namespace detail {

template<size_t N>
struct intrinsic_trait_helper;

template<>
struct intrinsic_trait_helper<1UL>
{
    // SSE type this size will refer to by default
    typedef __m128i type;
    enum { size           = ( ET_SSE2_MODE ) ? 16 : 1 };
};

template<>
struct intrinsic_trait_helper<2UL>
{
    typedef __m128i type;
    enum { size           = ( ET_SSE2_MODE ) ? 8 : 1 };
};

template<>
struct intrinsic_trait_helper<4UL>
{
    typedef __m128i type;
    enum { size           = ( ET_SSE2_MODE ) ? 4 : 1 };
};

template<>
struct intrinsic_trait_helper<8UL>
{
    typedef __m128i type;
    enum { size           = ( ET_SSE2_MODE ) ? 2 : 1 };
};

template<typename T>
struct intrinsic_trait_base
{
    typedef T type;
    enum { size           = 1,
           alignment      = alignment_trait<T>::value };
};

template<>
struct intrinsic_trait_base<short>
{
private:
    typedef intrinsic_trait_helper<sizeof(short)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<short>::value };
};

template<>
struct intrinsic_trait_base<unsigned short>
{
private:
    typedef intrinsic_trait_helper<sizeof(unsigned short)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<unsigned short>::value };
};

template<>
struct intrinsic_trait_base<int>
{
private:
    typedef intrinsic_trait_helper<sizeof(int)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<int>::value };
};

template<>
struct intrinsic_trait_base<unsigned int>
{
private:
    typedef intrinsic_trait_helper<sizeof(unsigned int)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<unsigned int>::value };
};

template<>
struct intrinsic_trait_base<long>
{
private:
    typedef intrinsic_trait_helper<sizeof(long)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<long>::value };
};

template<>
struct intrinsic_trait_base<unsigned long>
{
private:
    typedef intrinsic_trait_helper<sizeof(unsigned long)> helper;

public:
    typedef helper::type type;
    enum { size           = helper::size,
           alignment      = alignment_trait<unsigned long>::value };
};

#if ET_AVX_MODE
template<>
struct intrinsic_trait_base<float>
{
    typedef __m256 type;
    enum { size = (32UL / sizeof(float)),
           alignment = alignment_trait<float>::value };
};
#else
template<>
struct intrinsic_trait_base<float>
{
    typedef __m128 type;
    enum { size = (ET_SSE_MODE) ? ( 16UL  / sizeof(float)) : 1,
           alignment = alignment_trait<float>::value };
};
#endif

#if ET_AVX_MODE
template<>
struct intrinsic_trait_base<double>
{
    typedef __m256d type;
    enum { size = (32UL / sizeof(double)),
           alignment = alignment_trait<double>::value };
};
#else
template<>
struct intrinsic_trait_base<double>
{
    typedef __m128d type;
    enum { size = (16UL / sizeof(double)),
           alignment = alignment_trait<double>::value };
};
#endif

} // namespace et::detail

template<typename T>
struct intrinsic_trait : public detail::intrinsic_trait_base<typename boost::remove_cv<T>::type> {};

} // namespace et

#endif // intrinsics_traits_h
