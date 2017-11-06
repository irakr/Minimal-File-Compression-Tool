#include <exception>
#include "compression-driver.h"
#include "logger.h"

CompressionDriver :: CompressionDriver(int fCount, const char **fileNames)
					: m_Compressor(0)
{
	Log(this, "Started...");
	if(fCount <= 1)
		throw std::invalid_argument("No input file(s) provided.");
	
	for(int i = 0; i < fCount - 1; i++) {
		std::string *s = new std::string(fileNames[i]);
		m_fileNames.push_back(*s);
	}
	/* --- Just to check ---
	std::cout << "Filenames: " << std::endl;
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		std::cout << *i << std::endl;
	*/
}

// Set the provided compression algorithm
void CompressionDriver :: setCompressor(const std::string& algo) {
	// TODO... Find valid compressor and register it
	Log(this, "Started...");
	
	// --- This code is just for initial testing purpose ---
	// --- Later we will add separate module for maintaining registered algorithms ---
	if(algo.compare("Huffman-Coding") == 0)
		m_Compressor = new HuffmanCompressor();
	else
		std::cerr << "[Fatal Error] Invalid compression algorithm \"" << algo << "\"" << std::endl;
}

// Return the name of the registered compression algorithm
std::string CompressionDriver :: getCompressorName() const {
	Log(this, "Started...");
	if(!m_Compressor) {
		std::cerr << "[Fatal Error] Unable to get compression name." << std::endl;
		return "";
	}
	
	return m_Compressor->name();
}

// Compress the file 'file'
void CompressionDriver :: compress(const std::string file) {
	Log(this, "Started...");
	if(!m_Compressor) {
		std::cerr << "[Fatal Error] No compression algorithm registered." << std::endl;
		return; // FIXME... Throw an exception from here
	}
	
	// TODO ... 
	// Open file named 'file'
	// Pass the handle to specific encode() function
	// encode() should return back the compressed file handle
	std::fstream inputf;
	inputf.open(file, std::fstream::in | std::fstream::binary);
	if(!inputf.is_open()) {
		std::cerr << "[Error] The file \"" << file << "\" does not exist." << std::endl;
		return;
	}
	std::fstream& compressedf = m_Compressor->encoder().encode(inputf);
	inputf.close();
	compressedf.close();
}

// Compress all files in m_fileNames
void CompressionDriver :: compressAll() {
	Log(this, "Started...");
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		compress(*i);
}

// Decompress the compressed file 'file'
void CompressionDriver :: decompress(const std::string file) {
	// TODO ... 
	// Open file named 'file'
	// Pass the handle to specific decode() function
	// decode() should return back the decompressed file handle
	std::fstream inputf(file, std::fstream::in | std::fstream::binary);
	if(!inputf.is_open()) {
		std::cerr << "[Error] The file \"" << file << "\" does not exist." << std::endl;
		return;
	}
	std::fstream& decompressedf = m_Compressor->decoder().decode(inputf);
	inputf.close();
	decompressedf.close();
}
	
// Decompress all files in m_fileNames
void CompressionDriver :: decompressAll() {
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		decompress(*i);
}
