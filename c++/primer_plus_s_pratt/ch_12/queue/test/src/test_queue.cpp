#include "gtest/gtest.h"
#include "queue/Queue.h"

// Set-up
Queue q{};

TEST(QueueTest, queuecount){
    EXPECT_EQ(q.queuecount(), 0);
}

TEST(Queue, isempty_true){
    EXPECT_EQ(q.isempty(), true);
}

TEST(QueueTest, isfull_false){
    EXPECT_EQ(q.isfull(), false);
}

TEST(QueueTest, enqueue){
    for(int i=0; i<10; ++i){
        EXPECT_EQ(q.enqueue(i), true); // returns true cause there is enough space
        EXPECT_EQ(q.queuecount(),i+1); // returns current amount of items
    }

    EXPECT_EQ(q.enqueue(1), false); // returns false cause there isn't enough space
}

TEST(QueueTest, isfull_true){
    EXPECT_EQ(q.isfull(), true);
}

TEST(QueueTest, isempy_false){
    EXPECT_EQ(q.isempty(), false);
}

TEST(QueueTest, dequeue){
    for(int i=9; i>=0; --i){
        EXPECT_EQ(q.dequeue(i), true); // returns true cause there is enough space
        EXPECT_EQ(q.queuecount(),i); // returns current amount of items
    }

    int a = 1;
    EXPECT_EQ(q.dequeue(a), false); // returns false cause there isn't enough space
}
