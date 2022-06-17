#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "node.h"

// klasa PriorityQueue
class PriorityQueue {
private:
  // Sequential representation of the priority queue.
  Node *heap_;

  // Total number of elements that the priority queue can store.
  unsigned int capacity_;

  // Current number of elements in the priority queue.
  unsigned int size_;

  // Override copy constructor and assignment operator in private so we can't
  // use them.
  PriorityQueue(const PriorityQueue &other) {}
  PriorityQueue &operator=(const PriorityQueue &other) {}

public:
  // Constructor initializes heap_ to an array of (capacity_ + 1) size, so
  // that there are at most capacity_ elements in the priority queue.
  PriorityQueue(unsigned int);
  ~PriorityQueue();

  // Returns the number of elements in the priority queue.
  unsigned int size() const;
  // Returns true if the priority queue is empty, and false otherwise.
  bool empty() const;
  // Returns true if the priority queue is full, and false otherwise.
  bool full() const;

  // Returns the max element of the priority queue, but does not remove it.
  Node top() const;
  bool push(Node val);
  bool pop();
};

#endif