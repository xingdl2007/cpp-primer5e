#include <dlfcn.h>
#include <iostream>
#include <functional>
#include <memory>
#if defined(__GNUG__)
#include <cxxabi.h> // abi::__cxa_demangle
#endif
#include <any>

// The Linux Programming interface: Chapter 42
void *plugin;

void DlError(const char *func)
{
    if (dlerror() != nullptr)
    {
        std::cout << func << " failed\n";
        abort();
    }
}

template <typename T>
std::function<T> get(const std::string &s)
{
    std::function<T> r = nullptr;

    // std::function constructed from free function pointer
    if (plugin != nullptr)
        r = reinterpret_cast<T *>(dlsym(plugin, s.c_str()));
    return r;
}

inline int is_le()
{
    static const std::uint32_t i = 0x04030201;
    return (*((std::uint8_t *)(&i)) == 1);
}

template <typename... T>
class Signature
{
  public:
    Signature() : s_(typeid(std::any(T...)).name())
    {
        std::cout << s_ << std::endl;
#if defined(__GNUG__)
        int status = -1;
        std::unique_ptr<char, void (*)(void *)> res{
            abi::__cxa_demangle(s_.c_str(), nullptr, nullptr, &status),
            std::free};

        if (status == 0)
            s_ = res.get();

        std::cout << s_ << std::endl;
#endif
    }

  private:
    std::string s_;
};

// simple demonstrate plugin method
int main(int argc, char *argv[])
{
    plugin = dlopen("./libplugin_hello.so", RTLD_NOW); // relative path
    DlError("dlopen");

    void (*func)(int);

    // method one:
    // *(void **)&func = (dlsym(plugin, "hello")); // function pointer

    // methdo two:
    func = (void (*)(int))(dlsym(plugin, "hello")); // function pointer
    DlError("dlsym");

    // the following is error: error: lvalue required as left operatnd of assignment
    // (void*)func as a rvalue not a lvalue
    // (void*)func = dlsym(plugin, "hello"); // function pointer

    (*func)(100);

    auto f = get<void(int)>("hello");
    f(200);

    dlclose(plugin);
    DlError("dlclose");

    std::shared_ptr<int> p = nullptr;
    std::cout << sizeof(p) << std::endl; // 16 bytes, basically two pointers

    uint64_t array[4] __attribute__((aligned(4)));
    std::cout << std::dec << sizeof(array) << std::endl;

    Signature<int, int> s;
}