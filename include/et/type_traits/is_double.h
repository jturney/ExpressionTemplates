#if !defined is_double_h
#define is_double_h

// for boost::true_type and boost::false_type
#include <boost/type_traits/integral_constant.hpp>

namespace et {

template<typename T> struct is_double              : public boost::false_type {};
template<> struct is_double<double>                : public boost::true_type {};
template<> struct is_double<const double>          : public boost::true_type {};
template<> struct is_double<volatile double>       : public boost::true_type {};
template<> struct is_double<const volatile double> : public boost::true_type {};

}

#endif // is_double_h
