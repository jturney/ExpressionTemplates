#ifndef tensor_h
#define tensor_h

#include <cstdio> // for printf
namespace et {

template <typename DataType>
struct tensor
{
    typedef DataType data_type;
    enum { vector_size = data_type::vector_size };

    tensor(size_t size) : real_size_(size) {
        // need to do size checking of size with data_type::vector_size
        // this may result in padding being applied to data_.
        size_ = (real_size_ + vector_size - 1) % vector_size;
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
        for (size_t i=0; i<size_; ++i) {
            data_[i] = x[i];
        }
        return *this;
    }

    void print() const {
        printf("tensor: size = %zu\n", size_);
        for (size_t i=0; i<size_; ++i) {
            data_[i].print();
//            if ((i + data_type::vector_size) % 8 == 0)
            if (i+4 % 8 == 0)
                printf("\n");
        }
        printf("\n");
    }

    /// Real size of the vector that the user requested.
    size_t real_size_;
    /// Actual size of the vector (real_size + data_type::vector_size - 1) % data_type::vector_size
    size_t size_;
    data_type* data_;
};

}

#endif // tensor_h
