#if !defined(config_h)
#define config_h

// At this time, alignas is only found in GCC 4.8 and Clang 3.0
#if !defined alignas
#   define alignas(x)
#endif

#if defined(__SSE__)
#   include <xmmintrin.h>
#   define ET_SSE_MODE 1
#else
#   define ET_SSE_MODE 0
#endif

#if defined(__SSE2__)
#   include <emmintrin.h>
#   define ET_SSE2_MODE 1
#else
#   define ET_SSE2_MODE 0
#endif

#if defined(__SSE3__)
#   include <pmmintrin.h>
#   define ET_SSE3_MODE 1
#else
#   define ET_SSE3_MODE 0
#endif

#if defined(__SSSE3__)
#   include <tmmintrin.h>
#   define ET_SSSE3_MODE 1
#else
#   define ET_SSSE3_MODE 0
#endif

#if defined(__SSE4_2__) || defined(__SSE4_1__)
#   include <smmintrin.h>
#   define ET_SSE4_MODE 1
#else
#   define ET_SSE4_MODE 0
#endif

#if defined(__AVX__)
#   include <immintrin.h>
#   define ET_AVX_MODE 1
#else
#   define ET_AVX_MODE 0
#endif

#endif // config_h

