#if !defined is_int_h
#define is_int_h

// for boost::true_type and boost::false_type
#include <boost/type_traits/integral_constant.hpp>

namespace et {

template<typename T> struct is_int           : public boost::false_type {};
template<> struct is_int<int>                : public boost::true_type {};
template<> struct is_int<const int>          : public boost::true_type {};
template<> struct is_int<volatile int>       : public boost::true_type {};
template<> struct is_int<const volatile int> : public boost::true_type {};
template<> struct is_int<unsigned int>                : public boost::true_type {};
template<> struct is_int<const unsigned int>          : public boost::true_type {};
template<> struct is_int<volatile unsigned int>       : public boost::true_type {};
template<> struct is_int<const volatile unsigned int> : public boost::true_type {};

}

#endif // is_double_h
