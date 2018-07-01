#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <iostream>
#include <climits>
#include <typeinfo>
#include <queue>
#include "logger.h"

// A Huffman tree node as a min heap node
template <class T, class FrequencyValType>
struct MinHeapNode {
	T data;			 // One of the input characters
	FrequencyValType freq;			 // No of occurences of the object type T
	MinHeapNode *left, *right; // Left and right child
	bool m_isInternalNode;

	MinHeapNode() {
		left = right = NULL;
		m_isInternalNode = false;
	}
	MinHeapNode(T data, FrequencyValType freq, bool isInternalNode = false) {
		left = right = NULL;
		this->data = data;
		this->freq = freq;
		m_isInternalNode = isInternalNode;
	}
	~MinHeapNode() {
		delete left;
		delete right;
	}

	// Useful by Huffman tree algorithm
	inline bool isInternalNode() {
		return m_isInternalNode;
	}

	// Utility function to check if this node is leaf
	inline bool isLeaf() {
	    return !left && !right;
	}

	// Print the data members
	// XXX... the member 'T data' must be printable by << operator
	void printContents() {
		std::cout << "-------------------------" << std::endl;
		std::cout << /* "(" << typeid(data).name() << ")" <<" */ "data = " << data
			<< std::endl << /* "(" << typeid(freq).name()  << ")" <<" */ "freq = " << freq
			<< std::endl << "left = " << left
			<< std::endl << "right =" << right
			<< std::endl;
	}
};

// For comparison of two heap nodes (needed in min heap)
template <class T, class U>
struct compare {
	bool operator()(MinHeapNode<T, U>* l, MinHeapNode<T, U>* r) {
		return (l->freq > r->freq); // Change '>' to '<' to make
									// it a Max heap.
	}
};

// This is the Min heap data structure
// !!! So simple it is in C++ !!!
template <class T, class U>
using MinHeap = std::priority_queue<MinHeapNode<T, U>*,
				std::vector<MinHeapNode<T, U>*>, compare<T, U>>;

// Print the contents of each node in the heap
// XXX... Note that this function pops out all the elements in the heap.
// So only use it if u just wanna debug.
template <class T, class U>
void printMinheap(const MinHeap<T, U> &heap) {
	Log_static("Started...");
	std::cout << "------------------" << std::endl;
	MinHeap<T, U> temp = heap;
	while(!temp.empty()) {
		temp.top()->printContents();
		temp.pop();
	}
}

// Preorderly traverse the heap by following the 'left' and 'right' pointer
// structure member of struct MinHeap.
template <class T, class U>
void traversePreorder(MinHeapNode<T, U> *root, const std::string &str) {
	if(root) {
		if(!root->isInternalNode())
			std::cout << root->data << ": " << str << std::endl;
		traversePreorder(root->left, str + "0");
		traversePreorder(root->right, str + "1");
	}
}














////////////////////////////////////////////////////////////////////////
/////////////////////////// CONTAMINATED AREA //////////////////////////
////////////////////////////////////////////////////////////////////////












/*************************************************************
 * We don't need the complexities of maintaining a separate
 * class for MinHeap since it can directly be done using
 * std::priority_queue.
 *************************************************************
 */
#ifdef CRAP

/*	XXX... A severe bug in insertNode() */

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
template <class T, class U>
class MinHeap {
private:

	// Internal array type of MinHeap class
	typedef std::priority_queue<MinHeapNode<T, U>*, std::vector<MinHeapNode<T, U>*>, compare<T, U>> HeapArray;

	// No. of bytes to be reserved by the internal vector 'm_array'
	// at each resizing event.
	//@@@ static const typename HeapArray::size_type PerReservableSize = 2048;

	// Array/vector of minheap node pointers
    HeapArray m_array;

	//@@@ int m_size;    // Current size of min heap
    //@@@ int m_capacity;   // capacity of min heap

	// Allocate and return a new min heap node with given data(symbol)
	// and frequency of the character
	inline MinHeapNode<T, U>* newNode(const T& data, const U& freq, bool internal = false);

	// The standard minHeapify function.
	// idx -> Index of the first node at which the minHeapify()
	// 		  algorithm will begin.
	void minHeapify(int idx);

	// A utility function to swap two min heap nodes by array index
	void swap(int index1, int index2);

public:

	MinHeap() {
		  //@@@ m_array = new HeapArray();
		  //@@@ m_array.reserve(PerReservableSize);
	}

	~MinHeap() {
		//m_array.clear();
	}

	// Returns no of elements
	inline int size() {
		return m_array.size();
	}

	// Returns current capacity
	inline int capacity() {
		return -1;//m_array.capacity();
	}

	// Insert a new node to Min Heap
	void insertNode(const T& data, const U& freq);

	// Print the content of m_array[][]
	void printArray() {
		if(size() == 0)
			throw 20;
		for(auto& i : m_array)
			i.printContents();
	}

	// Returns the 0th MinHeapNode pointer from *m_array[] and removes it
	// from the array. The array is then heapified again.
	MinHeapNode<T, U>* extractMin();

	// Build the min heap into m_array using bottom-up approach
	void buildMinHeap();
};


/* ============================= Definitions ================================ */

// Allocate a new min heap node with given character
// and frequency of the character
template <class T, class U>
inline MinHeapNode<T, U>*
	MinHeap<T, U> :: newNode(const T& data, const U& freq, bool internal)
{
    MinHeapNode<T, U>* temp = new MinHeapNode<T, U>(data, freq, internal);
    return temp;
}

//XXX
// A utility function to swap two min heap nodes by array index
template <class T, class U>
void MinHeap<T, U> :: swap(int index1, int index2) {
	if((index1 < 0) || (index2 < 0))
		throw 20;
    MinHeapNode<T, U> t = m_array[index1];
    m_array[index1] = m_array[index2];
    m_array[index2] = t;
}

// Insert a new node to Min Heap
template <class T, class U>
void MinHeap<T, U> :: insertNode(const T& data, const U& freq) {
    MinHeapNode<T, U> *n = newNode(data, freq);
    int i;

	if(m_array.size() == 0) { // XXX ... Careful with delete() implementation
		m_array.push_back(*n);
		return;
	}

	i = m_array.size();
    while ((i > 0) && (n->freq < m_array.at((i - 1)/2).freq)) {
        m_array[i] = m_array[(i - 1)/2];
        i = (i - 1) / 2;
    }
    m_array[i] = *n;
}

// The standard minHeapify function.
// idx -> Index of the first node at which the minHeapify()
// 		  algorithm will begin.
template <class T, class U>
void MinHeap<T, U> :: minHeapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < m_array.size() &&
        m_array[left].freq < m_array[smallest].freq)
      smallest = left;

    if (right < m_array.size() &&
        m_array[right].freq < m_array[smallest].freq)
      smallest = right;

    if (smallest != idx) {
		swap(smallest, idx);
        minHeapify(smallest);
    }
}

// Returns the 0th MinHeapNode pointer from *m_array[] and removes it
// from the array. The array is then heapified again.
template <class T, class U>
MinHeapNode<T, U>* MinHeap<T, U> :: extractMin() {
	if(size() == 0)
		return NULL;
    MinHeapNode<T, U>* ret = new MinHeapNode<T, U>(m_array.front());
    m_array[0] = m_array[m_array.size() - 1];
    minHeapify(0);
    return ret;
}

// Build the min heap into m_array using bottom using bottom-up approach
template <class T, class U>
void MinHeap<T, U> :: buildMinHeap() {
	if(m_array.size() == 0)
		throw "[Error] Heap size = 0";
    int n = m_array.size() - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(i);
}
#endif /* CRAP */

#endif /* MINHEAP_H_ */
