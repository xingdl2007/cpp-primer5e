template <class T>
void doNotOptimizeAway(T &&datum)
{
    asm volatile(""
                 : "+r"(datum));
}

int main(int argc, char *argv)
{
    int sum = 0;
    for (int i = 0; i < 100; ++i)
    {
        doNotOptimizeAway(sum += i);
    }

    doNotOptimizeAway(sum);
}