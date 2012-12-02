#include <cstdio>

#include "avx.h"

// operation tags
struct plus; struct minus;

// expression tree node
template <class L, class OpTag, class R>
struct expression
{
    typedef typename L::data_type data_type;

    expression(L const& l, R const& r)
        : l_(l), r_(r)
    {}

    data_type operator[](size_t index) const {
        return OpTag::apply(l_[index], r_[index]);
    }

    L const& l_;
    R const& r_;
};

// addition operator
template <class L, class R>
expression<L, plus, R> operator+(L const& l, R const& r)
{
    return expression<L, plus, R>(l, r);
}

// subtraction operator
template <class L, class R>
expression<L, minus, R> operator-(L const& l, R const& r)
{
    return expression<L, minus, R>(l, r);
}

struct plus
{
    template <typename DataType>
    static DataType apply(DataType a, DataType b) {
        return a + b;
    }
};

struct minus
{
    template <typename DataType>
    static DataType apply(DataType a, DataType b) {
        return a - b;
    }
};

template <typename DataType>
struct tensor
{
    typedef DataType data_type;

    tensor(size_t size) : size_(size) {
        data_ = new data_type[size];
    }
    ~tensor() {
        delete[] data_;
    }

    data_type& operator[](size_t i) {
        return data_[i];
    }

    data_type const& operator[](size_t i) const {
        return data_[i];
    }

    template <typename Expr>
    tensor& operator=(Expr const& x) {
        for (size_t i=0; i<size_; ++i) {
            data_[i] = x[i];
        }
        return *this;
    }

    size_t size_;
    data_type* data_;
};

int main(int /*argc*/, char** /*argv*/)
{
    enum { N = 2 };
    avx one(1.0, 2.0, 3.0, 4.0), two(2.0);

    tensor<avx> x(N), y(N), z(N);

    // Calls the operator= on the first avx object which sets all 4 doubles to 1.0, or 2.0
    x[0] = one;
    y[0] = two;
    x[1] = two;
    y[1] = one;

    z = x + y;

    printf("%10s%10s%10s\n", "x", "y", "z");
    avx x0 = x[0], y0 = y[0], ans = z.data_[0];
    for (int i=0; i<4; ++i)
        printf("%10lf%10lf%10lf\n", x0.d[i], y0.d[i], ans.d[i]);
    x0 = x[1]; y0 = y[1]; ans = z.data_[1];
    for (int i=0; i<4; ++i)
        printf("%10lf%10lf%10lf\n", x0.d[i], y0.d[i], ans.d[i]);

    return 0;
}
