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

bool Queue::isempty() const {
    return (items == 0) ? true : false;
}

bool Queue::isfull() const {
    return (items == qsize) ? true : false;
}

int Queue::queuecount() const {
    return items;
}

bool Queue::enqueue(const Item &item) {
    if (items + 1 <= qsize) {
        if (rear == nullptr) {
            rear = new Node({item, nullptr});
        } else {
            if (front == nullptr) {
                front = new Node({item, rear});
            } else {
                front = new Node({item, front});
            }
        }
        ++items;
        return true;
    } else {
        return false;
    }
}

bool Queue::dequeue(Item &item) {
//    if (items != 0) {
        Node *pre_node = nullptr;
        Node *cur_node = front;

        while ((cur_node->next != nullptr) and (items > 2)) {
            if (cur_node->item == item) {
                // if item is in a front node
                if (cur_node == front) {
                    // assign next node to front
                    front = cur_node->next;
                    // free memory
                    cur_node->next = nullptr;
                    delete cur_node;
                } else {
                    // change address of next node
                    pre_node->next = cur_node->next;
                    // free memory
                    cur_node->next = nullptr;
                    delete cur_node;
                }
                // decrease amount of items
                --items;
                return true;
            }
            // assign a new pair of nodes
            pre_node = cur_node;
            cur_node = cur_node->next;
        }

        if (front->item == item) {
            // free memory
            front->next = nullptr;
            delete front;

            --items;

            return true;
        } else if (rear->item == item) {
            // free memory
            delete rear;

            --items;

            return true;
        }

        return false;
}
