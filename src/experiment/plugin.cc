#include <dlfcn.h>
#include <iostream>

// The Linux Programming interface: Chapter 42

void DlError(const char *func)
{
    if (dlerror() != nullptr)
    {
        std::cout << func << " failed\n";
        abort();
    }
}

// simple demonstrate plugin method
int main(int argc, char *argv[])
{
    void *plugin = dlopen("./libplugin_hello.so", RTLD_NOW); // relative path
    DlError("dlopen");

    void (*func)();

    // method one:
    // *(void **)&func = (dlsym(plugin, "hello")); // function pointer

    // methdo two:
    func = (void (*)())(dlsym(plugin, "hello")); // function pointer

    // the following is error: error: lvalue required as left operatnd of assignment
    // (void*)func as a rvalue not a lvalue
    // (void*)func = dlsym(plugin, "hello"); // function pointer

    DlError("dlsym");

    (*func)();

    dlclose(plugin);
    DlError("dlclose");
}