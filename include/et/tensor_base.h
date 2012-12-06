#if !defined tensor_base_h
#define tensor_base_h

namespace et {

/*! \brief Base class for tensors.
 *  \ingroup tensor
 *
 * The tensor_base struct is a the base for all tensors. It provides an
 * abstraction from the actual type of tensor, but enables a conversion
 * back to its type via the 'Curiously Recurring Template Pattern'.
 */
template<typename TT> // Type of the tensor
struct tensor_base
{
    typedef TT tensor_type;

    /// Handles type casting
    tensor_type& operator~() {
        return *static_cast<tensor_type*>(this);
    }

    ///
    tensor_type const& operator~() const {
        return *static_cast<tensor_type const*>(this);
    }
};

}

#endif // tensor_base_h
