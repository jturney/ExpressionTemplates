#ifndef expr_h
#define expr_h

#include <boost/type_traits/is_same.hpp>

namespace et {

template<typename DataType, typename D1>
struct tensor;

// operation tags
struct plus; struct minus;

// expression tree node
template <class L, class OpTag, class R>
struct expression
{
    static_assert(boost::is_same<L, R>::value, "L and R must be same type.");

    typedef L data_type;
    typedef typename data_type::data_type result_type;

//    typedef typename L::data_type data_type;

    expression(L const& l, R const& r)
        : l_(l), r_(r)
    {}

    result_type operator[](size_t index) const {
        return OpTag::apply(l_[index], r_[index]);
    }

    L const& l_;
    R const& r_;
};

// addition operator
template <typename L, typename R, typename D1>
expression<tensor<L, D1>, plus, tensor<R, D1> > operator+(tensor<L, D1> const& l, tensor<R, D1> const& r)
{
    return expression<tensor<L, D1>, plus, tensor<R, D1> >(l, r);
}

// subtraction operator
template <typename L, typename R, typename D1>
expression<tensor<L, D1>, minus, tensor<R, D1> > operator-(tensor<L, D1> const& l, tensor<R, D1> const& r)
{
    return expression<tensor<L, D1>, minus, tensor<R, D1> >(l, r);
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

//template <typename DataType, typename D1>
//inline tensor<DataType, D1> sqrt(tensor<DataType, D1> const& a) {
//    for ()
//    return _mm256_sqrt_pd(a.d);
//}

}

#endif // expr_h
