#include <deque>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <iostream>

std::deque<int> buffer;
std::mutex buffer_mutex;    // provide thread-safe access to the buffer


void produce()
{

    while (true) 
    {
        if (buffer.size() < 10)
        {
            buffer_mutex.lock();
            
            buffer.push_back(1);
            std::cout << "Producer added element to queue." <<
            "Deque size =" << buffer.size() << std::endl;
            
            buffer_mutex.unlock(); 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()/(RAND_MAX/100)));   // sleep for a second
    }
}

void consume()
{   
    while (true)
    {
        if (!buffer.empty()) {
            buffer_mutex.lock();

            buffer.pop_back();
            std::cout << "Consumer removed element from queue." 
            "Deque size = " << buffer.size() << std::endl; 
    
            buffer_mutex.unlock();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()/(RAND_MAX/100)));   // sleep for a second
    }
}

int main(int argc, char const *argv[])
{
    std::srand(std::time(nullptr)); // randomizer initialization
    
    std::thread t1(produce);
    std::thread t2(consume);

    t1.join();
    t2.join();


    return 0;
}
