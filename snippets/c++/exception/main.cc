#include <iostream>

class Bad
{
  public:
    // Added the noexcept(false) so the code keeps its original meaning.
    // Post C++11 destructors are by default `noexcept(true)` and
    // this will (by default) call terminate if an exception is
    // escapes the destructor.
    //
    // But this example is designed to show that terminate is called
    // if two exceptions are propagating at the same time.
    ~Bad() noexcept(false)
    {
        throw 1;
    }
};

class Bad2
{
  public:
    ~Bad2()
    {
        throw 1;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        Bad bad;
    }
    catch (...)
    {
        std::cout << "Print This\n";
    }

    try
    {
        if (argc > 3)
        {
            std::cout << " argc > 3 \n";
            Bad bad; // This destructor will throw an exception that escapes (see above)
            throw 2; // But having two exceptions propagating at the
                     // same time causes terminate to be called.
        }
        else
        {
            std::cout << " argc <= 3 \n";
            Bad2 bad; // The exception in this destructor will
                      // cause terminate to be called.
        }
    }
    catch (...)
    {
        std::cout << "Never print this\n";
    }
}