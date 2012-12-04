#include <cstdio>
#include <et/et.h>

namespace et {

}

using namespace et;

#define base_type sse

int main(int /*argc*/, char** /*argv*/)
{
    base_type one(1.0/*, 2.0, 3.0, 4.0*/),
        two(2.0),
        four(4.0);

    occ o(3);
    virt v(5);
    o.print();

    tensor<base_type, occ> i("i", o), j("j", o), k("k", o), l("l", o);
    tensor<base_type, virt> a("a", v);

    // Calls the operator= passing an avx object to each element in the tensor.
    i = one;
    j = two;
    l = four;

    k = i + j;

    i.print();
    j.print();
    k.print();

    k = i - j;
    k.print();

    printf("k = i + sqrt(l): i = one, l = four\n");
    k = i + sqrt(l);
    k.print();

    // The following line fails because you're trying to assign a virtual tensor
    // to an occupied tensor. This results in a compile time static aavxrtion
    // with a nice error message.
//    k = a;

    return 0;
}
