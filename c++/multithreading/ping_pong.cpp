#include <iostream>
#include <thread>
#include <chrono>
#include <string>


void print_msg(std::string msg)
{
    while (true)
    {
        std::cout << "Thread: " << std::this_thread::get_id() << " works" << std::endl;
        std::cout << msg << std::endl;                          // print a message
        std::cout << "Thread: " << std::this_thread::get_id() << " sleeps" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));   // sleep for a second   
    }
}

int main(int argc, char const *argv[])
{   
    // start threads
    std::thread t1(print_msg, "Ping!");
    std::thread t2(print_msg, "Pong!");

    //  wait till both thread finish their work
    t1.join();
    t2.join();

    return 0;
}
