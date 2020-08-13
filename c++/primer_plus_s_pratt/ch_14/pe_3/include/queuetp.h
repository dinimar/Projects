#ifndef QUEUE_TP_H_
#define QUEUE_TP_H_

#include <valarray>
#include <vector>

template <typename T>
class Queue
{
private:
    // static const int Q_SIZE = 10;
    // class scope definitions
    // Node is a nested structure definition local to this class
    struct Node
    {
        T t;
        struct Node *next;
    };
    // private class members
    Node *mFront = nullptr; // pointer to front of Queue
    Node *mRear = nullptr;  // pointer to rear of Queue
    int mItems = 0;         // current number of items in Queue
    const int M_Q_SIZE;     // maximum number of items in Queue
public:
    Queue(int qs = 10) : M_Q_SIZE(qs){}; // create queue with a qs limit
    ~Queue();
    bool isEmpty() const;
    bool isFull() const;
    int queueCount() const;
    bool enqueue(const T &t); // add item to end
    bool dequeue(T &t);       // remove item from front
};

template <typename T>
bool Queue<T>::isEmpty() const
{
    return mItems == 0 ? true : false;
}

template <typename T>
bool Queue<T>::isFull() const
{
    return mItems == M_Q_SIZE ? true : false;
}

template <typename T>
int Queue<T>::queueCount() const
{
    return mItems;
}

template <typename T>
bool Queue<T>::enqueue(const T &t)
{
    if (mItems == M_Q_SIZE)
    {
        return false;
    }
    else
    {
        if (mFront == nullptr)
        {
            mFront = new Node();
            mFront->t = t;
        }
        else if (mRear == nullptr)
        {
            mRear = new Node();
            mRear->t = t;

            mFront->next = mRear;
        }
        else
        {
            // Create tmp pointer
            Node *tmp = new Node();
            tmp->t = t;
            // Set next item in rear object
            mRear->next = tmp;
            // Reassign mRear
            mRear = tmp;
        }

        ++mItems;
        return true;
    }
}

template <typename T>
bool Queue<T>::dequeue(T &t)
{
    if (mItems == 0)
    {
        return false;
    }
    else
    {
        // Assign mFront to buffer object
        t = mFront->t;
        if (mItems > 2)
        {
            // Create tmp pointer
            Node *tmp = mFront->next;
            // Reassign mFront
            mFront = tmp;
        }
        else if (mItems == 2)
        {
            // Reassign mFront to mRear
            mFront = mRear;
            // Set mRear empty
            mRear = nullptr;
        }
        else if (mItems == 1)
        {
            // Set mFront empty
            mFront = nullptr;
        }

        --mItems;
        return true;
    }
}


template <typename T>
Queue<T>::~Queue()
{
    Node * tmp;
    
    while (mFront != nullptr) // while queue is not empty
    {
        tmp = mFront; //
        mFront = mFront->next; //
        delete tmp; //
    }
}

// template <typename T>
// class Queue<T *>
// {
//     bool enqueue(const T *t)
//     {
//         if (mItems == M_Q_SIZE)
//         {
//             return false;
//         }
//         else
//         {
//             if (mFront == nullptr)
//             {
//                 mFront = new Node();
//                 mFront->t = *t;
//             }
//             else if (mRear == nullptr)
//             {
//                 mRear = new Node();
//                 mRear->t = *t;

//                 mFront->next = mRear;
//             }
//             else
//             {
//                 // Create tmp pointer
//                 Node *tmp = new Node();
//                 tmp->t = *t;
//                 // Set next item in rear object
//                 mRear->next = tmp;
//                 // Reassign mRear
//                 mRear = tmp;
//             }

//             ++mItems;
//             return true;
//         }
//     }

//     bool dequeue(const T *t)
//     {
//         if (mItems == 0)
//         {
//             return false;
//         }
//         else
//         {
//             // Assign mFront to buffer object
//             t = new T;
//             *t = mFront->t;

//             if (mItems > 2)
//             {
//                 // Create tmp pointer
//                 Node *tmp = mFront->next;
//                 // Reassign mFront
//                 mFront = tmp;
//             }
//             else if (mItems == 2)
//             {
//                 // Reassign mFront to mRear
//                 mFront = mRear;
//                 // Set mRear empty
//                 mRear = nullptr;
//             }
//             else if (mItems == 1)
//             {
//                 // Set mFront empty
//                 mFront = nullptr;
//             }

//             --mItems;
//             return true;
//         }
//     }
// };
#endif