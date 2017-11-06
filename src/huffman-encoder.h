/*
 * @file huffman-encoder.h
 *
 * @description
 * This file contains various classes and functions that implements the Huffman encoding
 * algorithm.
 *
 * @note
 * This file and other files related to huffman encoding algorithm implementation contains
 * some code that has been taken from the site
 * http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
 * with few modifications such that it conforms to the needs of our API.
 */

#ifndef HUFFMAN_ENCOD_H_
#define HUFFMAN_ENCOD_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include "compressor-base.h"
#include "min-heap.h"
#include "logger.h"

/// For comparison of two heap nodes (needed in min heap)
struct Compare {
	bool operator () (MinHeapNode* l, MinHeapNode* r) {
		return (l->freq > r->freq);
	}
};

/// Typedef for the huffman tree
/// A short-form for the weirdly long priority_queue type
typedef
	std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, Compare>
	HuffmanTree;

/// Typedef for the symbol-frequency table that will be generated from
/// the input file.
/// It is implemented using std::unordered_map which is a hash mapped
/// key-value storage data structure.
/// Here, symbols are 'key' and their respective frequencies/occurences
/// in the file are the 'values'
typedef
	std::unordered_map<byte, double>
	FrequencyTable;

/// Typedef for the codewords table
/// The symbols are the 'key' and the codewords for each symbols are
/// the 'values'.
/// Note that this type is holding codewords in std::string type and
/// not in an actual bit level codes.
typedef
	std::unordered_map<byte, std::string>
	CodewordTable;

/// Huffman encoder implementation
class HuffmanEncoder : public Encoder {
public:
	HuffmanEncoder() {}
	
	// Compresses the file specified by the fstream and returns another
	// fstream that is a handle to the compressed file.
	// When called, it clears the internal tables that might have been
	// filled by a previous operation.
	// TODO... If the previously compressed file is same then don't clear
	//         the internal tables. Re-use them.
	std::fstream& encode(std::fstream&);
	
private:

	// Build symbol-frequency table
	void buildFrequencyTable(byte*);
	
	// Build a huffman tree as priority queue provided by C++ STL
	HuffmanTree& buildHuffmanTree();
	
	// The symbol-frequency table
	FrequencyTable m_frequencyTable;
	
	// Codewords table
	CodewordTable m_codewordTable;
};

#endif