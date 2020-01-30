#ifndef NODE_H_
#define NODE_H_

template <typename T>
class Node
{
private:
    T *item_;
    Node *next_;
public:
    Node();
    Node(T *item);
    const T& item() const;
    void item(const T& item);
    ~Node();
};

// default constructor
// initializes a pointer to next node as nullptr, item is not initialized
template <typename T>
Node<T>::Node()
{
    next_ = nullptr;
}

// constructror with item argument
// sets item_ to item without next_ node
template <typename T>
Node<T>::Node(T *item)
{
    *item_ = *item;
    next_ = nullptr;
}

// Item's getter
// Returns a node item
template <typename T>
const T& Node<T>::item() const
{
    return item_;
}

// Item's setter
// Sets an item value
template <typename T>
void Node<T>::item(const T& item)
{
    item_ = item;
}

// Destructor
template <typename T>
Node<T>::~Node()
{
    delete item_;
    next_ = nullptr;
}

#endif