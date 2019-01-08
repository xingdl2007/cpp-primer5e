#include <type_traits>
#include <tuple>
#include <iostream>

using std::cout;

// True if Predicate matches for none of the types Ts
template <template <typename> class Predicate, typename... Ts>
struct static_none_of : std::is_same<std::tuple<std::false_type, typename Predicate<Ts>::type...>,
                                     std::tuple<typename Predicate<Ts>::type..., std::false_type>>
{
};

template <typename... Types>
class varaint
{
    static_assert(static_none_of<std::is_reference, Types...>::value, "Variant can not hold reference types. Maybe use std::reference?");
};

// declaration
template <typename... Types>
struct variant_helper;

//
template <typename T, typename... Types>
struct variant_helper<T, Types...>
{
    static void destroy()
    {
        cout << "template <typename T, typename... Types>\nstruct variant_helper<T, Types...>\n";
    }

    static void move()
    {
        cout << "template <typename T, typename... Types>\nstruct variant_helper<T, Types...>\n";
    }

    static void copy()
    {
        cout << "template <typename T, typename... Types>\nstruct variant_helper<T, Types...>\n";
    }
};

// when template type parameter is int
template <>
struct variant_helper<int>
{
    static void destroy() { cout << "template <>\nstruct variant_helper<int>\n"; }
    static void move() { cout << "template <>\nstruct variant_helper<int>\n"; }
    static void copy() { cout << "template <>\nstruct variant_helper<int>\n"; }
};

// default, no template parameter
template <>
struct variant_helper<>
{
    static void destroy() { cout << "template <>\nstruct variant_helper<>\n"; }
    static void move() { cout << "template <>\nstruct variant_helper<>\n"; }
    static void copy() { cout << "template <>\nstruct variant_helper<>\n"; }
};

static constexpr std::size_t invalid_value = std::size_t(-1);

// at least has one template type parameter
template <typename T, typename... Types>
struct direct_type;

template <typename T, typename First, typename... Types>
struct direct_type<T, First, Types...>
{
    static constexpr std::size_t index = std::is_same<T, First>::value
                                             ? sizeof...(Types)
                                             : direct_type<T, Types...>::index;
};

template <typename T>
struct direct_type<T>
{
    static constexpr std::size_t index = invalid_value;
};

int main(int argc, char const *argv[])
{
    {
        cout << direct_type<int>::index << std::endl;
        cout << direct_type<int, int>::index << std::endl;
        cout << direct_type<int, double>::index << std::endl;
        cout << direct_type<int, double, int>::index << std::endl;
        cout << direct_type<float, int, double, int>::index << std::endl;
    }

    {
        variant_helper<>::copy();
        cout << '\n';
        variant_helper<int>::copy();
        cout << '\n';
        variant_helper<int, double>::copy();
        cout << '\n';
    }

    {
        using TupleA = std::tuple<int, double, std::true_type>;
        using TupleB = std::tuple<int, double, std::false_type>;

        std::cout << std::boolalpha;
        std::cout << std::is_same<TupleA, TupleB>::value << std::endl;
    }
    return 0;
}
