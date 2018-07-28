/*
 * header.cpp
 */

#include <cstring>
#include <cmath>
#include "header.h"
#include "logger.h"
#include "huffman-encoder.h"
#include "utils/BitVector.h"
//@ #include "bit-manip.h"


// This function computes the absolute size of the header structure,
// without considering the structure padding bytes.
size_t get_header_size(HeaderStruct* header) {
    Log_static("Started...");
    if(!header)
        return -1;

    // XXX... Note that this code will work incorrectly if
    // this function is called for some other input file
    // within a lifetime of the program.
    // So I recommend replace the below 3 lines of code with just:
    // size_t ret = 0;
    size_t ret = 0;

    ret = sizeof(int) + sizeof(size_t) * 2 + 1; // header_size + original_size + compressed_size + nSyms
    ret += header->nSyms * sizeof(*header->cw_table); // Total summation of sizes of each cw_table entry.
    return ret;
}

// Convert string of binary digits to uint8_t binary format.
// XXX Currently works only for 8-bit binary numbers.
static uint8_t str2bits(const std::string &str) {
    Log_static("Started...");

    uint8_t ret = 0,
            l = str.length()-1,
            i = 0;

    while(i < str.length()) {
        if(str[i] == '1')
            ret |= (0x1 << l);
        else if(str[i] == '0')
            ret &= ~(0x1 << l);
        --l; ++i;
    }

    return ret;
}

// Set parameters of the header struct 'hdr' from
// the codeword_table_map 'cw_table'.
void build_header(HeaderStruct *hdr, CodewordTable &cw_table) {
    Log_static("Started...");
    if(!hdr)
        return;

    memset(hdr, 0, sizeof(*hdr));

    hdr->nSyms = cw_table.size();
    hdr->cw_table = new HeaderStruct::codeword_table[hdr->nSyms];

    // Migrate the CodewordTable contents to codeword_table contents
    int i = 0;
    for(auto &x : cw_table) {
        hdr->cw_table[i].symbol = x.first;
        hdr->cw_table[i].codeword = str2bits(x.second);
        hdr->cw_table[i].nBits = x.second.length();
        ++i;
    }
}

// Computes and returns the estimated size of the compressed data.
// It is the sum of all codeword_table.nBits.
// Returns the size in terms of bits.
// XXX...NOTE: At first call to this function, @freqsym_map must be passed.
size_t get_compressed_size(HeaderStruct * const hdr, const FrequencyTable &freqsym_map) {
    Log_static("Started...");
    if(!hdr)
        return -1;

    size_t ret;
    double temp1 = 0, temp2 = 0;

    // XXX... Note that this calculates the size in terms of bits.
    // Convert it to bytes before returning.
    for(uint8_t i = 0; i < hdr->nSyms; i++) {
        temp1 = ( (double)freqsym_map.at(hdr->cw_table[i].symbol) * hdr->original_size ) / 100.0; // % to number
        temp2 += (double)hdr->cw_table[i].nBits * temp1;
    }

    temp2 /= 8;
    ret = ceil(temp2);
    return ret;
}

// Dump the header structure to the output buffer.
void dump_header(HeaderStruct* header, byte* buff) {
    Log_static("Started...");
    if(!header || !buff)
        return; // TODO... Create a NullArgumentException class

    byte *temp = buff;

    // FIXME... Examine in tests properly.
    memcpy((int*)buff, (int*)(&header->header_size), sizeof(int));

    // XXX...Important
    // Move buff ptr as the same no of bytes as the distance between
    // header.header_size and header.original_size.
    // This allows buff to take the exact image of the header structure
    // including structure padding bytes.
    // This is done all other similar steps below.
    buff += (uint64_t)((uint64_t)&header->original_size - (uint64_t)&header->header_size);

    memcpy((size_t*)buff, (size_t*)(&header->original_size), sizeof(size_t));
    buff += (uint64_t)((uint64_t)&header->compressed_size - (uint64_t)&header->original_size);
    memcpy((size_t*)buff, (size_t*)(&header->compressed_size), sizeof(size_t));
    buff += (uint64_t)((uint64_t)&header->nSyms - (uint64_t)&header->compressed_size);

    buff[0] = header->nSyms;
    buff += (uint64_t)((uint64_t)&header->cw_table - (uint64_t)&header->nSyms);

    size_t cw_table_size = sizeof(*header->cw_table) * header->nSyms;
    memcpy(buff, header->cw_table, cw_table_size);

}

// Returns the codeword of the symbol
// If the function is called consecutively for the same symbol then
// the cached pointer will be returned. This increases efficiency.
static HeaderStruct::codeword_table *get_cw_entry(HeaderStruct *header, uchar_t *symbol) {
    uint8_t i;
    static uchar_t sym = 0xff; // 0xff is unlikely to come.
    static HeaderStruct::codeword_table *cache = NULL;

    // Error check
    if(!header || !symbol)
        return NULL;

    // Cache hit
    if(sym == *symbol)
        return cache;

    // Cache miss
    for(i = 0; i < header->nSyms; i++) {
        if((sym = header->cw_table[i].symbol) == *symbol)
            break;
    }
    cache = header->cw_table + i;
    return cache;
}

// Dump the compressed content to the output buffer.
void dump_content(HeaderStruct* header, byte *ibuff, size_t ibuff_size, byte* obuff) {
    Log_static("Started...");
    if(!header || !ibuff || !obuff)
        return; // TODO... Create a NullArgumentException class

    // Push the bits into buff according to
    // the codeword_table in the header.
    HeaderStruct::codeword_table *cw_entry;
    //@ BitStream bit_stream(header->compressed_size); // FIXME... Incorrect argument
    BitVector bit_vector;
    uint32_t i;
    for(i = 0; i < ibuff_size; i++) {
        cw_entry = get_cw_entry(header, ibuff+i);

        try {
            bit_vector.appendByte(cw_entry->codeword, cw_entry->nBits);
        } catch(std::overflow_error *e) {
        	Log_static(e->what());
        	exit(1);
            break;
        }

    }

    ::memcpy(obuff, bit_vector.toCharArray(), bit_vector.getNumberOfBytes());

}
