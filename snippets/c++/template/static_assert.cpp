#include <type_traits>

template <class T>
void swap(T &a, T &b)
{
    static_assert(std::is_copy_constructible<T>::value,
                  "Swap requires copying");
    static_assert(std::is_nothrow_copy_constructible<T>::value && std::is_nothrow_copy_assignable<T>::value,
                  "Swap requires nothrow copy/assign");
    auto c = b;
    b = a;
    a = c;
}

template <class T>
struct data_structure
{
    static_assert(std::is_default_constructible<T>::value,
                  "Data Structure requires default-constructible elements");
};

struct no_copy
{
    no_copy(const no_copy &) = delete;
    no_copy() = default;
};

struct no_default
{
    no_default() = delete;
};

// True if Predicate matches for none of the types Ts
template <template <typename> class Predicate, typename... Ts>
struct static_none_of : std::is_same<std::tuple<std::false_type, typename Predicate<Ts>::type...>,
                                     std::tuple<typename Predicate<Ts>::type..., std::false_type>>
{
};

int main()
{
    int a, b;
    swap(a, b);

    no_copy nc_a, nc_b;
    swap(nc_a, nc_b); // 1

    data_structure<int> ds_ok;
    data_structure<no_default> ds_error; // 2
}