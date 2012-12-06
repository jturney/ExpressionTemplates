#ifndef tensor_h
#define tensor_h

#include <cstdio> // for printf
#include <string>

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

}

#endif // tensor_h
