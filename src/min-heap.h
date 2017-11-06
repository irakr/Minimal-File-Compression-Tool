#include <iostream>
#include <climits>

#ifndef MINHEAP_H_
#define MINHEAP_H_

// A Huffman tree node as a min heap node
struct MinHeapNode
{
	char data;			 // One of the input characters
	unsigned freq;			 // Frequency of the character
	MinHeapNode *left, *right; // Left and right child

	MinHeapNode(char data, unsigned freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

#endif