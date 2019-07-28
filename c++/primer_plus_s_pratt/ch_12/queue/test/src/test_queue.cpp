#include "gtest/gtest.h"
#include "queue/Queue.h"

TEST(QueueTest, QueueCount){
    Queue q{};
    EXPECT_EQ(q.queuecount(), 10);
}
