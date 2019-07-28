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

int Queue::queuecount() const {
    return qsize;
}
