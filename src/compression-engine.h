#include <iostream>
#include <fstream>
#include <vector>

#ifndef COMPR_ENGINE_H_
#define COMPR_ENGINE_H_

#include "huffman-compressor.h"

class CompressionEngine {
public:
	// Get file names from command line arguments
	CompressionEngine(int, const char**);
	
	~CompressionEngine() {
		if(!m_fileNames.empty())
			m_fileNames.clear();
	}
	
	// Set the provided compression algorithm
	void setCompressor(const std::string&);
	
	// Return the name of the registered compression algorithm
	std::string getCompressorName() const;
	
	// Compress the file 'file'
	void compress(const std::string);
	
	// Compress all files in m_fileNames
	void compressAll();
	
	// Decompress the compressed file 'file'
	void decompress(const std::string);
	
	// Decompress all files in m_fileNames
	void decompressAll();
	
private:
	std::vector<std::string> m_fileNames;
	
	// TODO... (Maybe)Keep file handles too
	
	// Registered compression algorithm
	Compressor *m_Compressor;
};

#endif
