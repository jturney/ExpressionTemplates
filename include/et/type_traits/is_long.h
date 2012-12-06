#if !defined is_long_h
#define is_long_h

// for boost::true_type and boost::false_type
#include <boost/type_traits/integral_constant.hpp>

namespace et {

template<typename T> struct is_long           : public boost::false_type {};
template<> struct is_long<long>                : public boost::true_type {};
template<> struct is_long<const long>          : public boost::true_type {};
template<> struct is_long<volatile long>       : public boost::true_type {};
template<> struct is_long<const volatile long> : public boost::true_type {};
template<> struct is_long<unsigned long>                : public boost::true_type {};
template<> struct is_long<const unsigned long>          : public boost::true_type {};
template<> struct is_long<volatile unsigned long>       : public boost::true_type {};
template<> struct is_long<const volatile unsigned long> : public boost::true_type {};

}

#endif // is_long_h
