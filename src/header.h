/*
 * header.h
 * 
 * Header structure of the compressed file.
 */

#ifndef HEADER_H_
#define HEADER_H_

#include "zz_types.h"
#include "huffman-encoder.h"

/* Header structure definition  */
struct HeaderStruct {
    //@@@ TODO ... size_t original_size, compressed_size;
    
    uint8_t nSyms; // Num of symbols in the file.
    
    // An inner struct:- This is a codeword table which
    // contains 3 columns:
    // Symbol | codeword | No_of_bits_from_lsb
    // XXX...A hash table implementation would make it much faster.
    struct codeword_table {
        uchar_t symbol;
        uint8_t codeword;
        uint8_t nBits;
    } *cw_table;
    
    // Compressed content... Stored separately. 
    //uchar_t *content;
};

// This function is different from the sizeof() operator.
// For a pointer variable, the sizeof() operator only considers the
// size of the pointer variable itself rather than the memory block
// it is pointing. So using sizeof() won't give the actual content size
// of a structure.
// Therefore, this function computes the the content wise size of the
// structure.
size_t get_header_size(HeaderStruct*);

// Set parameters of the header struct 'hdr' from
// the codeword_table_map 'cw_table'.
void build_header(HeaderStruct *hdr, CodewordTable &cw_table);

// Computes and returns the estimated size of the compressed data.
// It is the sum of all codeword_table.nBits.
size_t get_compressed_size(HeaderStruct *hdr);

// Dump the header structure to the output buffer.
void dump_header(HeaderStruct*, byte*);

// Dump the compressed content to the output buffer.
void dump_content(HeaderStruct*, byte*, size_t, byte*);

#endif
