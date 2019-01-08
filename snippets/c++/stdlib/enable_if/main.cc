#include <type_traits>
#include <iostream>

namespace detail
{

struct inplace_t
{
};

template <bool B, typename T = void>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T>
{
    typedef T type;
};
} // namespace detail

void *operator new(std::size_t, void *p, detail::inplace_t)
{
    return p;
}

// #1 ，通过返回类型使用
template <class T, class... Args>
typename detail::enable_if<std::is_trivially_constructible<T, Args &&...>::value>::type
construct(T *t, Args &&... args)
{
    std::cout << "constructing trivially constructible T\n";
}

// #2
template <class T, class... Args>
typename detail::enable_if<!std::is_trivially_constructible<T, Args &&...>::value>::type // 使用帮助类型
construct(T *t, Args &&... args)
{
    std::cout << "constructing non-trivially constructible T\n";
    new (t, detail::inplace_t{}) T(args...);
}

// #3 ，通过函数形参启用
template <class T>
void destroy(T *t,
             typename std::enable_if<std::is_trivially_destructible<T>::value>::type * = nullptr)
{
    std::cout << "destroying trivially destructible T\n";
}

// #4 ，通过模板形参启用
template <class T,
          typename std::enable_if<
              !std::is_trivially_destructible<T>{} &&
                  (std::is_class<T>{} || std::is_union<T>{}),
              int>::type = 0>
void destroy(T *t)
{
    std::cout << "destroying non-trivially destructible T\n";
    t->~T();
}

// #5 ，通过模板形参启用
template <class T,
          typename = std::enable_if_t<std::is_array<T>::value>>
void destroy(T *t) // 注意，不修改函数签名
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i)
    {
        destroy((*t)[i]);
    }
}

// template <class T,
//           typename = std::enable_if_t<std::is_void<T>::value>>
// void destroy(T *t) {} // 错误：与 #5 拥有相同签名

// A 的部分特化通过模板形参启用
template <class T, class Enable = void>
class A
{
  public:
    A() { std::cout << "primary template\n"; }
}; // 初等模板

template <class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  public:
    A() { std::cout << "float/double partial template\n"; }
}; // 为浮点类型特化

int main(int argc, char const *argv[])
{
    /* code */
    std::aligned_union_t<0, int, std::string> u;
    construct(reinterpret_cast<int *>(&u));
    destroy(reinterpret_cast<int *>(&u));

    construct(reinterpret_cast<std::string *>(&u), "Hello");
    destroy(reinterpret_cast<std::string *>(&u));

    A<int> a1;
    A<float> a2;
    A<double> a3;
    return 0;
}
