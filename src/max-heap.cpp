#include <exception>
#include "max-heap.h"

// A utility swap function
template <class T>
static void swap(T *x, T *y) {
	T temp = *x;
	*x = *y;
	*y = temp;
}

// Constructs a heap from the given array 'arr[n]'
MaxHeap :: MaxHeap(int *arr, int n) {
	*this = MaxHeap();
	int i;
	// Copy array first
	for(i = 0; i < n; i++)
		m_arr[i] = arr[i];
	m_size = n;
	// Then heapify it entirely using bottom-up approach
	// Simply using maxHeapify() doesn't consider the entire tree
	for(int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(i);
}
	
// Remove and return the maximum keyed node, i.e., m_arr[0]
int MaxHeap :: extractMax() {
	if(m_size <= 0)
		return POS_INF;
	if(m_size == 1) {
		m_size = 0;
		return m_arr[0];
	}
	
	int max = m_arr[0]; // Extract the value to be returned at last
	
	// Remove root and heapify
	m_arr[0] = m_arr[m_size - 1];
	maxHeapify(0);
	m_size--;
	
	return max;
}
	
// Insert the node with key 'key' to the heap
int MaxHeap :: insertKey(int key) {
	if(m_size >= m_capacity)
		return POS_INF;
	
	// First insert new key at last
	int i = m_size;
	m_arr[i] = key;
	
	// Then fix the max heap if it violates max-heap properties
	while( (i > 0) && (m_arr[i] < m_arr[parent(i)]) ) {
		swap(&m_arr[i], &m_arr[parent(i)]);
		i = parent(i);
	}
	
	m_size++;
	return 0;
}

// Delete the node at index 'i' from the heap
int MaxHeap :: deleteKey(int i) {
	if(m_size <= 0)
		return POS_INF;
	
	decreaseKey(i, NEG_INF);
	extractMax();
}
	
// Decrease the value of the key at node 'i' by the value 'newVal'
int MaxHeap :: decreaseKey(int i, int newVal) {
	// If you're trying to increment instead of decrement
	if(newVal > m_arr[i])
		return POS_INF;
	
	m_arr[i] = newVal;
	
	// Fix the max heap
	while( (i > 0) && (m_arr[i] < m_arr[parent(i)]) ) {
		swap(&m_arr[i], &m_arr[parent(i)]);
		i = parent(i);
	}
	
	return 0;
}
	
// Heapify the max heap if it violates the properties of a max heap
// starting from the node index 'i'
void MaxHeap :: maxHeapify(int i) {
	int largest = i, left = leftChild(i), right = rightChild(i);
	
	// Figure out largest among 'left child' of i and i itself
	if( (left < m_size) && (m_arr[left] > m_arr[i]) )
		largest = left;
	// Then figure out largest among 'right child' of i and previously figured out largest
	if( (right < m_size) && (m_arr[right] > m_arr[largest]) )
		largest = right;
	// Now swap the largest with ith
	if(largest != i) {
		swap(&m_arr[i], &m_arr[largest]);
		maxHeapify(largest);
	}
}

// Heapify the array 'arr[n]' if it violates the properties of a max heap
// starting from the node index 'i'
void MaxHeap :: maxHeapify(int i, int *arr, int n) {
	int largest = i, left = leftChild(i), right = rightChild(i);
	
	// Figure out largest among 'left child' of i and i itself
	if( (left < n) && (arr[left] > arr[i]) )
		largest = left;
	// Then figure out largest among 'right child' of i and previously figured out largest
	if( (right < n) && (arr[right] > arr[largest]) )
		largest = right;
	// Now swap the largest with ith
	if(largest != i) {
		swap(&arr[i], &arr[largest]);
		maxHeapify(largest, arr, n);
	}
}

// Simply prints the internal array
void MaxHeap :: printArray() {
	for(int i = 0; i < m_size; i++)
		cout << m_arr[i] << endl;
}

// Build a max heap out of the given array 'arr'
MaxHeap& MaxHeap :: buildMaxHeap(int *arr, int n) {
	if(!arr)
		throw (new exception());
		
	/*
	for(int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(i);
	*/
}