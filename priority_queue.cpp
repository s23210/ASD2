#include <iostream>
#include <cmath>
#include "priority_queue.h"
#include "node.h"

// konstruktor
PriorityQueue::PriorityQueue(unsigned int capacity) {
	// maksymalna ilość elementów jaka może znajdować się w kolejce
	capacity_ = capacity;
	// ilość elementów w kolejce
	size_ = 0;
	// kopiec liści
	heap_ = new Node[capacity_ + 1];
	// inicjalizacja kopca
	// heap_[0] nie jest używany, więc zostanie zignorowany i zaczynam od 1
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
// zwracanie najmniejszej wartości kopca
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
	// pętla wykonuje się dopóki wstawiony element jest mniejszy niż rodzic kopca, przerywa się gdy dojdzie do heap[0]
	while (heap_[index].value < heap_[index / 2].value && index / 2 != 0) {
		// zamienia miejsca liścia i jego rodzica							  
		Node temp = heap_[index];
		heap_[index] = heap_[index / 2];
		heap_[index / 2] = temp;
		// nowy index to rodzic wstawionego elementu
		index = index / 2;
	}
	return true;
}

// Usuwanie elementu z kopca
bool PriorityQueue::pop() {
	// jeśli kolejka jest pusta, to nie można usunąć elementu
	if (empty())
		return false;
	else {
		// zamiana pierwszego elementu z ostatnim prawym dzieckiem
		heap_[1] = heap_[size_];
		size_--;
		// inicjalizacja indeksu liścia do usunięcia
		int index = 1;
		// index najmniejszego dziecka
		int smaller_child;
		// pętla wykonuje się dopóki heap_[index] nie jest liściem i nowy liść jest mniejszy niż jedno z jego dzieci, przerywa się gdy dojdzie do korzenia
		while (2 * index < size_ && (heap_[index].value < heap_[2 * index].value || heap_[index].value > heap_[2 * index + 1].value)) {
			// ustawienie smaller_child na prawe lub lewe dziecko nowego liścia
			if (heap_[2 * index].value < heap_[2 * index + 1].value)
				smaller_child = 2 * index;
			else
				smaller_child = 2 * index + 1;
			// zamienianie miejscami nowego liścia z mniejszym dzieckiem
			Node temp = heap_[index];
			heap_[index] = heap_[smaller_child];
			heap_[smaller_child] = temp;
			index = smaller_child;
		}
		return true;
	}
}
