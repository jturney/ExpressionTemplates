#include <cstdio>

#include "avx.h"
#include "expr.h"
#include "tensor.h"

using namespace et;

int main(int /*argc*/, char** /*argv*/)
{
    enum { N = 2 };
    avx one(1.0, 2.0, 3.0, 4.0), two(2.0);

    tensor<avx> x(N), y(N), z(N);

    // Calls the operator= on the first avx object which sets all 4 doubles to 1.0, or 2.0
    x[0] = one;
    y[0] = two;
    x[1] = two;
    y[1] = one;

    z = x + y;

    printf("%10s%10s%10s\n", "x", "y", "z");
    avx x0 = x[0], y0 = y[0], ans = z.data_[0];
    for (int i=0; i<4; ++i)
        printf("%10lf%10lf%10lf\n", x0.d[i], y0.d[i], ans.d[i]);
    x0 = x[1]; y0 = y[1]; ans = z.data_[1];
    for (int i=0; i<4; ++i)
        printf("%10lf%10lf%10lf\n", x0.d[i], y0.d[i], ans.d[i]);

    return 0;
}
