#include <iostream>

static constexpr std::size_t invalid_value = std::size_t(-1);

// template declaration
template <typename T, typename... Types>
struct direct_type;

template <typename T>
struct direct_type<T>
{
    static constexpr std::size_t index = invalid_value;
};

template <typename T, typename First, typename... Types>
struct direct_type<T, First, Types...>
{
    static constexpr std::size_t index = std::is_same<T, First>::value
                                             ? sizeof...(Types)
                                             : direct_type<T, Types...>::index;
};

// template declaration
template <typename T, typename... Types>
struct convertible_type;

template <typename T>
struct convertible_type<T>
{
    static constexpr std::size_t index = invalid_value;
};

template <typename T, typename First, typename... Types>
struct convertible_type<T, First, Types...>
{
    static constexpr std::size_t index = std::is_convertible<T, First>::value
                                             ? sizeof...(Types)
                                             : convertible_type<T, Types...>::index;
};

// check if T is in Types..., interesting
template <typename T, typename... Types>
struct has_type;

template <typename T>
struct has_type<T> : std::false_type
{
};

template <typename T, typename First, typename... Types>
struct has_type<T, First, Types...>
{
    static constexpr bool value = std::is_same<T, First>::value || has_type<T, Types...>::value;
};

template <typename T, typename... Types>
struct is_valid_type;

template <typename T>
struct is_valid_type<T> : std::false_type
{
};

template <typename T, typename First, typename... Types>
struct is_valid_type<T, First, Types...>
{
    static constexpr bool value = std::is_convertible<T, First>::value || is_valid_type<T, Types...>::value;
};

// enable if: not
template <typename T, typename R = void>
struct enable_if_type
{
    using type = R;
};

template <typename F, typename V, typename Enable = void>
struct result_of_unary_visit
{
    using type = typename std::result_of<F(V &)>::type;
};

template <typename F, typename V>
struct result_of_unary_visit<F, V, typename enable_if_type<typename F::result_type>::type>
{
    using type = typename F::result_type;
};

template <typename F, typename V, typename Enable = void>
struct result_of_binary_visit
{
    using type = typename std::result_of<F(V &, V &)>::type;
};

template <typename F, typename V>
struct result_of_binary_visit<F, V, typename enable_if_type<typename F::result_type>::type>
{
    using type = typename F::result_type;
};

// static_max
template <std::size_t arg1, std::size_t... others>
struct static_max;

template <std::size_t arg>
struct static_max<arg>
{
    static const std::size_t value = arg;
};

template <std::size_t arg1, std::size_t arg2, std::size_t... others>
struct static_max<arg1, arg2, others...>
{
    static const std::size_t value = arg1 >= arg2 ? static_max<arg1, others...>::value : static_max<arg2, others...>::value;
};

int main()
{
    // direct_type
    std::cout << direct_type<double>::index << std::endl;
    std::cout << direct_type<int, double>::index << std::endl;
    std::cout << direct_type<int, int, double>::index << std::endl;
    std::cout << direct_type<int, int, int, double>::index << std::endl;
    std::cout << direct_type<int, double, double, float>::index << std::endl;

    // convertible_type
    std::cout << '\n';
    std::cout << convertible_type<double>::index << std::endl;
    std::cout << convertible_type<int, double>::index << std::endl;
    std::cout << convertible_type<int, int, double>::index << std::endl;
    std::cout << convertible_type<int, int, int, double>::index << std::endl;
    std::cout << convertible_type<int, double, double, float>::index << std::endl;

    // has types
    std::cout << '\n';
    std::cout << std::boolalpha << has_type<double>::value << std::endl;
    std::cout << std::boolalpha << has_type<int, double>::value << std::endl;
    std::cout << std::boolalpha << has_type<int, int, double>::value << std::endl;
    std::cout << std::boolalpha << has_type<int, int, int, double>::value << std::endl;
    std::cout << std::boolalpha << has_type<int, double, double, float>::value << std::endl;

    // is valid type
    std::cout << '\n';
    std::cout << std::boolalpha << is_valid_type<double>::value << std::endl;
    std::cout << std::boolalpha << is_valid_type<int, double>::value << std::endl;
    std::cout << std::boolalpha << is_valid_type<int, int, double>::value << std::endl;
    std::cout << std::boolalpha << is_valid_type<int, int, int, double>::value << std::endl;
    std::cout << std::boolalpha << is_valid_type<int, double, double, float>::value << std::endl;

    // static max
    std::cout << '\n';
    std::cout << static_max<15>::value << std::endl;
    std::cout << static_max<1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value << std::endl;
    std::cout << static_max<80, 9, 100>::value << std::endl;
}