#include <iostream>
#include <fstream>
#include <vector>

#ifndef COMPR_ENGINE_H_
#define COMPR_ENGINE_H_

#include "huffman-encoder.h"

class CompressionEngine {
public:
	CompressionEngine(int, const char**);
	
	~CompressionEngine() {
		if(!m_fileNames.empty())
			m_fileNames.clear();
	}
	
	// Set the required compression algorithm
	void setCompressor(Compressor &compressor) {
		m_Compressor = &compressor;
	}
	
	// Compress the file 'file'
	void compress(std::string);
	
	// Compress all files in m_fileNames
	void compressAll();
	
private:
	std::vector<std::string> m_fileNames;
	// TODO... Also keep file handles
	
	// Registered compression algorithms
	Compressor *m_Compressor;
};

#endif
