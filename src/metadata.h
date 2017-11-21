/*
 * @file metadata.h
 *
 * @Description
 * This file contains classes and data structures to represent handle
 * manipulate and compression protocol headers.
 *
 * @XXX
 * The protocol implemented by this module does not follow any standard
 * header formats.
 */
#ifndef METADATA_H_
#define METADATA_H_

#include <iostream>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include "compressor-base.h" // also includes <base-class.h>
#include "logger.h"

// This is a very important formula which computes and returns a byte size
// enough to store the 'l' bit sized codewords
#define compute_word_len(l)		\
		ceil( ((double)(l) / 8.0) )

/**** XXX ***
 * The order of structure members here have significant meaning.
 * All dynamically allocated(pointer) member variables of the structs are
 * declared at the last members.
 */

/// Low-level data structure for symbol-codeword
/// corresponding to 'CodewordTable'
struct codeword_map_struct {
    byte sym;   // A symbol of single byte

    // Bit level codeword
    struct {
        // No. of bits in 'cw' that are actually part of the codeword.
        // Counting starts from LSB to MSB since it is only compatible
        // in a little-endian CPU.
        fsize_t n_bits;

        // Pointer to a memory location which has enough bytes to pack and
        // store the codeword bits.
        // XXX... Allocated by compute_word_len(n_bits) macro only
        byte *cw;
    } codeword;

    codeword_map_struct() {
        memset(&sym, 0, 1);
        memset(&codeword, 0, sizeof(codeword));
    }
    ~codeword_map_struct() {
        if(codeword.cw)
            delete[] codeword.cw;
    }
};

/// Header/Metadata format for Compressed file
struct header_struct {

// 8-bit unique number for a compression algorithm
#define HUFFMAN_CODEC       1
#define ARITHMETIC_CODEC    2
#define LZW_CODEC           3
#define RUN_LENGTH          4
    // Compression algorithm
    int8_t compression_algo;

    // File's state
    enum state : int8_t {UNDEFINED=-1, COMPRESSED=0, UNCOMPRESSED=1} file_state;

	// Actual total size of header_struct which includes sizes of internal
	// dynamically allocated data members too.
	fsize_t header_size;

	// Total size of the compressed buffer (header + content)
	fsize_t compressed_size;

    // Codeword table
    fsize_t n_syms; // No. of symbols
    codeword_map_struct *cw_map;   // Table of symbol vs codewords(1d-array)

    header_struct() {
        compression_algo = 0;
        file_state = UNDEFINED;
        n_syms = 0;
		header_size = 0;
        cw_map = NULL;
    }
    ~header_struct() {
        //if(cw_map)
        //    delete cw_map;
    }

	/* Get the total size of this structs */
	fsize_t size() {
		return header_size;
	}

    /* Just a utility function to test correct values */
    void print_cw_map() {
        if(!cw_map)
            throw new std::exception();
        Log_static("Printing cw_map");
        for(fsize_t i = 0; i < n_syms; ++i) {
            std::cout << "[" << cw_map[i].sym
                    << ", " << std::hex << (int)cw_map[i].codeword.cw[0]
                    << std::dec << "]" << std::endl;
        }

    }
};

/// Build the metadata structure
struct header_struct* init_header(std::unordered_map<byte, std::string>*);

// Builds a compressed form of the byte according to the header parameters
byte* get_compressed_byte_stream(byte *in_buff, fsize_t buff_len, struct header_struct *header);

// Lookup for the codeword of 'sym' in 'header.cw_map[]' field
// and return a pointer to the particular entry.
struct codeword_map_struct*
    get_cw_entry(byte *sym, struct header_struct* header);

// Copy every byte and even bytes of pointer members of the header_struct
void hdr_2_bytes(byte *out, struct header_struct *hdr);

void hex_dump(byte *buff, fsize_t len);

#endif
