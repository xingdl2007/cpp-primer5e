#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
void foo(const T &t)
{
    if (is_pointer<T>::value)
    {
        cout << "foo() called for a pointer" << endl;
    }
    else
    {
        cout << "foo() called for a value" << endl;
    }
}

// interesting: compile error, you can't wirte *t and t in the same expression
// template <typename T>
// void foo2(const T &t)
// {
//     cout << (is_pointer<T>::value ? *t : t) << endl;
// }

// another version: template partial specialization
// true_type + false_type = all_type
template <typename T>
void foo_impl(const T &val, true_type)
{
    cout << "foo_impl() called for pointer to " << *val << endl;
}

template <typename T>
void foo_impl(const T &val, false_type)
{
    cout << "foo_impl() called for value to " << val << endl;
}

template <typename T>
void foo3(const T &val)
{
    // std::is_pointer<T>() will generate an object
    // which is either std::true_type or std::false_type
    foo_impl(val, is_pointer<T>{});
}

// interesting behaviour
int main(int argc, char const *argv[])
{
    /* code */
    int a = 1;
    int *p = &a;
    int &r = a;

    foo(a);
    foo(p);
    foo(r);
    cout << endl;

    foo3(a);
    foo3(p);
    foo3(r);
    return 0;
}
