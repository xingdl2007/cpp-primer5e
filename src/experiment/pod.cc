#include <type_traits>
#include <iostream>
#include <stdlib.h>
#include <string.h>

// POD 类型全称 Plain Old Data: 一个类或结构体通过二进制拷贝后还能保持其数据不变，那么它就是一个POD类型

// trivial（平凡）的定义
// 1. 有 trivial 的构造函数
// 2. 有 trivial 的拷贝构造函数
// 3. 有 trivial 的移动构造函数
// 3. 有 trivial 的拷贝赋值运算符
// 4. 有 trivial 的移动赋值运算符
// 5. 有 trivial 的析构函数
// 6. 不能包含虚函数
// 7. 不能包含虚基类

namespace trivial
{
class A
{
    A() {}
};

class B
{
    B(B const &) {}
};

class C
{
    C(C &&) {}
};

class D
{
    D &operator=(D const &) {}
};

class E
{
    E &operator=(E &&) {}
};

class F
{
    ~F() {}
};

class G
{
    virtual void foo() = 0;
};

class H : G
{
};

class I
{
};
} // namespace trivial

// 标准布局的定义
// 1. 所有非静态成员有相同的访问权限
// 2. 继承树中最多只能有一个类有非静态数据成员
// 3. 子类的第一个非静态成员不可以是基类类型
// 4. 没有虚函数
// 5. 没有虚基类
// 6. 所有非静态数据成员都符合标准布局类型

//  不满足1：所有非静态成员具有相同的访问权限
namespace layout
{
class A
{
  private:
    int a;

  public:
    int b;
};

class B1
{
    static int x1;
};
class B2
{
    int x2;
};
// 不满足2：含有两个（包括两个）以上的类具有非静态数据成员
class B : B1, B2
{
    int x;
};

class C1
{
};
// 不满足3：第一个非静态数据成员是基类类型
class C : C1
{
    C1 c;
};

// 不满足4：有虚函数
class D
{
    virtual void foo() = 0;
};

// 不满足5：有虚基类
class E : D
{
};

// 不满足6：所有非静态数据成员都符合标准布局类型
class F
{
    A a;
};
} // namespace layout

struct POD
{
  public:
    int x;
    double y;
};

int main(int argc, char *argv[])
{
    {
        POD p;
        p.x = 1;
        p.y = 3.14;

        if (std::is_pod<POD>::value)
        {
            std::cout << p.x << " " << p.y << std::endl;
            void *mem = malloc(sizeof(p));

            memcpy(mem, (void *)&p, sizeof(p));

            POD *ptr = (POD *)mem;
            std::cout << ptr->x << " " << ptr->y << std::endl;
        }
    }

    std::cout << "trivial: \n";
    {
        std::cout << "A: ";
        std::cout << std::is_trivial<trivial::A>::value << std::endl;
    }

    {
        std::cout << "B: ";
        std::cout << std::is_trivial<trivial::B>::value << std::endl;
    }
    {
        std::cout << "C: ";
        std::cout << std::is_trivial<trivial::C>::value << std::endl;
    }

    {
        std::cout << "D: ";
        std::cout << std::is_trivial<trivial::D>::value << std::endl;
    }

    {
        std::cout << "E: ";
        std::cout << std::is_trivial<trivial::E>::value << std::endl;
    }

    {
        std::cout << "F: ";
        std::cout << std::is_trivial<trivial::F>::value << std::endl;
    }

    {
        std::cout << "G: ";
        std::cout << std::is_trivial<trivial::G>::value << std::endl;
    }

    {
        std::cout << "H: ";
        std::cout << std::is_trivial<trivial::H>::value << std::endl;
    }

    {
        std::cout << "I: ";
        std::cout << std::is_trivial<trivial::I>::value << std::endl; // also pod type
    }

    std::cout << "standard layout: \n";
    {
        std::cout << "A: \n";
        std::cout << std::is_standard_layout<layout::A>::value << std::endl;
        std::cout << std::is_pod<layout::A>::value << std::endl;
    }

    {
        std::cout << "B1: \n";
        std::cout << std::is_standard_layout<layout::B1>::value << std::endl;
        std::cout << std::is_pod<layout::B1>::value << std::endl;
    }

    {
        std::cout << "B2: \n";
        std::cout << std::is_standard_layout<layout::B2>::value << std::endl;
        std::cout << std::is_pod<layout::B2>::value << std::endl;
    }

    {
        std::cout << "B: \n";
        std::cout << std::is_standard_layout<layout::B>::value << std::endl;
        std::cout << std::is_pod<layout::B>::value << std::endl;
    }

    {
        std::cout << "C: \n";
        std::cout << std::is_standard_layout<layout::C>::value << std::endl;
        std::cout << std::is_pod<layout::C>::value << std::endl;
    }

    {
        std::cout << "D: \n";
        std::cout << std::is_standard_layout<layout::D>::value << std::endl;
        std::cout << std::is_pod<layout::D>::value << std::endl;
    }

    {
        std::cout << "E: \n";
        std::cout << std::is_standard_layout<layout::E>::value << std::endl;
        std::cout << std::is_pod<layout::E>::value << std::endl;
    }

    {
        std::cout << "F: \n";
        std::cout << std::is_standard_layout<layout::F>::value << std::endl;
        std::cout << std::is_pod<layout::F>::value << std::endl;
    }
}