#include <iostream>

#ifndef HUFFMAN_COMP_H_
#define HUFFMAN_COMP_H_

#include "compressor-base.h"
#include "huffman-encoder.h"
#include "huffman-decoder.h"
#include "min-heap.h"

// Implementation for Huffman coding algorithm
class HuffmanCompressor : public Compressor {
public:
	HuffmanCompressor()	{
		m_name = "Huffman-Coding"; // TODO... Names will be assigned by a separate module
		m_encoder = new HuffmanEncoder();
		m_decoder = new HuffmanDecoder();
	}
	
};

#endif