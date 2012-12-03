#include <cstdio>

#include "avx.h"
#include "expr.h"
#include "tensor.h"

namespace et {



}

using namespace et;

int main(int /*argc*/, char** /*argv*/)
{
    avx one(1.0/*, 2.0, 3.0, 4.0*/),
        two(2.0);

    occ o(3);
    virt v(5);
    o.print();

    tensor<avx, occ> i("i", o), j("j", o), k("k", o);
    tensor<avx, virt> a("a", v);

    // Calls the operator= passing an avx object to each element in the tensor.
    i = one;
    j = two;

    k = i + j;

    i.print();
    j.print();
    k.print();

    k = i - j;
    k.print();

    // The following line fails because you're trying to assign a virtual tensor
    // to an occupied tensor. This results in a compile time static assertion
    // with a nice error message.
//    k = a;

    return 0;
}
