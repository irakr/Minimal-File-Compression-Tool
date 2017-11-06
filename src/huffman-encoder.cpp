#include "huffman-encoder.h"
#include <exception>

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

// XXX... Currently supports only ascii text files
// Compresses the file specified by the fstream and returns
// another fstream that is a handle to the compressed file
std::fstream& HuffmanEncoder :: encode(std::fstream &ifile) {
	//@std::cout << "In HuffmanEncoder::encode()" << std::endl;
	Log(this, "Started...");
	
	// Parse the text file and generate a symbol-frequency table
	// TODO ...
	if(!ifile.is_open())
		throw 10;
	
	// Get file size
	fsize_t file_size = getFileSize(ifile);
	
	//std::cout << "File size = " << file_size << std::endl;
	
	byte *raw_byte_buff = new byte[file_size + 1];
	ifile.read((char*)raw_byte_buff, file_size);
	raw_byte_buff[file_size - 1] = 0; // Append null at the end because read() doesn't
	
	//std::cout << raw_byte_buff << std::endl << "No. of bytes read = " << ifile.gcount() << std::endl;
	buildFrequencyTable(raw_byte_buff);
	
	return ifile;
}

// Build symbol-frequency table
void HuffmanEncoder :: buildFrequencyTable(byte *buffer) {
	//@std::cout << "In HuffmanEncoder::buildFrequencyTable()" << std::endl;
	Log(this, "Started...");
	
	// TODO ...
}

// Build a huffman tree as priority queue provided by C++ STL
HuffmanTree& HuffmanEncoder :: buildHuffmanTree() {
	struct MinHeapNode *left, *right, *top;
	/*
	// Create a min heap & inserts all characters of data[]
	HuffmanTree minHeap;
	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	// Iterate while size of heap doesn't become 1
	while (minHeap.size() != 1)
	{
		// Extract the two minimum freq items from min heap
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		// Create a new internal node with frequency equal to the
		// sum of the two nodes frequencies. Make the two extracted
		// node as left and right children of this new node. Add
		// this node to the min heap
		// '$' is a special value for internal nodes, not used
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	*/
}