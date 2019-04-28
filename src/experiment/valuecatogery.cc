#include <iostream>
#include <type_traits>

class Foo
{
  public:
    Foo() = default;
    Foo &operator=(Foo const &)
    {
        std::cout << "Foo &operator=(Foo const &)" << std::endl;
    }
};

// better match for prvalue and xvalue
void func(int &&a)
{
    std::cout << "void func(int &&a): " << a << std::endl;
}

// actually can match every value catogery
void func(int const &a)
{
    std::cout << "void func(int const &a): " << a << std::endl;
}

int &lvalue()
{
    static int a;
    return a;
}
int &&rvalue()
{
    static int a;
    return static_cast<int &&>(a);
}
int prvalue()
{
    static int a;
    return a;
}

// compile error if T is deducted const: use static_assert
template <typename T>
void outR(T &arg)
{
    // static_assert(!std::is_const<T>::value, "our parameter of outR<T>(T&) is const");
}

// compile error if T is deducted const: use enable_if
template <typename T, typename = typename std::enable_if<!std::is_const<T>::value>::type>
void foo(T &arg)
{
}

int main()
{
    Foo f;
    // C++: rvalue can occur on the lef-hand side of assignments, because
    // it follows the member function rules
    Foo() = f;

    {
        std::cout << std::boolalpha << std::is_same<decltype(lvalue()), int &>::value << std::endl;
        std::cout << std::boolalpha << std::is_same<decltype(rvalue()), int &&>::value << std::endl;
        std::cout << std::boolalpha << std::is_same<decltype(prvalue()), int>::value << std::endl;
    }

    {
        int a = 100;
        func(a);            // lvalue
        func(100);          // prvalue
        func(std::move(a)); // xvluae
    }

    {
        std::string a = "hi";
        // outR(std::move(a));      // xvalue: cannot bind non-const lvalue to an rvalue
        // outR(std::string("hi")); // prvalue: cannot bind non-const lvalue to an rvalue
    }

    {
        std::string const a = "hi";
        // outR(a);
        // outR("hi"); // rvalue is allowed
        // outR(std::move(a));
    }
}