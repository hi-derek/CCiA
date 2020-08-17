#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

using namespace std;

std::atomic<bool> x,y;
std::atomic<int> z;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));

    if(y.load(std::memory_order_seq_cst)) {
        stdlog<<"read_x_then_y" "\n";
        ++z;
    }
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));

    if(x.load(std::memory_order_seq_cst)){
        stdlog<<"read_y_then_x" "\n";
        ++z;
    }
}


bool test(int loop) {
    bool fail=false;
    do {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x);
        std::thread b(write_y);
        std::thread c(read_x_then_y);
        std::thread d(read_y_then_x);
        a.join();
        b.join();
        c.join();
        d.join();
        fail=(z.load() == 0);
        assert(!fail);
    } while(--loop>0);
    return fail?-1:0;
}


int main()
{
    test(10);

    return 0;
}
