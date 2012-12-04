#ifndef expr_h
#define expr_h

#include <boost/type_traits/is_same.hpp>

namespace et {

// All expressions derive from this base class.
struct expression
{};

template<typename DataType, typename D1>
struct tensor;

// operation tags
struct plus; struct minus; struct square_root;

// expression tree node
template <class L, class OpTag, class R>
struct expression2 : public expression
{
//    static_assert(boost::is_same<L, R>::value, "L and R must be same type.");

    typedef L data_type;
    typedef typename data_type::data_type result_type;

//    typedef typename L::data_type data_type;

    expression2(L const& l, R const& r)
        : l_(l), r_(r)
    {}

    result_type operator[](size_t index) const {
        return OpTag::apply(l_[index], r_[index]);
    }

    L const& l_;
    R const& r_;
};

template <class L, class OpTag>
struct expression1 : public expression
{
    typedef L data_type;
    typedef typename data_type::data_type result_type;

    expression1(L const& l)
        : l_(l)
    {}

    result_type operator[](size_t index) const {
        return OpTag::apply(l_[index]);
    }

    L const& l_;
};

// addition operator
template <typename L, typename D1>
expression2<tensor<L, D1>, plus, tensor<L, D1> > operator+(tensor<L, D1> const& l, tensor<L, D1> const& r)
{
    return expression2<tensor<L, D1>, plus, tensor<L, D1> >(l, r);
}

template <typename L, typename D1, typename Op1>
expression2<tensor<L, D1>, plus, expression1<tensor<L, D1>, Op1> > operator+(tensor<L, D1> const& l, expression1<tensor<L, D1>, Op1> const& r)
{
    return expression2<tensor<L, D1>, plus, expression1<tensor<L, D1>, Op1> >(l, r);
}

// subtraction operator
template <typename L, typename R, typename D1>
expression2<tensor<L, D1>, minus, tensor<R, D1> > operator-(tensor<L, D1> const& l, tensor<R, D1> const& r)
{
    return expression2<tensor<L, D1>, minus, tensor<R, D1> >(l, r);
}

// square root operator
template <typename L, typename D1>
inline expression1<tensor<L, D1>, square_root> sqrt(tensor<L, D1> const& l) {
    return expression1<tensor<L, D1>, square_root>(l);
}

}

#endif // expr_h
