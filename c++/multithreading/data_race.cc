#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

// std::mutex mt;
int i = 17;

void increment()
{
    // mt.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));   //read delay
    int a = i;
    printf("Read from server: %d\n", a);

    a += 1; // increment

    std::this_thread::sleep_for(std::chrono::seconds(1));   // write delay

    i = a;
    // mt.unlock();
}

int main(int argc, char const *argv[])
{
    using std::thread;

    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    return 0;
}
