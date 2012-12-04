#if !defined ops_h
#define ops_

namespace et {

struct plus
{
    template <typename data_type>
    static data_type apply(data_type a, data_type b) {
        return a + b;
    }
};

struct minus
{
    template <typename data_type>
    static data_type apply(data_type a, data_type b) {
        return a - b;
    }
};

struct square_root
{
    template <typename data_type>
    static data_type apply(data_type a) {
        return sqrt(a);
    }
};

}

#endif // ops_h
