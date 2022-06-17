#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "node.h"

// klasa PriorityQueue
class PriorityQueue {
private:
  Node *heap_;
  unsigned int capacity_;
  unsigned int size_;

public:
  PriorityQueue(unsigned int);
  ~PriorityQueue();

  unsigned int size() const;
  bool empty() const;
  bool full() const;
  Node top() const;
  bool push(Node val);
  bool pop();
};

#endif