#include "compression-engine.h"

CompressionEngine :: CompressionEngine(int fCount, const char **fileNames) {
	for(int i = 0; i < fCount - 1; i++) {
		std::string *s = new std::string(fileNames[i]);
		m_fileNames.push_back(*s);
	}
	std::cout << "Filenames: " << std::endl;
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		std::cout << *i << std::endl;
		
}

// Compress the file 'file'
void CompressionEngine :: compress(std::string file) {
	// TODO ... 
	// Open file named 'file'
	// Pass the handle to specific encode() function
	// encode() should return back the compressed file handle
	std::fstream inputf;
	std::fstream compressedf;
}
	
// Compress all files in m_fileNames
void CompressionEngine :: compressAll() {
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		compress(*i);
}