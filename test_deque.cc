#include <gtest/gtest.h>
#include "deque.h"

TEST(Deque, Empty) {
  Deque<int> dq;

  /* Should be fully empty */
  EXPECT_EQ(dq.Empty(), true);
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq.PopFront(), std::exception);
}

TEST(Deque, DoubleInsertionBack) {
  Deque<int> dq;

  /* Test some insertions at back */
  dq.PushBack(23);
  dq.PushBack(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq.Back(), 42);
}

TEST(Deque, DoubleInsertionBackFront) {
  Deque<int> dq;

  /* Test some insertions at back and front */
  dq.PushBack(23);
  dq.PushFront(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq.Back(), 23);
}

//  Front() and Back() 
TEST(Deque, FrontBackException) {
  Deque<int> dq;
  EXPECT_THROW(dq.Front(), std::runtime_error);
  EXPECT_THROW(dq.Back(), std::runtime_error);
}

// operator[] 
TEST(Deque, OutOfRange) {
  Deque<int> dq;
  dq.PushBack(10);
  EXPECT_THROW(dq[1], std::out_of_range);
}

// PushFront + PushBack
TEST(Deque, MultiplePush) {
  Deque<int> dq;
  for (int i = 1; i <= 5; i++) dq.PushFront(i); // 5 4 3 2 1
  for (int i = 6; i <= 10; i++) dq.PushBack(i); // 5 4 3 2 1 6 7 8 9 10

  EXPECT_EQ(dq.Size(), 10);
  EXPECT_EQ(dq.Front(), 5);
  EXPECT_EQ(dq.Back(), 10);
}

// PopFront and PopBack
TEST(Deque, PopUntilEmpty) {
  Deque<int> dq;
  for (int i = 1; i <= 5; i++) dq.PushBack(i);

  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(dq.Front(), i);
    dq.PopFront();
  }

  EXPECT_TRUE(dq.Empty());
}


TEST(Deque, ResizeUp) {
  Deque<int> dq;
  for (int i = 0; i < 20; i++) dq.PushBack(i); 
  EXPECT_EQ(dq.Size(), 20);
  EXPECT_EQ(dq.Front(), 0);
  EXPECT_EQ(dq.Back(), 19);
}

// ShrinkToFit
TEST(Deque, Shrink) {
  Deque<int> dq;
  for (int i = 0; i < 16; i++) dq.PushBack(i); 
  for (int i = 0; i < 12; i++) dq.PopFront();  
  dq.ShrinkToFit();
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq.Front(), 12);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

