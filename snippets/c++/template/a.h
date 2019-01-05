#pragma once

#include <mutex>

class A
{
  public:
    A()
    {
        printf("A()\n");
        m.lock();
    }
    ~A()
    {
        printf("~A()\n");
    }

    void fun()
    {
        m.lock();
    }

  private:
    std::mutex m;
};

class B
{
  public:
    B()
    {
        printf("B()\n");
    }

    ~B()
    {
        printf("~B()\n");
        a.fun();
    }
    
    static A a;
};