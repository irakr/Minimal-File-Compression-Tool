#include <iostream>

#ifndef HUFFMAN_COMP_H_
#define HUFFMAN_COMP_H_

#include "compressor-base.h"
#include "huffman-encoder.h"
#include "huffman-decoder.h"
#include "min-heap.h"

// A Compressor implementation for Huffman coding algorithm
class HuffmanCompressor : public Compressor {
public:
	HuffmanCompressor() {
		m_encoder = new HuffmanEncoder();
		m_decoder = new HuffmanDecoder();
	}
	
};

#endif