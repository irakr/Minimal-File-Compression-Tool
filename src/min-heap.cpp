#include "min-heap.h"

// A utility swap function
template <class T>
static void swap(T *x, T *y) {
	T temp = *x;
	*x = *y;
	*y = temp;
}

// Constructs a heap from the given array 'arr[n]'
MinHeap :: MinHeap(int *arr, int n) {
	*this = MinHeap();
	int i;
	// Copy array first
	for(i = 0; i < n; i++)
		m_arr[i] = arr[i];
	m_size = n;
	// Then heapify it entirely using bottom-up approach
	// Simply using maxHeapify() doesn't consider the entire tree
	for(int i = n / 2 - 1; i >= 0; i--)
		minHeapify(i);
}

// Remove and return the minimum keyed node, i.e., m_arr[0]
int MinHeap :: extractMin() {
	if(m_size <= 0)
		return POS_INF;
	if(m_size == 1) {
		m_size = 0;
		return m_arr[0];
	}
	
	int min = m_arr[0]; // Extract the value to be returned at last
	
	// Remove root and heapify
	m_arr[0] = m_arr[m_size - 1];
	minHeapify(0);
	m_size--;
	
	return min;
}
	
// Insert the node with key 'key' to the heap
int MinHeap :: insertKey(int key) {
	if(m_size >= m_capacity)
		return POS_INF;
	
	// First insert new key at last
	int i = m_size;
	m_arr[i] = key;
	
	// Then fix the min heap if it violates min-heap properties
	while( (i > 0) && (m_arr[i] < m_arr[parent(i)]) ) {
		swap(&m_arr[i], &m_arr[parent(i)]);
		i = parent(i);
	}
	
	m_size++;
	return 0;
}

// Delete the node at index 'i' from the heap
int MinHeap :: deleteKey(int i) {
	if(m_size <= 0)
		return POS_INF;
	
	decreaseKey(i, NEG_INF);
	extractMin();
}
	
// Decrease the value of the key at node 'i' by the value 'newVal'
int MinHeap :: decreaseKey(int i, int newVal) {
	// If you're trying to increment instead of decrement
	if(newVal > m_arr[i])
		return POS_INF;
	
	m_arr[i] = newVal;
	
	// Fix the min heap
	while( (i > 0) && (m_arr[i] < m_arr[parent(i)]) ) {
		swap(&m_arr[i], &m_arr[parent(i)]);
		i = parent(i);
	}
	
	return 0;
}
	
// Heapify the min heap if it violates the properties of a min heap
// starting from the node index 'i'
void MinHeap :: minHeapify(int i) {
	int smallest = i, left = leftChild(i), right = rightChild(i);
	
	// Figure out smallest among 'left child' of i and i itself
	if( (left < m_size) && (m_arr[left] < m_arr[i]) )
		smallest = left;
	// Then figure out smallest among 'right child' of i and previously figured out smallest
	if( (right < m_size) && (m_arr[right] < m_arr[smallest]) )
		smallest = right;
	// Now swap the smallest with ith
	if(smallest != i) {
		swap(&m_arr[i], &m_arr[smallest]);
		minHeapify(smallest);
	}
}
