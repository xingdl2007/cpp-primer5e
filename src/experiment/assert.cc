#include <assert.h>

int main(int argc, char *argv[])
{
    assert(0);        // -DNDEBUG
    __builtin_trap(); // ASSERT not controlled by NDEBUG
    return 0;
}