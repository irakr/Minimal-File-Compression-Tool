#include <iostream>
#include <fstream>

#ifndef HUFFMAN_DECOD_H_
#define HUFFMAN_DECOD_H_

#include "compressor-base.h"
#include "min-heap.h"

// A single
class HuffmanDecoder : public Decoder {
public:
	HuffmanDecoder() {}
	std::fstream& decode(std::fstream&);
};

#endif