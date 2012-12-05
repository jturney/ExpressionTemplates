#if !defined is_float_h
#define is_float_h

// for boost::true_type and boost::false_type
#include <boost/type_traits/integral_constant.hpp>

namespace et {

template<typename T> struct is_float              : public boost::false_type {};
template<> struct is_float<float>                : public boost::true_type {};
template<> struct is_float<const float>          : public boost::true_type {};
template<> struct is_float<volatile float>       : public boost::true_type {};
template<> struct is_float<const volatile float> : public boost::true_type {};

}

#endif // is_float_h
