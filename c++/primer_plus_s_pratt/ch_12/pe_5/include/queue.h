// queue.h -- interface for a queue
#ifndef QUEUE_H_
#define QUEUE_H_
// #include "node.h"
#include "customer.h"

template <typename T>
class Queue
{
private:
    // Node is a nested structure definition local to this class
    struct Node { T * item_; Node * next_;};

    Node *front_;    // pointer to front of Queue
    Node *rear_;     // pointer to rear of Queue

    const int MAX_Q_SIZE_;      // maximum number of items in Queue
    int q_size_ = 0;            // current number of items in Queue
    
    void remove_nodes();        // use in destructor/copy assignment operator for removing all nodes in queue
    void copy_nodes(const Queue &q);          // use in copy constructor/copy assignment operator for copying all nodes in queue

public:
    Queue(int qs = 10); // create queue with a qs limit
    ~Queue();
    // preemptive definitions to prevent public copying
    Queue(const Queue<T> &q);
    Queue<T> &operator=(const Queue<T> &q);
    
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const T &item);  // add item to end
    bool dequeue(T &item);        // remove item from front
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
    Node * temp;
    while (front_ != nullptr) // while queue is not yet empty
    {
        temp = front_;           // save address of front item
        front_ = front_->next_;    // reset pointer to next item
        delete temp;            // delete former frontA Queue Simulation
    }
}

// help function to copy passing queue
// copies all nodes from passing queue
template <typename T>
void Queue<T>::copy_nodes(const Queue &q)
{
    // Initialize front, rear node
    // front_ = new Node<T>();
    // rear_ = new Node<T>();

    Node * curOrig = front_;             // current node in original queue
    Node * curCopy = q.front_;           // current node from passed queue
    Node * nextTmp = q.front_->next_;    // next node

    // Allocate memory for front node
    curOrig = new Node;

    while (nextTmp != nullptr) {
        // Allocate memory
        curOrig->item_ = new T();
        curOrig->next_ = new Node;
        // Copy values
        *curOrig->item_ = *curCopy->item_;
        // *curOrig->next_ = *nextTmp;

        // Update values
        curOrig = curOrig->next_;
        curCopy = nextTmp;
        nextTmp = nextTmp->next_;
    }
}

template <typename T>
Queue<T>::~Queue()
{
    remove_nodes();
}

// Copy constructor
template <typename T>
Queue<T>::Queue(const Queue &q)
{
    copy_nodes(q);
}

// Copy assignment operator
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &q)
{
    // Check whether self-assignment or not
    if (this != &q) {
        remove_nodes();        
        copy_nodes();

        // *front_ = *q.front_;            // set a front node
        // *rear_ = *q.rear_;              // set a rear node
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
bool Queue<T>::enqueue(const T &item)
{
    if (isfull()) {
        return false;
    } else {
        Node * add = new Node; // create node
        // initialize node by item
        add->item_ = new T();
        *(add->item_) = item;

        q_size_++;                  // increase number of nodes in queue
        if (front_ == nullptr) {    // if queue is empty,
            front_ = new Node;      // init front node
            *front_ = *add;         // place item at front
        } else {
            rear_->next_ = new Node;    // init next node
            *rear_->next_ = *add;       // else place at rear
        }
        rear_ = add;                // have rear point to new node
        
        return true;
    }
}

// Place front item into item variable and remove from queue
template <typename T>
bool Queue<T>::dequeue(T &item)
{
    if (front_ == nullptr) {
        return false;
    } else {
        T * item = front_->item_;    // set item to first item in queue
        Node * temp = front_; // save location of first item
        front_ = front_->next_;  // reset front to next item
        delete temp;            // delete former first item
        q_size_--;              // decrease number of nodes in queue
        
        if (q_size_ == 0)       // if there is no nodes
            rear_ = nullptr;     // set rear to nullptr
        return true;
    }
}

#endif