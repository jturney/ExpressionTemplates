#if !defined is_short_h
#define is_short_h

// for boost::true_type and boost::false_type
#include <boost/type_traits/integral_constant.hpp>

namespace et {

template<typename T> struct is_short           : public boost::false_type {};
template<> struct is_short<short>                : public boost::true_type {};
template<> struct is_short<const short>          : public boost::true_type {};
template<> struct is_short<volatile short>       : public boost::true_type {};
template<> struct is_short<const volatile short> : public boost::true_type {};
template<> struct is_short<unsigned short>                : public boost::true_type {};
template<> struct is_short<const unsigned short>          : public boost::true_type {};
template<> struct is_short<volatile unsigned short>       : public boost::true_type {};
template<> struct is_short<const volatile unsigned short> : public boost::true_type {};

}

#endif // is_short_h
