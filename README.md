ExpressionTemplates
===================

This project is a playground for a C++ DSL for computing tensors.
Example usage:


    // Define some initial constants
    sse one(1.0/*, 2.0, 3.0, 4.0*/), two(2.0), four(4.0);

    // Define our spaces
    occ o(3);
    virt v(5);
    o.print();

    // Define out tensors
    tensor<sse, occ> i("i", o), j("j", o), k("k", o), l("l", o);
    tensor<sse, virt> a("a", v);

    // Calls the operator= passing an sse object to each element in the tensor.
    i = one;
    j = two;
    l = four;

    // Add two tensors of the same space together
    k = i + j;

    // Subtract two tensors of the same together
    k = i - j;

    // Take the sqrt of one tensor and add the result to another tensor
    k = i + sqrt(l);

    // The following line fails because you're trying to assign a virtual tensor
    // to an occupied tensor. This results in a compile time static aavxrtion
    // with a nice error message.
    //  k = a;
