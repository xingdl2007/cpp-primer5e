#pragma once

template <typename T>
class AddSpace
{
  private:
    T const &ref;

  public:
    AddSpace(T const &r) : ref(r) {}

    friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s)
    {
        return os << s.ref << ' ';
    }
};

// interesting: no need to unpack function parameter pack
template <typename... Args>
void print(Args... args)
{
    (std::cout << ... << AddSpace(args)) << '\n';
}
