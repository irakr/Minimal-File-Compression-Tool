#include <iostream>
#include <climits>

#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#define POS_INF INT_MAX 	// +ve Infinity value
#define NEG_INF INT_MIN 	// -ve Infinity value

using namespace std;

// A binary max heap implementation
class MaxHeap {

protected:
	
	int *m_arr; 		// Array containing heap elements/keys
	int m_capacity; 	// Max size of heap
	int m_size; 		// Current heap size
	
	// Heapify the max heap m_arr[i] if it violates the properties of a max heap
	// starting from the node index 'i'
	void maxHeapify(int i);
	
	// Heapify the array 'arr[n]' which may be an ordinary array that does
	// not have the properties of a max heap starting from the index 'i'
	void maxHeapify(int i, int *arr, int n);

public:
	MaxHeap() {
		m_capacity = 100;
		m_arr = new int[100];
		m_size = 0;
	}
	
	MaxHeap(int capacity) {
		m_capacity = capacity;
		m_arr = new int[capacity];
		m_size = 0;
	}
	
	// Constructs a heap from the given array 'arr[n]'
	MaxHeap(int *arr, int n);
	
	// Get index of the parent node of i
	static int parent(int i) {
		return (i / 2);
	}
	
	// Get index of the left child of i
	static int leftChild(int i) {
		return (2 * i + 1);
	}
	
	// Get index of the right child of i
	static int rightChild(int i) {
		return (2 * i + 2);
	}
	
	// Return the max/root element
	int getMax() {
		return (m_size > 0) ? m_arr[0] : POS_INF;
	}
	
	// Return as well as remove the max keyed node
	int extractMax();
	
	// Insert the node with key 'key' to the heap
	int insertKey(int key);
	
	// Delete the 'key' node from the heap
	int deleteKey(int key);
	
	// Decrease the value of the key at node 'i' by the value 'newVal'
	int decreaseKey(int i, int newVal);
	
	// Simply prints the internal array
	void printArray();
	
	// **** XXX A good design approach ****
	// Build a max heap out of the given array 'arr'
	static MaxHeap &buildMaxHeap(int *arr, int n);
};

#endif