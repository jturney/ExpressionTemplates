#if !defined is_expression_h
#define is_expression_h

#include <boost/type_traits/is_base_of.hpp>

namespace et {

struct expression;

template<typename T>
struct is_expression
{
    enum { value = boost::is_base_of<expression, T>::value && !boost::is_base_of<T, expression>::value };
};

}
#endif // is_expression_h
