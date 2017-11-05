#include "compression-engine.h"

CompressionEngine :: CompressionEngine(int fCount, const char **fileNames)
					: m_Compressor(0)
{
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
void CompressionEngine :: setCompressor(const std::string&) {
	// TODO... Find valid compressor and register it
	
}

// Compress the file 'file'
void CompressionEngine :: compress(const std::string file) {
	if(!m_Compressor) {
		std::cerr << "[Fatal Error] No compression algorithm registered." << std::endl;
		return; // FIXME... Throw an exception from here
	}
	
	// TODO ... 
	// Open file named 'file'
	// Pass the handle to specific encode() function
	// encode() should return back the compressed file handle
	std::fstream inputf(file);
	std::fstream& compressedf = m_Compressor->Encoder().encode(inputf);
}

// Compress all files in m_fileNames
void CompressionEngine :: compressAll() {
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		compress(*i);
}

// Decompress the compressed file 'file'
void CompressionEngine :: decompress(const std::string file) {
	// TODO ... 
	// Open file named 'file'
	// Pass the handle to specific decode() function
	// decode() should return back the decompressed file handle
	std::fstream inputf(file);
	std::fstream& decompressedf = m_Compressor->Decoder().decode(inputf);
}
	
// Decompress all files in m_fileNames
void CompressionEngine :: decompressAll() {
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		decompress(*i);
}
