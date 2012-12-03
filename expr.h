#ifndef expr_h
#define expr_h

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
namespace et {

template<typename DataType>
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
template <class L, class R>
expression<tensor<L>, plus, tensor<R> > operator+(tensor<L> const& l, tensor<R> const& r)
{
    return expression<tensor<L>, plus, tensor<R> >(l, r);
}

// subtraction operator
template <class L, class R>
expression<tensor<L>, minus, tensor<R> > operator-(tensor<L> const& l, tensor<R> const& r)
{
    return expression<tensor<L>, minus, tensor<R> >(l, r);
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

}

#endif // expr_h
