//
// Created by dinir on 7/27/19.
//
#include <iostream>
using std::cout;
#include "Queue.h"

Queue::Queue(int qs):qsize(qs) {
    front = rear = nullptr;
    items = 0;
}

Queue::~Queue() {}

bool Queue::isempty() const {}

bool Queue::isfull() const {
    return (items == qsize) ? true : false;
}

int Queue::queuecount() const {
    return items;
}

bool Queue::dequeue(Item &item) {}

bool Queue::enqueue(const Item &item) {
    if (items + 1 <= qsize) {
        rear = new Node({item, nullptr});
        ++items;
        return true;
    } else {
        return false;
    }
}
