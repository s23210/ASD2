#include <iostream>
#include <cmath> //used to compute log(x)
#include "priority_queue.h"
#include "node.h"

PriorityQueue::PriorityQueue(unsigned int capacity) {
	capacity_ = capacity;
	size_ = 0;
	heap_ = new Node[capacity_+1];
	for(int i = 0; i < capacity_; i++) heap_[i] = NULL; //initialize heap_
}
  // Destructor of the class PriorityQueue. It deallocates the memory space 
  // allocated for the priority queue. 
PriorityQueue::~PriorityQueue() {
	delete [] heap_;
}
// Returns the number of elements in the priority queue.
unsigned int PriorityQueue::size() const {
	return size_;
}
// Returns true if the priority queue is empty, and false otherwise.
bool PriorityQueue::empty() const {
	return !size_;
}
 // Returns true if the priority queue is full, and false otherwise.
bool PriorityQueue::full() const {
	return (size_ == capacity_);
}
int log2(int val) { //helper function to decide when new level needs to be made
	return log(val) / log(2);
};
// Prints the contents of the priority queue.
void PriorityQueue::print() const {
	double level = 0.0;
	std::cout << "Ordered Priority Queue:\n";
	for(int i = 1; i < size_+1; i++) { 
		//adds a break to the tree to maintain binary heap structure albiet floating left
		if(log2(i)>=level + 1) { 
			level++;
			std::cout << std::endl;
		}
		std::cout << heap_[i].value << " ";
	}
}
 // Returns the top element of the priority queue, but does not remove it.
Node PriorityQueue::top() const {
	return heap_[1];
}
 // Inserts value into the priority queue. Returns true if successful, and 
 // false otherwise. Assume no duplicate entries will be entered.
bool PriorityQueue::push(Node val) {
	if(full()) return false; //full queue
	heap_[++size_] = val;
	int index = size_;
	while(heap_[index].value < heap_[index/2].value && index/2 != 0) { //loop while inserted node greater than heap parent, &&: stop if reached heap[0]
		Node temp = heap_[index]; //if true, swap inserted node & parent
		heap_[index] = heap_[index/2];
		heap_[index/2] = temp;
		index = index/2; //set new parent index
	}
	return true;
}
 // Removes the top element with the maximum value (priority) and rearranges 
 // the resulting heap. Returns true if successful, and false otherwise.
bool PriorityQueue::pop() {
	if(empty()) return false; // you can't "dequeue" an empty queue...
	else {
		heap_[1] = heap_[size_]; //replace highest priority with bottom-right most leaf in heap (newNode)
		size_--;
		int index = 1; //initialize index value to point to node we just inserted into highest priority position (newNode)
		int larger_child; //variable to fill with index of largest child of node (to trickle it down)
		//while not a leaf node AND newNode is less than one of its children, bubble newNode down
		while (2*index < size_ && (heap_[index].value < heap_[2*index].value || heap_[index].value > heap_[2*index + 1].value)) {
			//if/else: set larger_child to right or left of newNode
			if (heap_[2*index].value > heap_[2*index+1].value) larger_child = 2*index; 
			else larger_child = 2*index+1;
			//Swap values with newNode and larger child
			Node temp = heap_[index]; 
			heap_[index] = heap_[larger_child];
			heap_[larger_child] = temp;
			index = larger_child;
		}
		return true;
	}	 
}
