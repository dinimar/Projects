//
// Created by dinir on 7/27/19.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

typedef int Item;

class Queue
{
private:
    static const int Q_SIZE = 10;
    // class scope definitions
    // Node is a nested structure definition local to this class
    struct Node { Item item; struct Node * next;};
    // private class members
    Node * front; // pointer to front of Queue
    Node * rear; // pointer to rear of Queue
    int items; // current number of items in Queue
    const int qsize; // maximum number of items in Queue
public:
    Queue(int qs = Q_SIZE); // create queue with a qs limit
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &item); // add item to end
    bool dequeue(Item &item); // remove item from front
};

#endif //QUEUE_QUEUE_H
