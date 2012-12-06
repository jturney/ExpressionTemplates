#if !defined dense_tensor_h
#define dense_tensor_h

#include <string>
#include <boost/type_traits/is_same.hpp>

namespace et {

template<typename TT>
struct tensor_base;

template <typename DT, typename D1>
struct dense_tensor : public tensor_base<dense_tensor<DT, D1> >
{
    /// Type of tensor (could be a raw tensor or an expression of a tensor)
    typedef DT tensor_type;

    /// Data width (AVX = 4, SSE2 = 2, etc.)
    enum { vector_size = tensor_type::vector_size };

    dense_tensor(const std::string& name, const D1& d1) : name_(name), real_size_(d1), d1_(d1) {
        // need to do size checking of size with data_type::vector_size
        // this may result in padding being applied to data_.
        size_ = real_size_ / vector_size;
        if (real_size_ % vector_size)
            size_ += 1;
        data_ = new tensor_type[size_];
    }
    ~dense_tensor() {
        delete[] data_;
    }

    tensor_type& operator[](size_t i) {
        return data_[i];
    }

    tensor_type const& operator[](size_t i) const {
        return data_[i];
    }

    template <typename Expr>
    dense_tensor& operator=(Expr const& x) {
        for (size_t i=0; i<size_; ++i)
            data_[i] = x[i];
        return *this;
    }

    template<typename Dimension2>
    dense_tensor& operator=(dense_tensor<tensor_type, Dimension2> const& x) {
        static_assert(boost::is_same<D1, Dimension2>::value, "Tensor assigment only possible across same dimension.");

        for (size_t i=0; i<size_; ++i)
            data_[i] = x[i];
        return *this;
    }

    dense_tensor& operator=(tensor_type const& x) {
        for (size_t i=0; i<size_; ++i)
            data_[i] = x;
        return *this;
    }

    void print() const {
        printf("tensor: name = %s size = %zu vector_size = %d user_requested %zu\n",
               name_.c_str(), size_, tensor_type::vector_size, real_size_);
        for (size_t i=0; i<size_; ++i) {
            data_[i].print();
//            if ((i + data_type::vector_size) % 8 == 0)
            if (i+4 % 8 == 0)
                printf("\n");
        }
        printf("\n");
    }

    /// Name of this tensor.
    std::string name_;
    /// Real size of the vector that the user requested.
    size_t real_size_;
    /// Actual size of the vector
    size_t size_;
    /// Dimension object
    D1 const& d1_;

    /// The actual data
    tensor_type* data_;
};

}

#endif // dense_tensor_
