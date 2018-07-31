#include <exception>
#include <climits>
#include <cstring>
#include <functional>
#include "huffman-encoder.h"
#include "header.h"

// XXX... Currently supports only ascii text files.
// Compresses the file specified by the fstream and returns
// another fstream that is a handle to the compressed file
byte* HuffmanEncoder :: encode(byte *in_buff, fsize_t *buff_len) {
	Log(this, "Started...");

	m_inBuffSize = *buff_len;

	// This will hold bytes of the compressed data;
	// Header + content
	byte *out_buff = NULL;

	try {
		// All the 3 statements below must be in this sequence only.
		buildFrequencyTable(in_buff);			// (OK)
		buildHuffmanTree();						// (OK)
		buildCodewordTable();					// (OK)
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl
			<< "[.......Rethrowing exception]" << std::endl;
		throw (new std::exception(e));
	}

	// Build the file header.
	HeaderStruct header;
	build_header(&header, *m_codewordTable);
	header.header_size = get_header_size(&header);
	header.original_size = m_inBuffSize;
	header.compressed_size = get_compressed_size(&header, *m_frequencyTable);
	
	// Build the compressed data(payload)
	size_t out_size = header.header_size + header.compressed_size + PREFIX_LEN;
	
	// If compression not useful.
	if(out_size >= m_inBuffSize)
	    return NULL;
	// Else continue encoding...
	out_buff = new byte[out_size];
	::memcpy((byte*)out_buff, (byte*)PREFIX_STR, PREFIX_LEN);
	
	dump_header(&header, out_buff + PREFIX_LEN);
    dump_content(&header, in_buff, *buff_len, out_buff + header.header_size);
	
	// Return compressed file buffer and its size.
	*buff_len = out_size;
	return out_buff;
}

// Build symbol-frequency table
void HuffmanEncoder :: buildFrequencyTable(byte *buffer) {
	//@std::cout << "In HuffmanEncoder::buildFrequencyTable()" << std::endl;
	Log(this, "Started...");

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
		x.second = (x.second / m_inBuffSize) * 100;

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
	//traversePreorder(m_huffmanTree->top(), "");
}

// TODO TODO TODO TODO
// Generate code word table
void HuffmanEncoder :: buildCodewordTable()
{
	Log(this, "Started...");

	/* --- This code is unlikely to happen unless someone really forgets ---
	 * -- Avoided! Since it will unnecessarily occupy each recursion stack --
	 *
	 * If prerequisites doesn't exist
	if(!m_codewordTable || !m_frequencyTable || !m_huffmanTree)
		throw 10;
	*/

	// Huffman tree parser lambda
	std::function<void(MinHeapNode<byte, double>*, const std::string&)>
		huffmanTreeParser;
	huffmanTreeParser =
			[&](MinHeapNode<byte, double>* root, const std::string &codeword) {
				if(root) {
					if(!root->isInternalNode()) {
						(*m_codewordTable)[root->data] = codeword;
						//@@@ std::cout << root->data << ": " << codeword << std::endl;
					}
					huffmanTreeParser(root->left, codeword + "0");
					huffmanTreeParser(root->right, codeword + "1");
				}
			};

	huffmanTreeParser(m_huffmanTree->top(), "");

	/* Just testing
	for(auto &x : *m_codewordTable)
		std::cout << x.first << " : " << x.second << std::endl;
	*/
}
