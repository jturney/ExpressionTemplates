#include <cstdio>

#include "avx.h"
#include "expr.h"
#include "tensor.h"

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

}

using namespace et;

int main(int /*argc*/, char** /*argv*/)
{
    enum { N = 3 };
    avx one(1.0, 2.0, 3.0, 4.0), two(2.0);

    dimension<'o'> o(3);
    o.print();

    tensor<avx> x(N), y(N), z(N);

    // Calls the operator= on the first avx object which sets all 4 doubles to 1.0, or 2.0
    x[0] = one;
    y[0] = two;
    x[1] = two;
    y[1] = one;

    z = x + y;

    printf("vector size = %d\n", avx::vector_size);

    x.print();
    y.print();
    z.print();

    return 0;
}
