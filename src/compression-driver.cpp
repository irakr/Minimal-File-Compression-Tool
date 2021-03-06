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
	// --- Yea it is currently hard-coded kinda ---
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
		Log(this, "[Fatal Error] Unable to get compression name.");
		return "";
	}

	return m_Compressor->name();
}

// Just a trivial wrapper for getting file length
static inline fsize_t getFileSize(std::fstream& f) {
	Log_static("Started...");

	if(!f.is_open())
		return -1;
	f.seekg(0, f.end);
	fsize_t file_size = f.tellg(); // This may also return -1
	f.seekg(0, f.beg);
	return file_size;
}

// Compress the file 'file'
void CompressionDriver :: compress(std::string &ifilename) {
	Log(this, "Started...");
	if(!m_Compressor) {
		Log(this, "[Fatal Error] No compression algorithm registered.");
		return; // FIXME... Throw an exception from here
	}

	std::cout << "Input File: " << ifilename << std::endl;

	// Output filename
	// (XXX) For now this is the auto generated output file name
	std::string ofilename = ifilename + ".compressed";

	// TODO ...
	// Open file named 'file'
	// Pass the handle to specific encode() function
	// encode() should return back the compressed file handle
	std::fstream inputf;
	inputf.open(ifilename, std::fstream::in | std::fstream::binary);
	if(!inputf.is_open()) {
		Logf(this, "[Error] The file \"%s\" does not exist.", ifilename.c_str());
		throw "fstream::open() failed.";
	}

	fsize_t file_size = getFileSize(inputf);
    std::cout << "Size: " << file_size << " bytes" << std::endl;
    
	// Read bytes from input file
	byte *in_data_byte_buff = new byte[file_size + 1];
	inputf.read((char*)in_data_byte_buff, file_size);
	in_data_byte_buff[file_size] = 0; // Append null at the end because read() doesn't
	//std::cout << "file_buff: " << in_data_byte_buff << std::endl;

	// Get the compressed byte stream
	byte* compressed_buff = m_Compressor->encoder().encode(in_data_byte_buff, &file_size);
	if(!compressed_buff) {
	    // TODO... Cleanup code like should be placed somewhere else systematically.
	    Logf(this, "Error: File too small to be compressed.");
	    delete[] in_data_byte_buff;
	    inputf.close();
	    return;
	}
	std::cout << "Compressed size = " << file_size << " bytes" << std::endl;

	// Open output file. The size will be obviously less than or impossibly
	// equal to the input file size;
	// Then write the compressed byte stream to it.
	std::fstream outputf;
	outputf.open(ofilename, std::fstream::out | std::fstream::binary);
	outputf.write((const char*)compressed_buff,
		file_size);

	inputf.close();
	outputf.close();
}

// Compress all files in m_fileNames
void CompressionDriver :: compressAll() {
	Log(this, "Started...");
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		compress(*i);
}

// Decompress the compressed file 'file'
void CompressionDriver :: decompress(std::string &ifilename) {
	Log(this, "Started...");
	if(!m_Compressor) {
		Log(this, "[Fatal Error] No compression algorithm registered.");
		return; // FIXME... Throw an exception from here
	}

	std::cout << "Input File: " << ifilename << std::endl;

	// Output filename
	// (XXX) For now this is the auto generated output file name
	std::string ofilename = ifilename + ".orig";

	// TODO ...
	// Open file named 'file'
	// Pass the handle to specific decode() function
	// decode() should return back the decompressed file handle
	std::fstream inputf(ifilename, std::fstream::in | std::fstream::binary);
	if(!inputf.is_open()) {
		std::cerr << "[Error] The file \"" << ifilename << "\" does not exist." << std::endl;
		return;
	}
	
	fsize_t file_size = getFileSize(inputf);
    std::cout << "Size: " << file_size << " bytes" << std::endl;
    
	// Read bytes from input file
	byte *in_data_byte_buff = new byte[file_size + 1];
	inputf.read((char*)in_data_byte_buff, file_size);
	in_data_byte_buff[file_size] = 0; // Append null at the end because read() doesn't
	//std::cout << "file_buff: " << in_data_byte_buff << std::endl;

	// Get the compressed byte stream
	byte* decompressed_buff = m_Compressor->decoder().decode(in_data_byte_buff, &file_size);
	if(!decompressed_buff) {
	    // TODO... Cleanup code like should be placed somewhere else systematically.
	    Logf(this, "Error: Invalid file format.");
	    delete[] in_data_byte_buff;
	    inputf.close();
	    return;
	}
	std::cout << "Decompressed size = " << file_size << " bytes" << std::endl;

	// Open output file. The size will be obviously less than or impossibly
	// equal to the input file size;
	// Then write the compressed byte stream to it.
	std::fstream outputf;
	outputf.open(ofilename, std::fstream::out | std::fstream::binary);
	outputf.write((const char*)decompressed_buff,
		file_size);

	inputf.close();
	outputf.close();
}

// Decompress all files in m_fileNames
void CompressionDriver :: decompressAll() {
	for(std::vector<std::string>::iterator i = m_fileNames.begin(); i != m_fileNames.end(); i++)
		decompress(*i);
}
