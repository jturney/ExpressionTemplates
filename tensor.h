#ifndef tensor_h
#define tensor_h

namespace et {

template <typename DataType>
struct tensor
{
    typedef DataType data_type;

    tensor(size_t size) : size_(size) {
        data_ = new data_type[size];
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

    size_t size_;
    data_type* data_;
};

}

#endif // tensor_h
