#include "gtest/gtest.h"
#include "queue/Queue.h"

// Set-up
Queue q{};

TEST(QueueTest, queuecount){
    EXPECT_EQ(q.queuecount(), 0);
}

TEST(QueueTest, isfull_false){
    EXPECT_EQ(q.isfull(), false);
}

TEST(QueueTest, enqueue){
    for(int i=0; i<10; i++){
        EXPECT_EQ(q.enqueue(i), true); // returns true cause there is enough space
        EXPECT_EQ(q.queuecount(),i+1); // returns current amount of items
    }

    EXPECT_EQ(q.enqueue(1), false); // returns false cause there isn't enough space
}

TEST(QueueTest, isfull_true){
    EXPECT_EQ(q.isfull(), true);
}
