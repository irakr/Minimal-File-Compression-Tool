#include <iostream>
#include <fstream>

#ifndef HUFFMAN_ENCOD_H_
#define HUFFMAN_ENCOD_H_

#include "compressor-base.h"
#include "min-heap.h"

// A single
class HuffmanEncoder : public Encoder {
public:
	HuffmanEncoder() {}
	std::fstream& encode(std::fstream&);
};

#endif