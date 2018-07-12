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
#include "zz_types.h"
#include "compressor-base.h"
#include "min-heap.h"
//#include "header.h"
#include "logger.h"

#define HUFFMAN_BLOCK_SIZE      8

/// Typedef for a simple min-heap based huffman tree type
typedef
	MinHeap<byte, double>
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
	HuffmanEncoder() {
		m_frequencyTable = new FrequencyTable();
		m_huffmanTree = new HuffmanTree();
		m_codewordTable = new CodewordTable();
	}
	~HuffmanEncoder() {
		if(m_frequencyTable)
			delete m_frequencyTable;
		if(m_codewordTable)
			delete m_codewordTable;
		if(m_huffmanTree)
			delete m_huffmanTree;
	}

	// Compresses the file specified by the fstream and returns another
	// fstream that is a handle to the compressed file.
	// When called, it clears the internal tables that might have been
	// filled by a previous operation.
	// TODO... If the previously compressed file is same then don't clear
	//         the internal tables. Re-use them.
	byte* encode(byte *in_buff, fsize_t *buff_len);

private:


	// Build symbol-frequency table 'm_frequencyTable'
	void buildFrequencyTable(byte*);

	// Build a huffman tree 'm_huffmanTree' as a
	// priority queue provided by C++ STL
	void buildHuffmanTree();

	// Generate code word table 'm_codewordTable'
	void buildCodewordTable();

	// Generates the compressed content portion only from the
	// input buffer and returns it.
	byte* getCompressedContent(byte *in_buff);

	// Size of the input buffer
	fsize_t m_inBuffSize;

	// The symbol-frequency table built by 'buildFrequencyTable()'
	// XXX... This value is changed to a pointer type because there was
	// an unknown issue when it was a value variable.
	FrequencyTable *m_frequencyTable;

	// The HuffmanTree built by 'buildHuffmanTree()'
	HuffmanTree *m_huffmanTree;

	// Codewords table built by buildCodewordTable()
	CodewordTable *m_codewordTable;
};

#endif
