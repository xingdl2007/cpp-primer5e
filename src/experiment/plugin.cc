#include <dlfcn.h>
#include <iostream>
#include <functional>

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
}