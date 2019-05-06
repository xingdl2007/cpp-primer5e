// https://stackoverflow.com/questions/38565650/what-does-release-sequence-mean

// No he doesn't. All modification to count are atomic, so both reader threads would always see different values for it in the given code.

// He's talking about the implications of the release sequence rule, namely that when a given thread performs a release store, other multiple
// threads that then perform acquire loads of the same location form a release sequence, in which each subsequent acquire load has a
// happens-before relationship with the storing thread (i.e. the completion of the store happens-before the load). This means that the load
// operation in the reader thread is a synchronisation point with the writer thread, and all memory operations in the writer prior to the
// store must complete and be visible in the reader when its corresponding load completes.

// He's saying that without this rule, only the first thread would be thus synchronised to the writer. The second thread would therefore
// have a data race in accessing queue (note: not count, which is protected anyway by atomic access). Theoretically, memory operations on
// data occurring before the store on count could be seen by reader thread number 2 only after its own load operation on count. The release
// sequence rule assures that this will not happen.

// In summary: the release sequence rules assures multiple threads can synchronise their loads on a single store. The synchronisation in
// question is that of memory accesses to data other than the actual atomic variable being synchronised on (which is guaranteed to be synchronised
// anyway due to being atomic).

// Note to add here: for the most part these kind of issues are only of concern on CPU architectures that are relaxed about reordering their
// memory operations. The Intel architecture is not one of them: it is strongly-ordered and has only a few very specific circumstances in which
// memory operations can ever be reordered. These kind of nuances are mostly only relevant when talking about other architectures, such as
// ARM and PowerPC.

#include <vector>
#include <iostream>
#include <atomic>
#include <thread>

std::vector<int> queue_data;
std::atomic<int> count;

void wait_for_more_items() {}
void process(int v)
{
    std::cout << v << std::endl;
}

void populate_queue()
{
    unsigned const number_of_items = 20;
    queue_data.clear();
    for (unsigned i = 0; i < number_of_items; ++i)
    {
        queue_data.push_back(i);
    }
    count.store(number_of_items, std::memory_order_release);
}

void consume_queue_items()
{
    while (true)
    {
        int item_index;
        if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
        {
            wait_for_more_items(); // do nothing, then break
            break;
        }
        process(queue_data[item_index - 1]);
    }
}

int main()
{
    std::thread a(populate_queue);
    std::thread b(consume_queue_items);
    std::thread c(consume_queue_items);

    a.join();
    b.join();
    c.join();
}