#include "huffman-decoder.h"
#include "header.h"

byte* HuffmanDecoder :: decode(byte *in_buff, fsize_t *buff_len) {
	Log(this, "Started...");

	m_inBuffSize = *buff_len;

	// This will hold bytes of the compressed data;
	// Header + content
	byte *out_buff = NULL;
	
	// Extract header from file buffer.
	HeaderStruct header;
	
	return NULL;
}
