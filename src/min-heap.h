#include <iostream>
#include <climits>

#ifndef MINHEAP_H_
#define MINHEAP_H_

#define POS_INF INT_MAX 	// +ve Infinity value
#define NEG_INF INT_MIN 	// -ve Infinity value

// A binary min heap implementation
class MinHeap {

protected:
	static int m_defaultCapacity; // Default capacity =100
	
	int *m_arr; 		// Array containing heap elements/keys
	int m_capacity; 	// Max size of heap
	int m_size; 		// Current heap size
	
	// Heapify the min heap if it violates the properties of a min heap
	// starting from the node index 'i'
	void minHeapify(int i);
	
public:
	
	MinHeap(int capacity) {
		m_capacity = capacity;
		m_arr = new int[capacity];
		m_size = 0;
	}
	
	// Constructs a min-heap from the given array 'arr[n]'
	MinHeap(int *arr, int n);
	
	// Get index of the parent node of i
	int parent(int i) {
		return (i / 2);
	}
	
	// Get index of the left child of i
	int leftChild(int i) {
		return (2 * i + 1);
	}
	
	// Get index of the right child of i
	int rightChild(int i) {
		return (2 * i + 2);
	}
	
	// Return the min/root element
	int getMin() {
		return (m_size > 0) ? m_arr[0] : NEG_INF;
	}
	
	// Return as well as remove the minimum keyed node
	int extractMin();
	
	// Insert the node with key 'key' to the heap
	int insertKey(int key);
	
	// Delete the 'key' node from the heap
	int deleteKey(int key);
	
	// Decrease the value of the key at node 'i' by the value 'newVal'
	int decreaseKey(int i, int newVal);
};

#endif