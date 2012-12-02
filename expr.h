#ifndef expr_h
#define expr_h

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
namespace et {

// operation tags
struct plus; struct minus;

// expression tree node
template <class L, class OpTag, class R>
struct expression
{
    static_assert(boost::is_same<typename L::data_type, typename R::data_type>::value, "L and R must be same type.");

    typedef typename L::data_type data_type;

//    typedef typename L::data_type data_type;

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

}

#endif // expr_h
