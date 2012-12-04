#if !defined(config_h)
#define config_h

// At this time, alignas is only found in GCC 4.8 and Clang 3.0
#if !defined alignas
#   define alignas(x)
#endif

#if defined __SSE2__
#   include <emmintrin.h>
#endif

#if defined __AVX__
#   include <immintrin.h>
#endif

#endif // config_h

