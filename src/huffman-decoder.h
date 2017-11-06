#include <iostream>
#include <fstream>

#ifndef HUFFMAN_DECOD_H_
#define HUFFMAN_DECOD_H_

#include "compressor-base.h"
#include "min-heap.h"

// Huffman decoder implementation
class HuffmanDecoder : public Decoder {
public:
	HuffmanDecoder() {}
	
	// Decompresses the file specified by the fstream and returns
	// another fstream that is a handle to the decompressed file
	std::fstream& decode(std::fstream&);
};

#endif