#if !defined alignment_trait_h
#define alignment_trait_h

#include <boost/type_traits/alignment_of.hpp>

#include <et/config.h>
#include <et/type_traits/is_vectorizable.h>

namespace et {

template<typename T>
struct alignment_trait
{
#if ET_SSE2_MODE
    // If SSE is available for the data type then we need 16 byte alignment
    // otherwise boost::alignment_of will return return the size of the type
    // as the alignment.
    enum { value = ( is_vectorizable<T>::value ) ? 16UL : boost::alignment_of<T>::value };
#else
    enum { value = boost::alignment_of<T>::value };
#endif
};

template<>
struct alignment_trait<float>
{
#if ET_AVX_MODE
    // If we have AVX then 32 byte alignment is required
    enum { value = 32UL };
#elif ET_SSE_MODE
    // Otherwise, 16 byte alignment
    enum { value = 16UL };
#else
    // Otherwise, the size of the type
    enum { value = boost::alignment_of<float>::value };
#endif
};

template<>
struct alignment_trait<double>
{
#if ET_AVX_MODE
    // If we have AVX then 32 byte alignment
    enum { value = 32UL };
#elif ET_SSE_MODE
    // Otherwise, 16 byte alignment
    enum { value = 16UL };
#else
    // Or, the size of the type
    enum { value = boost::alignment_of<double>::value };
#endif
};

} // namespace et

#endif // alignment_trait_h
