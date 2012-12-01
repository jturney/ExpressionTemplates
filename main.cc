#include <cstdio>

// operation tags
struct plus; struct minus;

// expression tree node
template <class L, class OpTag, class R>
struct expression
{
    expression(L const& l, R const& r)
        : l_(l), r_(r)
    {}

    double operator[](size_t index) const {
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
    static double apply(DataType a, DataType b) {
        return a + b;
    }
};

struct minus
{
    template <typename DataType>
    static double apply(DataType a, DataType b) {
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
    tensor<int> x(4), y(4), z(4);

    x[0] = x[1] = x[2] = x[3] = 1.0;
    y[0] = y[1] = y[2] = y[3] = 2.0;

    z = x + y;

    printf("%5s%5s%5s\n", "x", "y", "z");
    for (int i=0; i<4; ++i)
        printf("%5d%5d%5d\n", x[i], y[i], z[i]);

    return 0;
}
