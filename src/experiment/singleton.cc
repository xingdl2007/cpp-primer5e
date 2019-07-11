// https://blog.csdn.net/fullsail/article/details/8483106
// very interesting blog post, but wired's implementation does not works any more
// g++ 7.4.0

#include <iostream>

//#define detail naive
#define detail wired

namespace naive
{
template <typename T>
class Singleton
{
private:
    static T obj;

public:
    const static T *instance()
    {
        return &obj;
    }
};

template <typename T>
T Singleton<T>::obj;

} // namespace naive

namespace wired
{
//---------------
template <typename T>
class Singleton
{
private:
    struct object_creator
    {
        object_creator()
        {
            Singleton<T>::instance();
        }
        inline void do_nothing() const {}
    };

    //利用类的静态对象object_creator的构造初始化,在进入main之前已经调用了instance
    //从而避免了多次初始化的问题
    static object_creator create_object_;

public:
    static T *instance()
    {
        static T obj;
        //do_nothing 是必要的，do_nothing的作用有点意思，
        //如果不加create_object_.do_nothing();这句话，在main函数前面
        //create_object_的构造函数都不会被调用，instance当然也不会被调用，
        //我的估计是模版的延迟实现的特效导致，如果没有这句话，编译器也不会实现
        // Singleton<T>::object_creator,所以就会导致这个问题
        create_object_.do_nothing();
        return &obj;
    }
};
//因为create_object_是类的静态变量，必须有一个通用的声明
template <typename T>
typename Singleton<T>::object_creator Singleton<T>::create_object_;

} // namespace wired

class A;
class B;

class A
{
    friend class detail::Singleton<A>;

protected:
    A();

public:
    void do_something() const;

private:
    mutable int a;
};

class B
{
    friend class detail::Singleton<B>;

protected:
    B();

public:
    void do_something() const;

private:
    mutable int b;
};

A::A() : a(1)
{
    std::cout << "A::A() this[" << this << "], a[" << a << "]" << std::endl;
    detail::Singleton<B>::instance()->do_something();
}

void A::do_something() const
{
    a += 1000;
    std::cout << "A::do_something() this[" << this << "], a[" << a << "]" << std::endl;
}

B::B() : b(2)
{
    std::cout << "B::B() this[" << this << "], b[" << b << "]" << std::endl;
    detail::Singleton<A>::instance()->do_something();
}

void B::do_something() const
{
    b += 2000;
    std::cout << "B::do_something() this[" << this << "], b[" << b << "]" << std::endl;
}

int main()
{
    const int *data = detail::Singleton<int>::instance();
    std::cout << "In main(): " << *data << std::endl;
    return 0;
}