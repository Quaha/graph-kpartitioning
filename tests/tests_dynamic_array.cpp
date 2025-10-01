#include <gtest/gtest.h>

#include "dynamic_array.hpp"

TEST(DynamicArray, DefaultConstructor) {
    DynamicArray<int> arr;

    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.begin(), arr.end());
}

TEST(DynamicArray, SizeConstructor) {
    DynamicArray<int> arr(5);

    EXPECT_EQ(arr.size(), 5);
}

TEST(DynamicArray, SizeValueConstructor) {
    DynamicArray<int> arr(4, 7);

    EXPECT_EQ(arr.size(), 4);
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], 7);
    }
}

TEST(DynamicArray, CopyConstructor) {
    DynamicArray<int> arr1(3, 42);
    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), arr1.size());
    for (size_t i = 0; i < arr1.size(); i++) {
        EXPECT_EQ(arr2[i], arr1[i]);
    }

    arr2[1] = 99;
    EXPECT_EQ(arr1[1], 42);
    EXPECT_EQ(arr2[1], 99);
}

TEST(DynamicArray, MoveConstructor) {
    DynamicArray<int> arr1(3, 42);
    EXPECT_EQ(arr1.size(), 3);

    DynamicArray<int> arr2(std::move(arr1));

    EXPECT_EQ(arr2.size(), 3);
    for (size_t i = 0; i < arr2.size(); i++) {
        EXPECT_EQ(arr2[i], 42);
    }

    EXPECT_EQ(arr1.size(), 0);
    EXPECT_EQ(arr1.begin(), arr1.end());
}

TEST(DynamicArray, CopyAssignment) {
    DynamicArray<int> arr1(3, 5);
    DynamicArray<int> arr2(2, 99);

    arr2 = arr1;

    EXPECT_EQ(arr2.size(), arr1.size());
    for (size_t i = 0; i < arr2.size(); i++) {
        EXPECT_EQ(arr2[i], arr1[i]);
    }

    arr2[0] = 77;
    EXPECT_EQ(arr1[0], 5);
    EXPECT_EQ(arr2[0], 77);
}

TEST(DynamicArray, CopyAssignmentItself) {
    DynamicArray<int> arr(3, 5);

    arr = arr;

    EXPECT_EQ(arr.size(), 3);
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], 5);
    }

    arr[0] = 77;
    EXPECT_EQ(arr[0], 77);
}

TEST(DynamicArray, MoveAssignment) {
    DynamicArray<int> arr1(4, 10);
    DynamicArray<int> arr2(2, 99);

    arr2 = std::move(arr1);

    EXPECT_EQ(arr2.size(), 4);
    for (size_t i = 0; i < arr2.size(); i++) {
        EXPECT_EQ(arr2[i], 10);
    }

    EXPECT_EQ(arr1.size(), 0);
    EXPECT_EQ(arr1.begin(), arr1.end());
}

TEST(DynamicArray, MoveAssignmentItself) {
    DynamicArray<int> arr(3, 5);

    arr = std::move(arr);

    EXPECT_EQ(arr.size(), 3);
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], 5);
    }

    arr[0] = 77;
    EXPECT_EQ(arr[0], 77);
}

TEST(DynamicArray, OperatorIndexNonConst) {
    DynamicArray<int> arr(3, 7);

    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[1], 7);
    EXPECT_EQ(arr[2], 7);

    arr[1] = 42;
    EXPECT_EQ(arr[1], 42);
}

TEST(DynamicArray, OperatorIndexConst) {
    const DynamicArray<int> arr(3, 99);

    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 99);
}

TEST(DynamicArray, DataNonConst) {
    DynamicArray<int> arr(3, 5);

    int* raw_ptr = arr.data();
    EXPECT_NE(raw_ptr, nullptr);

    EXPECT_EQ(raw_ptr[0], 5);
    EXPECT_EQ(raw_ptr[1], 5);
    EXPECT_EQ(raw_ptr[2], 5);

    raw_ptr[0] = 77;
    EXPECT_EQ(arr[0], 77);
}

TEST(DynamicArray, DataConst) {
    const DynamicArray<int> arr(3, 11);

    const int* raw_ptr = arr.data();
    EXPECT_NE(raw_ptr, nullptr);

    EXPECT_EQ(raw_ptr[0], 11);
    EXPECT_EQ(raw_ptr[1], 11);
    EXPECT_EQ(raw_ptr[2], 11);
}

TEST(DynamicArray, IterateNonConst) {
    DynamicArray<int> arr(5);

    int value = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        *it = ++value;
    }

    value = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], ++value);
    }
}

TEST(DynamicArray, IterateConst) {
    const DynamicArray<int> arr(3, 7);

    int counter = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        EXPECT_EQ(*it, 7);
        counter++;
    }

    EXPECT_EQ(counter, 3);
}

TEST(DynamicArray, RangeBasedFor) {
    DynamicArray<int> arr(4);

    int value = 10;
    for (auto& x : arr) {
        x = value++;
    }

    value = 10;
    for (auto x : arr) {
        EXPECT_EQ(x, value++);
    }
}

TEST(DynamicArray, ResizeSmaller) {
    DynamicArray<int> arr(5);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i + 1;
    }

    arr.resize(3);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArray, ResizeLarger) {
    DynamicArray<int> arr(3);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i + 1;
    }

    arr.resize(5);

    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArray, ResizeLargerWithValue) {
    DynamicArray<int> arr(2, 1);

    arr.resize(5, 42);

    EXPECT_EQ(arr.size(), 5);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 42);
    EXPECT_EQ(arr[3], 42);
    EXPECT_EQ(arr[4], 42);
}

TEST(DynamicArray, ResizeSmallerWithValue) {
    DynamicArray<int> arr(5, 99);

    arr.resize(2, 123);

    EXPECT_EQ(arr.size(), 2);

    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 99);
}

TEST(DynamicArray, AssignLargerSize) {
    DynamicArray<int> arr(2, 5);

    arr.assign(4, 42);

    EXPECT_EQ(arr.size(), 4);
    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], 42);
    }
}

TEST(DynamicArray, AssignSmallerSize) {
    DynamicArray<int> arr(5, 7);

    arr.assign(2, 99);

    EXPECT_EQ(arr.size(), 2);

    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 99);
}

TEST(DynamicArray, Clear) {
    DynamicArray<int> arr(4, 99);

    EXPECT_EQ(arr.size(), 4);

    arr.clear();

    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.data(), nullptr);

    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.data(), nullptr);
}