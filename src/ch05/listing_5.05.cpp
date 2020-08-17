#include <cstdlib>
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x,y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed));

    if (x.load(std::memory_order_relaxed))
        ++z;
}

int testcase_memory_order_relaxed() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    return z.load() == 0;
}

int test(int loop) {
    int i=1;
    int res=0;
    for(;i<=loop;++i) {
        res=testcase_memory_order_relaxed();
        stdlog.println(sep(""), i, "/", loop, sep(" "), ":", res);
        if(res) break;
    }
    stdlog.println(res?"[FAIL]":"[PASS]", "in", sep(), i, "/", loop, sep(" "), " loops");
    return res;
}

std::atomic<int> a,b,c;
std::atomic_flag run = ATOMIC_FLAG_INIT;

void increase_a_then_b(int loop)
{
    while(loop-->0 && run.test_and_set(std::memory_order_relaxed)) {
        a.fetch_add(1, std::memory_order_relaxed);
        b.fetch_add(1, std::memory_order_relaxed);
    }
}

void read_a_then_b(int loop)
{
    int x=0,y=0;
    while(loop>0&&(x=a.load(std::memory_order_relaxed))>=(y=b.load(std::memory_order_relaxed))) --loop;
    if(loop) {
        run.clear(std::memory_order_relaxed);
        c.fetch_add(1);
        stdlog.println(sep(),"x=",x," / y=",y,sep(" "));
    }
}

int testcase_memory_order_relaxed2() {
    a=0;
    b=0;
    c=0;
    int loop=10000;
    run.test_and_set();
    std::thread ta(increase_a_then_b, loop);
    std::thread tb(read_a_then_b, loop);
    ta.join();
    tb.join();
    return c.load();
}

int test2(int loop) {
    int i=1;
    int res=0;
    for(;i<=loop;++i) {
        res=testcase_memory_order_relaxed2();
        stdlog.println(sep(""), i, "/", loop, sep(" "), ":", res);
        if(res) break;
    }
    stdlog.println(res?"[FAIL]":"[PASS]", "in", sep(), i, "/", loop, sep(" "), " loops");
    return res;
}

int main(int argc, char **argv)
{
    int loop=10;
    if(argc>1) loop=strtol(argv[1],nullptr,0);
    test(loop);
    stdlog.println("###################################################");
    test2(loop);
    return 0;
}
