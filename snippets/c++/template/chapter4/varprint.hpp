#pragma once

#include <iostream>

void print()
{
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n';
    print(args...);
}

template <typename... T>
void printDouble(T const &... args)
{
    print((args + args)...);
}

template <typename... T>
void addOne(T const &... args)
{
    print((args + 1)...);
}

// actually fold expression, including a wrapper
template <typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...)
{
    return (std::is_same_v<T1, TN> && ...);
}

// interesting, idx as function parameter
template <typename C, typename... Idx>
void printElems(C const &coll, Idx... idx)
{
    print(coll[idx]...);
}

// same effect, but idx as template parameter
template <std::size_t... Idx, typename C>
void printIdx(C const &coll)
{
    print(coll[Idx]...);
}

template <std::size_t...>
struct Indices
{
};

template <typename T, std::size_t... Idx>
void printByIdx(T t, Indices<Idx...>)
{
    print(std::get<Idx>(t)...);
}
