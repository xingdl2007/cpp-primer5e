#include <iostream>
#include <functional>
#include <tuple>
#include <type_traits>

// Actually, a subtle bug may arise when the function is using index_constant as parameter.
// For this reason, a more correct implementation should define a specialized class, hidden in a namespace,
// and forbid the use in other places.
// An easier, more correct, but more verbose way would be to just define two different classes for the argument list
// and the bounded arguments, to avoid the confusion with the index_constant bracket operator overload.
// However, as this is only an academic example, it should strive to stay extremly simple and straightforward, so this
// improvment will not be applied. I just wanted anyone wanting to use this somewhere to be aware of this caveheat.
// Moreover, you should use std::bind anyway.

template <size_t n>
using index_constant = std::integral_constant<size_t, n>;

template <class... Args>
class binder_list
{
public:
    template <class... TArgs>
    constexpr binder_list(TArgs &&... args) noexcept
        : boundedArgs_{std::forward<TArgs>(args)...}
    {
    }

    template <size_t n>
    constexpr decltype(auto) operator[](index_constant<n>) noexcept
    {
        return std::get<n>(boundedArgs_);
    }

private:
    std::tuple<Args...> boundedArgs_;
};

template <class... Args>
class callee_list
{
public:
    template <class... TArgs>
    constexpr callee_list(TArgs &&... args) noexcept
        : boundedArgs_{std::forward<TArgs>(args)...}
    {
    }

    template <class T, std::enable_if_t<(std::is_placeholder<std::remove_reference_t<T>>::value == 0)> * = nullptr>
    constexpr decltype(auto) operator[](T &&t) noexcept
    {
        return std::forward<T>(t);
    }

    template <class T, std::enable_if_t<(std::is_placeholder<T>::value != 0)> * = nullptr>
    constexpr decltype(auto) operator[](T) noexcept
    {
        return std::get<std::is_placeholder<T>::value - 1>(std::move(boundedArgs_));
    }

private:
    std::tuple<Args &&...> boundedArgs_;
};

template <class Fn, class... Args>
class binder
{
public:
    template <class TFn, class... TArgs>
    constexpr binder(TFn &&f, TArgs &&... args) noexcept
        : f_{std::forward<TFn>(f)},
          argumentList_{std::forward<TArgs>(args)...}
    {
    }

    // Please C++, give me a way of detecting noexcept :'(
    template <class... CallArgs>
    constexpr decltype(auto) operator()(CallArgs &&... args)
    //noexcept(noexcept(call(std::make_index_sequence<sizeof...(Args)>{}, std::declval<Args>()...)))
    {
        return call(std::make_index_sequence<sizeof...(Args)>{}, std::forward<CallArgs>(args)...);
    }

private:
    template <class... CallArgs, size_t... Seq>
    constexpr decltype(auto) call(std::index_sequence<Seq...>, CallArgs &&... args)
    //noexcept(noexcept(f_(this->binder_list<CallArgs...>{std::declval<CallArgs>()...}[this->argumentList_[index_constant<Seq>{}]]...)))
    {
        return f_((callee_list<CallArgs...>{std::forward<CallArgs>(args)...}[argumentList_[index_constant<Seq>{}]])...);
    }

private:
    std::function<std::remove_reference_t<std::remove_pointer_t<Fn>>> f_;
    binder_list<Args...> argumentList_;
};

namespace me
{
template <class Fn, class... Args>
binder<Fn, Args...> bind(Fn &&f, Args &&... args)
{
    return binder<Fn, Args...>{std::forward<Fn>(f), std::forward<Args>(args)...};
}
} // namespace me