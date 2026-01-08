#include <gtest/gtest.h>

#include "heap.hpp" 

using Heap = IndexedHeap<int>;

TEST(IndexedHeap, CapacityConstructor) {
    Heap heap(5);

    EXPECT_TRUE(heap.empty());
    for (int i = 0; i < 5; i++) {
        heap.push(i, i);
    }
    EXPECT_FALSE(heap.empty());
}

TEST(IndexedHeap, CopyConstructor) {
    Heap h1(5);
    h1.push(3, 0);
    h1.push(1, 1);
    h1.push(4, 2);

    Heap h2(h1);

    EXPECT_EQ(h1.top().first, h2.top().first);
    EXPECT_EQ(h1.top().second, h2.top().second);

    auto old_top = h1.top();
    h2.extract();
    EXPECT_EQ(h1.top(), old_top);
}

TEST(IndexedHeap, MoveConstructor) {
    Heap h1(5);
    h1.push(10, 0);
    h1.push(5, 1);

    Heap h2(std::move(h1));

    EXPECT_EQ(h2.top().first, 5);
    EXPECT_ANY_THROW(h1.top());
}

TEST(IndexedHeap, CopyAssignment) {
    Heap h1(5);
    h1.push(3, 0);
    h1.push(1, 1);

    Heap h2(5);
    h2.push(10, 2);

    h2 = h1;

    EXPECT_EQ(h2.top().first, h1.top().first);
    h2.extract();
    EXPECT_NE(h2.top().first, h1.top().first);
}

TEST(IndexedHeap, MoveAssignment) {
    Heap h1(5);
    h1.push(3, 0);
    h1.push(7, 1);

    Heap h2(5);
    h2 = std::move(h1);

    EXPECT_EQ(h2.top().first, 3);
    EXPECT_ANY_THROW(h1.top());
}

TEST(IndexedHeap, PushAndTop) {
    Heap heap(4);
    heap.push(5, 0);
    heap.push(2, 1);
    heap.push(7, 2);

    EXPECT_EQ(heap.top().first, 2);
    EXPECT_EQ(heap.top().second, 1);
}

TEST(IndexedHeap, ExtractMaintainsHeapProperty) {
    Heap heap(5);
    heap.push(10, 0);
    heap.push(2, 1);
    heap.push(5, 2);

    auto first = heap.extract();
    EXPECT_EQ(first.first, 2);
    EXPECT_EQ(heap.top().first, 5);
}

TEST(IndexedHeap, ChangePriorityUpAndDown) {
    Heap heap(5);
    heap.push(10, 0);
    heap.push(20, 1);
    heap.push(30, 2);

    heap.changePriority(5, 1);
    EXPECT_EQ(heap.top().second, 1);
    EXPECT_EQ(heap.top().first, 5);

    heap.changePriority(40, 1);
    EXPECT_EQ(heap.top().first, 10);
}

TEST(IndexedHeap, PushInvalidIndex) {
    Heap heap(3);
    EXPECT_ANY_THROW(heap.push(1, 5));
}

TEST(IndexedHeap, ExtractFromEmpty) {
    Heap heap(2);
    EXPECT_ANY_THROW(heap.extract());
}

TEST(IndexedHeap, TopFromEmpty) {
    Heap heap(2);
    EXPECT_ANY_THROW(heap.top());
}