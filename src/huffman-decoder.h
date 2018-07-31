#ifndef HUFFMAN_DECOD_H_
#define HUFFMAN_DECOD_H_

#include <iostream>
#include <fstream>
#include "compressor-base.h"
#include "min-heap.h"

// Huffman decoder implementation
class HuffmanDecoder : public Decoder {
public:
	HuffmanDecoder() {}

	// Decompresses the file specified by the fstream and returns
	// another fstream that is a handle to the decompressed file
	byte* decode(byte*, fsize_t*);

private:

    // Size of the input buffer
	fsize_t m_inBuffSize;
};

#endif
