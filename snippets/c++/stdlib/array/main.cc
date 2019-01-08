#include <array>
#include <iostream>

using namespace std;

template <std::size_t N>
struct Test
{
    void print();
};

template <std::size_t N>
void Test<N>::print()
{
    std::cout << N << std::endl;
}

class StaticInit
{
  public:
    StaticInit()
    {
        data[0] = 100;
    }

    void Dump()
    {
        std::cout << data[0] << " " << data[1] << " " << data[2] << std::endl;
        std::cout << std::boolalpha << init << std::endl;
    }

  private:
    std::array<int, 3> data{};
    bool init = true;
};

int main()
{
    {
        StaticInit init;
        init.Dump();
    }
    {
        constexpr std::size_t length = 100;
        Test<length> t1;
        t1.print();
    }
    {
        std::array<int, 3> arr{};
        std::cout << arr.size() << std::endl;
        for (auto i : arr)
        {
            std::cout << i << std::endl;
        }
    }
}