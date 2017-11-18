#include "huffman-encoder.h"
#include <exception>
#include <climits>
#include <cstring>

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
std::fstream& HuffmanEncoder :: encode(std::fstream &ifile, std::string &ofilename) {
	//@std::cout << "In HuffmanEncoder::encode()" << std::endl;
	Log(this, "Started...");

	std::fstream *ofile = 0; // Output file

	// Parse the text file and generate a symbol-frequency table
	// TODO ...

	if(!ifile.is_open())
		throw 10;

	m_fileSize = getFileSize(ifile);
	//std::cout << "File size = " << m_fileSize << std::endl;

	// Open output file. The size will be obviously less than or impossibly
	// equal to the input file size.
	ofile = new std::fstream();
	ofile->open(ofilename, std::fstream::in | std::fstream::binary);

	byte *raw_byte_buff = new byte[m_fileSize + 1];
	ifile.read((char*)raw_byte_buff, m_fileSize);
	raw_byte_buff[m_fileSize - 1] = 0; // Append null at the end because read() doesn't

	//std::cout << raw_byte_buff << std::endl << "No. of bytes read = " << ifile.gcount() << std::endl;

	buildFrequencyTable(raw_byte_buff);  //OK
	buildHuffmanTree();					//OK

	return *ofile;
}

// Build symbol-frequency table
void HuffmanEncoder :: buildFrequencyTable(byte *buffer) {
	//@std::cout << "In HuffmanEncoder::buildFrequencyTable()" << std::endl;
	Log(this, "Started...");

	std::cout << "File size: " << m_fileSize << std::endl;

	// Compute the frequencies of each byte in buffer and generate the
	// symbol-frequency map
	int i, j;	//, freq_len = 0;
	double frequency[UCHAR_MAX + 1] = {0}; // 2^8-1 = 255 = UCHAR_MAX different symbols
	memset(frequency, 0, UCHAR_MAX);
	for(i = 0; buffer[i] != '\0'; i++) {
		j = buffer[i]; // Just to typecast 'byte' to 'int'
		++(frequency[j]);
	}

	/****** Test *******
	for(i = 0; i <= UCHAR_MAX; i++) {
		std::cout << "frequency[" << i << "] = " << frequency[i] << std::endl;
	}
	****/

	// Fill the original symbol-frequency map by filtering out symbols
	// that does not exist(or frequency[symbol(i)] = 0)
	for(i = 0; i <= UCHAR_MAX; i++) {
		if(frequency[i] > 0) {
			byte b = i;
			(*m_frequencyTable)[b] = frequency[i];
		}
	}


	for(auto& x : *m_frequencyTable)
		x.second = (x.second / m_fileSize) * 100;

	/****** Test *******
	for(auto& x : *m_frequencyTable)
		std::cout << x.first << ":" << x.second << std::endl;
	//std::cout << (*m_frequencyTable)[(byte)'0'] << std::endl;
	****/

	//asm("nop");
}

// Build a huffman tree as priority queue provided by C++ STL
// Builds the 'm_huffmanTree' data structure
void HuffmanEncoder :: buildHuffmanTree() {
	Log(this, "Started...");

	MinHeapNode<byte, double> *left, *right, *top;

	// Create a min heap & inserts all characters of data[]
	//@@@ MinHeap<byte, double> minHeap;
	for(auto& x : *m_frequencyTable)
		m_huffmanTree->push(new MinHeapNode<byte, double>(x.first, x.second));
	//printMinheap(*m_huffmanTree);

	// Iterate while size of heap doesn't become 1
	while (m_huffmanTree->size() != 1)
	{
		// Extract the two minimum freq items from min heap
		left = m_huffmanTree->top();
		m_huffmanTree->pop();

		right = m_huffmanTree->top();
		m_huffmanTree->pop();

		// Create a new internal node with frequency equal to the
		// sum of the two nodes frequencies. Make the two extracted
		// node as left and right children of this new node. Add
		// this node to the min heap.
		// 0x00 is a special value for internal nodes.
		top = new MinHeapNode<byte, double>(0x00, left->freq + right->freq, true);
		top->left = left;
		top->right = right;
		m_huffmanTree->push(top);
	}
	//printMinheap(*m_huffmanTree);
	traversePreorder(m_huffmanTree->top(), "");
}

// Generate code word table
void HuffmanEncoder :: buildCodewordTable(MinHeapNode<byte, double>* root, const std::string& str)
{
	/* --- This code is unlikely to happen unless someone really forgets ---
	 * -- Avoided! Since it will unnecessarily occupy each recursion stack --
	 *
	 * If prerequisites doesn't exist
	if(!m_codewordTable || !m_frequencyTable || !m_huffmanTree)
		throw 10;
	*/

	if (!root)
		return;

	if (!root->isInternalNode())
		(*m_codewordTable)[root->data] += str;

	buildCodewordTable(root->left, "0");
	buildCodewordTable(root->right, "1");
}
