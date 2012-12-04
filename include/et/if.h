#ifndef if_h
#define if_h

namespace et {

// Template class if_ -- select among 2 types based on a bool constant expression
// Usage:
//   typename if_<(bool_const_expression)>::template then_<true_type, false_type>::type

template <bool b> struct if_
{
    template <class T, class F>
    struct then_ { typedef T type; };
};

template <>
struct if_<false>
{
    template <class T, class F>
    struct then_ { typedef F type; };
};

}

#endif // if_h
