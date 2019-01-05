#include <type_traits>
#include <tuple>
#include <iostream>

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

int main(int argc, char const *argv[])
{
    {
        using TupleA = std::tuple<int, double, std::true_type>;
        using TupleB = std::tuple<int, double, std::false_type>;

        std::cout << std::boolalpha;
        std::cout << std::is_same<TupleA, TupleB>::value << std::endl;
    }
    return 0;
}
