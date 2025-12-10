#pragma once

#include <iostream>
#include <functional>

#include "types.hpp"

template <
	typename HeapType,
	typename Comparator = std::less<HeapType>
>
class IndexedHeap {
protected:

	int_t capacity = 0_i;
	int_t sz = 0_i;

	std::pair<HeapType, int_t>* data = nullptr;
	int_t* index_to_position = nullptr;

	Comparator comp;

public:

	IndexedHeap() = delete;

	IndexedHeap(int_t cap): 
		capacity(cap), 
		sz(0_i),
		data(new std::pair<HeapType, int_t>[cap]),
		index_to_position(new int_t[cap])
	{
		std::fill(index_to_position, index_to_position + cap, -1_i);
	}

	IndexedHeap(const IndexedHeap& other) {
		capacity = other.capacity;
		sz = other.sz;

		data = new std::pair<HeapType, int_t>[capacity];
		std::copy(other.data, other.data + sz, data);

		index_to_position = new int_t[capacity];
		std::copy(other.index_to_position, other.index_to_position + capacity, index_to_position);
	}

	IndexedHeap(IndexedHeap&& other) noexcept {
		capacity = other.capacity;
		sz = other.sz;
		data = other.data;
		index_to_position = other.index_to_position;

		other.capacity = 0_i;
		other.sz = 0_i;
		other.data = nullptr;
		other.index_to_position = nullptr;
	}

	IndexedHeap& operator=(const IndexedHeap& other) {
		if (this != &other) {
			delete[] data;
			delete[] index_to_position;

			capacity = other.capacity;
			sz = other.sz;

			data = new std::pair<HeapType, int_t>[capacity];
			std::copy(other.data, other.data + sz, data);

			index_to_position = new int_t[capacity];
			std::copy(other.index_to_position, other.index_to_position + capacity, index_to_position);
		}
		return *this;
	}

	IndexedHeap& operator=(IndexedHeap&& other) noexcept {
		if (this != &other) {
			delete[] data;
			delete[] index_to_position;

			capacity = other.capacity;
			sz = other.sz;

			index_to_position = other.index_to_position;
			data = other.data;

			other.capacity = 0_i;
			other.sz = 0_i;
			other.index_to_position = nullptr;
			other.data = nullptr;
		}
		return *this;
	}

	~IndexedHeap() {
		delete[] data;
		delete[] index_to_position;
	}

protected:

	void siftUp(int_t position) {
		while (position > 0_i) {
			int_t parent = (position - 1_i) / 2_i;
			if (comp(data[position].first, data[parent].first)) {
				hswap(position, parent);
				position = parent;
			} 
			else {
				break;
			}
		}
	}

	void siftDown(int_t position) {
		while (position * 2_i + 1_i < sz) {
			int_t left_child = position * 2_i + 1_i;
			int_t right_child = position * 2_i + 2_i;
			int_t swap_candidate = left_child;
			if (right_child < sz && comp(data[right_child].first, data[left_child].first)) {
				swap_candidate = right_child;
			}
			if (comp(data[swap_candidate].first, data[position].first)) {
				hswap(position, swap_candidate);
				position = swap_candidate;
			} 
			else {
				break;
			}
		}
	}

	void hswap(int_t position1, int_t position2) {
		std::swap(data[position1], data[position2]);
		std::swap(index_to_position[data[position1].second], index_to_position[data[position2].second]);
	}

public:

	bool empty() const {
		return sz == 0_i;
	}

	void push(HeapType value, int_t index) {
		if (index < 0_i || index >= capacity) {
			throw std::runtime_error("Incorrect index in .push operation!");
		}
		if (index_to_position[index] != -1_i) {
			changePriority(value, index);
		}
		else {
			data[sz] = std::make_pair(value, index);
			index_to_position[index] = sz;
			siftUp(sz++);
		}
	}

	std::pair<HeapType, int_t> top() const {
		if (empty()) {
			throw std::runtime_error("Empty heap!");
		}
		return data[0_i];
	}

	std::pair<HeapType, int_t> extract() {
		if (empty()) {
			throw std::runtime_error("Empty heap!");
		}
		hswap(0_i, sz - 1_i);
		--sz;
		siftDown(0_i);
		index_to_position[data[sz].second] = -1_i;
		return data[sz];
	}

	void changePriority(HeapType new_priority, int_t index) {
		int_t position = index_to_position[index];
		if (position == -1_i) {
			throw std::runtime_error("No such index in the heap!");
		}
		data[position].first = new_priority;
		siftUp(position);
		siftDown(position);
	}
};