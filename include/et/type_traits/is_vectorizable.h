#ifndef is_vectorizable_h
#define is_vectorizable_h

#include <boost/type_traits/integral_constant.hpp>
#include <et/type_traits/is_double.h>
#include <et/type_traits/is_float.h>
#include <et/type_traits/is_integer.h>
#include <et/type_traits/is_long.h>
#include <et/type_traits/is_short.h>
#include <et/config.h>
#include <et/if.h>

namespace et {

namespace detail {

template<typename T>
struct is_vectorizable_helper
{
    enum { value = (ET_SSE_MODE  && ( is_float<T>::value || is_double<T>::value )) ||
                   (ET_SSE2_MODE && ( is_short<T>::value || is_int<T>::value || is_long<T>::value ) ) };
    typedef typename if_<value>::template then_<boost::true_type, boost::false_type>::type type;
};

} // namespace detail

template<typename T>
struct is_vectorizable : public detail::is_vectorizable_helper<T>::type { };

} // namespace et

#endif // is_vectorizable_h
