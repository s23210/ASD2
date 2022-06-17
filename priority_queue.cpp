#include <iostream>
#include <cmath>
#include "priority_queue.h"
#include "node.h"

// konstruktor
PriorityQueue::PriorityQueue(unsigned int capacity) {
	capacity_ = capacity;
	size_ = 0;
	heap_ = new Node[capacity_ + 1];
	// inicjalizacja kopca
	for (int i = 0; i < capacity_; i++)
		heap_[i] = 0;
}

// destruktor
PriorityQueue::~PriorityQueue() {
	delete[] heap_;
}
// zwraca ilość elementów w kopcu
unsigned int PriorityQueue::size() const {
	return size_;
}
// zwraca true jeśli kopiec jest pusty, false w przeciwnym wypadku
bool PriorityQueue::empty() const {
	return !size_;
}
// zwraca true jeśli kopiec jest pełny, false w przeciwnym wypadku
bool PriorityQueue::full() const {
	return (size_ == capacity_);
}
int log2(int val) { // helper function to decide when new level needs to be made
	return log(val) / log(2);
};
// drukowanie kolejki priorytetowej
void PriorityQueue::print() const {
	double level = 0.0;
	std::cout << "Ordered Priority Queue:\n";
	for (int i = 1; i < size_ + 1; i++) {
		// adds a break to the tree to maintain binary heap structure albiet floating left
		if (log2(i) >= level + 1) {
			level++;
			std::cout << std::endl;
		}
		std::cout << heap_[i].value << " ";
	}
}
// zwracanie najmniejszej wartości kopca ?
Node PriorityQueue::top() const {
	return heap_[1];
}

// dodawanie elementu do kopca
bool PriorityQueue::push(Node val) {
	// sprawdzenie czy kopiec jest pelny
	if (full())
		return false;
	heap_[++size_] = val;
	int index = size_;
	// loop while inserted node greater than heap parent, &&: stop if reached heap[0]
	while (heap_[index].value < heap_[index / 2].value && index / 2 != 0) {							  
		Node temp = heap_[index]; // if true, swap inserted node & parent
		heap_[index] = heap_[index / 2];
		heap_[index / 2] = temp;
		index = index / 2; // set new parent index
	}
	return true;
}

// Usuwanie elementu z kopca
bool PriorityQueue::pop() {
	// jeśli kolejka jest pusta, to nie można usunąć elementu
	if (empty())
		return false;
	else {
		heap_[1] = heap_[size_]; // replace highest priority with bottom-right most leaf in heap (newNode)
		size_--;
		int index = 1;	  // initialize index value to point to node we just inserted into highest priority position (newNode)
		int larger_child; // variable to fill with index of largest child of node (to trickle it down)
		// while not a leaf node AND newNode is less than one of its children, bubble newNode down
		while (2 * index < size_ && (heap_[index].value < heap_[2 * index].value || heap_[index].value > heap_[2 * index + 1].value)) {
			// if/else: set larger_child to right or left of newNode
			if (heap_[2 * index].value < heap_[2 * index + 1].value)
				larger_child = 2 * index;
			else
				larger_child = 2 * index + 1;
			// Swap values with newNode and larger child
			Node temp = heap_[index];
			heap_[index] = heap_[larger_child];
			heap_[larger_child] = temp;
			index = larger_child;
		}
		return true;
	}
}
