#ifndef is_tensor_h
#define is_tensor_h

#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace et {

// forward declare tensor's base class
struct tensor_base;

template<typename T>
struct is_tensor_helper
{
private:
    typedef typename boost::remove_cv<T>::type T2;

public:
    enum { value = boost::is_base_of<tensor_base>::value };
};

template<typename T>
struct is_tensor : public is_tensor_helper<T>
{
    enum { value = is_tensor_helper<T>::value };
};

}

#endif // IS_TENSOR_H
