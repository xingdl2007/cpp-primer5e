#pragma once

template <int Val, typename T>
T addValue(T x)
{
    return x + Val;
}

template <auto Val, typename T = decltype(Val)>
T foo()
{
    return Val;
}

template <typename T, T Val = T{}>
T bar()
{
    return Val;
}