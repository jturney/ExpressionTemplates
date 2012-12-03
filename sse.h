#if !defined(sse_h)
#define sse_h

#if !defined __SSE2__
# error SSE2 required.
#endif

#include <cstring>
#include <cstdio>  // for printf
#include <emmintrin.h>

namespace et {

struct sse {

    enum { vector_size = sizeof(__m128d) / sizeof(double) };
    typedef double value_type;
    __m128d d;

    sse() {}
    sse(__m128d a) : d(a) {}
    sse(value_type a) {
        d = _mm_set_pd(a, a);
    }
    sse(value_type (&a)[2]) {
        d = _mm_loadu_pd(&a[0]);
    }
    sse(value_type a0, value_type a1) {
        d = _mm_set_pd(a0, a1);
    }
    sse& operator=(value_type a) {
        d = _mm_set_pd(a, a);
        return *this;
    }
    sse& operator+=(sse a) {
        d = _mm_add_pd(d, a.d);
        return *this;
    }
    sse& operator-=(sse a) {
        d = _mm_sub_pd(d, a.d);
        return *this;
    }

    void print() const {
        alignas(__m128d) double p[vector_size];
        ::memcpy(&p, &d, sizeof(__m128d));
//        _mm256_storeu_pd(&(p[0]), d);
        printf("%lf %lf ", p[0], p[1]);
    }
};

inline sse operator*(double a, sse b) {
    sse c;
    sse _a(a);
    c.d = _mm_mul_pd(_a.d, b.d);
    return c;
}

inline sse operator*(sse a, double b) {
    sse c;
    sse _b(b);
    c.d = _mm_mul_pd(a.d, _b.d);
    return c;
}

inline sse operator*(int a, sse b) {
    if (a == 1)
        return b;
    else {
        sse c;
        sse _a((double)a);
        c.d = _mm_mul_pd(_a.d, b.d);
        return c;
    }
}

inline sse operator*(sse a, int b) {
    if (b == 1)
        return a;
    else {
        sse c;
        sse _b((double)b);
        c.d = _mm_mul_pd(a.d, _b.d);
        return c;
    }
}

inline sse operator*(sse a, sse b) {
    sse c;
    c.d = _mm_mul_pd(a.d, b.d);
    return c;
}

inline sse operator+(sse a, sse b) {
    sse c;
    c.d = _mm_add_pd(a.d, b.d);
    return c;
}

inline sse operator-(sse a, sse b) {
    sse c;
    c.d = _mm_sub_pd(a.d, b.d);
    return c;
}

inline sse operator/(sse a, sse b) {
    sse c;
    c.d = _mm_div_pd(a.d, b.d);
    return c;
}

inline sse sqrt(sse a) {
    return _mm_sqrt_pd(a.d);
}

#if defined(__FMA__)
inline avx fma_plus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm_fmadd_pd(a.d, b.d, c.d);
    return d;
}

inline avx fma_minus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm_fmsub_pd(a.d, b.d, c.d);
    return d;
}
#elif defined(__FMA4__)
inline avx fma_plus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm_facc_pd(a.d, b.d, c.d);
    return d;
}

inline avx fma_minus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm_fsub_pd(a.d, b.d, c.d);
    return d;
}
#endif // __FMA__ __FMA4__

}

#endif // sse_h
