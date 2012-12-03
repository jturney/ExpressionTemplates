#ifndef tensor_h
#define tensor_h

#include <cstdio> // for printf
#include <string>

#include <boost/type_traits/is_same.hpp>

namespace et {

template <char Label>
struct dimension
{
    typedef unsigned int length_type;

    enum { label = Label };

    length_type length;

    dimension(length_type l) : length(l) {}

    operator length_type() const {
        return length;
    }

    void print() const {
        printf("dimension: %c, length %u\n", label, length);
    }
};

typedef dimension<'o'> occ;
typedef dimension<'v'> virt;

template <typename DataType, typename D1>
struct tensor
{
    typedef DataType data_type;
    enum { vector_size = data_type::vector_size };

    tensor(const std::string& name, const D1& d1) : name_(name), real_size_(d1) {
        // need to do size checking of size with data_type::vector_size
        // this may result in padding being applied to data_.
        size_ = real_size_ / vector_size;
        if (real_size_ % vector_size)
            size_ += 1;
        data_ = new data_type[size_];
    }
    ~tensor() {
        delete[] data_;
    }

    data_type& operator[](size_t i) {
        return data_[i];
    }

    data_type const& operator[](size_t i) const {
        return data_[i];
    }

    template <typename Expr>
    tensor& operator=(Expr const& x) {
        for (size_t i=0; i<size_; ++i)
            data_[i] = x[i];
        return *this;
    }

    template<typename Dimension2>
    tensor& operator=(tensor<data_type, Dimension2> const& x) {
        static_assert(boost::is_same<D1, Dimension2>::value, "Tensor assigment only possible across same dimension.");

        for (size_t i=0; i<size_; ++i)
            data_[i] = x[i];
        return *this;
    }

    tensor& operator=(data_type const& x) {
        for (size_t i=0; i<size_; ++i)
            data_[i] = x;
        return *this;
    }

    void print() const {
        printf("tensor: name = %s size = %zu vector_size = %d user_requested %zu\n",
               name_.c_str(), size_, data_type::vector_size, real_size_);
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
    /// Actual size of the vector (real_size + data_type::vector_size - 1) % data_type::vector_size
    size_t size_;
    data_type* data_;
};

}

#endif // tensor_h
