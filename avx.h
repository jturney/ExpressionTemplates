#if !defined(avx_h)
#define avx_h

#if !defined __AVX__
# error AVX required.
#endif

#include <cstring>
#include <cstdio>  // for printf
#include <immintrin.h>

namespace et {

struct avx {

    enum { vector_size = sizeof(__m256d) / sizeof(double) };
    typedef double value_type;
    __m256d d;

    avx() {}
    avx(__m256d a) : d(a) {}
    avx(value_type a) {
        d = _mm256_set_pd(a, a, a, a);
    }
    avx(value_type (&a)[4]) {
        d = _mm256_loadu_pd(&a[0]);
    }
    avx(value_type a0, value_type a1, value_type a2, value_type a3) {
        d = _mm256_set_pd(a0, a1, a2, a3);
    }
    avx& operator=(value_type a) {
        d = _mm256_set_pd(a, a, a, a);
        return *this;
    }
    avx& operator+=(avx a) {
        d = _mm256_add_pd(d, a.d);
        return *this;
    }
    avx& operator-=(avx a) {
        d = _mm256_sub_pd(d, a.d);
        return *this;
    }

    void print() const {
        double p[vector_size];
        ::memcpy(&p, &d, sizeof(__m256d));
//        _mm256_store_pd(p, d);
        printf("%lf %lf %lf %lf ", p[0], p[1], p[2], p[3]);
    }

//    operator value_type() const {
//        value_type d0[4];
//        _mm256_storeu_pd(&(d0[0]), d);
//        return d0[0];
//    }
};

inline avx operator*(double a, avx b) {
    avx c;
    avx _a(a);
    c.d = _mm256_mul_pd(_a.d, b.d);
    return c;
}

inline avx operator*(avx a, double b) {
    avx c;
    avx _b(b);
    c.d = _mm256_mul_pd(a.d, _b.d);
    return c;
}

inline avx operator*(int a, avx b) {
    if (a == 1)
        return b;
    else {
        avx c;
        avx _a((double)a);
        c.d = _mm256_mul_pd(_a.d, b.d);
        return c;
    }
}

inline avx operator*(avx a, int b) {
    if (b == 1)
        return a;
    else {
        avx c;
        avx _b((double)b);
        c.d = _mm256_mul_pd(a.d, _b.d);
        return c;
    }
}

inline avx operator*(avx a, avx b) {
    avx c;
    c.d = _mm256_mul_pd(a.d, b.d);
    return c;
}

inline avx operator+(avx a, avx b) {
    avx c;
    c.d = _mm256_add_pd(a.d, b.d);
    return c;
}

inline avx operator-(avx a, avx b) {
    avx c;
    c.d = _mm256_sub_pd(a.d, b.d);
    return c;
}

inline avx operator/(avx a, avx b) {
    avx c;
    c.d = _mm256_div_pd(a.d, b.d);
    return c;
}

inline avx sqrt(avx a) {
    return _mm256_sqrt_pd(a.d);
}

#if defined(__FMA__)
inline avx fma_plus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm256_fmadd_pd(a.d, b.d, c.d);
    return d;
}

inline avx fma_minus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm256_fmsub_pd(a.d, b.d, c.d);
    return d;
}
#elif defined(__FMA4__)
inline avx fma_plus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm256_facc_pd(a.d, b.d, c.d);
    return d;
}

inline avx fma_minus(avx a, avx b, avx c) {
    avx d;
    d.d = _mm256_fsub_pd(a.d, b.d, c.d);
    return d;
}
#endif // __FMA__ __FMA4__

}

#endif // avx_h
