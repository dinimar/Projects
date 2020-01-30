// queue.h -- interface for a queue
#ifndef QUEUE_H_
#define QUEUE_H_
#include "node.h"
#include "customer.h"

template <typename T>
class Queue
{
private:
    Node<T> *front_;    // pointer to front of Queue
    Node<T> *rear_;     // pointer to rear of Queue

    const int MAX_Q_SIZE_;      // maximum number of items in Queue
    int q_size_ = 0;            // current number of items in Queue
    
    void remove_nodes();

public:
    Queue(int qs = 10); // create queue with a qs limit
    ~Queue();
    // preemptive definitions to prevent public copying
    Queue(const Queue<T> &q);
    Queue<T> &operator=(const Queue<T> &q);
    
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Node<T> &item);  // add item to end
    bool dequeue(Node<T> &item);        // remove item from front
};

template <typename T>
Queue<T>::Queue(int qs) : MAX_Q_SIZE_(qs)
{
    front_ = rear_ = nullptr;
}

// help function to empty queue
// deallocates memory that was used by nodes in queue
template <typename T>
void Queue<T>::remove_nodes()
{
    Node<T> *temp;
    while (front_ != nullptr) // while queue is not yet empty
    {
        temp = front_;           // save address of front item
        front_ = front_->next;    // reset pointer to next item
        delete temp;            // delete former frontA Queue Simulation
    }
}

template <typename T>
Queue<T>::~Queue()
{
    remove_nodes();
}


// Copy assignment operator
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &q)
{
    // Check whether self-assignment or not
    if (this != &q) {
        remove_nodes();         // remove old nodes
        
        *front_ = *q.front_;            // set a front node
        *rear_ = *q.rear_;              // set a rear node
        q_size_ = q.q_size_;            // set a current number of nodes in queue
        MAX_Q_SIZE_ = q.MAX_Q_SIZE_;    // set a queue capacity
    }

    return *this;
} 

template <typename T>
bool Queue<T>::isempty() const
{
    return q_size_ == 0;
}

template <typename T>
bool Queue<T>::isfull() const
{
    return q_size_ == MAX_Q_SIZE_;
}

template <typename T>
int Queue<T>::queuecount() const
{
    return q_size_;
}


// Add item to queue
template <typename T>
bool Queue<T>::enqueue(const Node<T> &item)
{
    if (isfull()) {
        return false;
    } else {
        Node<T> *add = new Node<T>(&item); // create node
        q_size_++;              // increase number of nodes in queue
        if (front_ == nullptr) { // if queue is empty,
            front_ = add;        // place item at front
        } else {
            rear_->next = add;   // else place at rear
        }
        rear_ = add;             // have rear point to new node
        
        return true;
    }
}

// Place front item into item variable and remove from queue
template <typename T>
bool Queue<T>::dequeue(Node<T> &item)
{
    if (front_ == nullptr) {
        return false;
    } else {
        item = front_->item;    // set item to first item in queue
        Node<T> *temp = front_; // save location of first item
        front_ = front_->next;  // reset front to next item
        delete temp;            // delete former first item
        q_size_--;              // decrease number of nodes in queue
        
        if (q_size_ == 0)       // if there is no nodes
            rear_ = nullptr;     // set rear to nullptr
        return true;
    }
}

#endif