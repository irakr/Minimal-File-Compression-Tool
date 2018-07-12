/*
 * header.cpp
 */

#include <cstring>
#include "header.h"
#include "logger.h"
#include "huffman-encoder.h"
#include "bit-manip.h"

size_t get_header_size(HeaderStruct* header) {
    Log_static("Started...");
    if(!header)
        return -1;
    
    // XXX... Note that this code will work incorrectly if
    // this function is called for some other input file 
    // within a lifetime of the program.
    // So I recommend replace this portion with:
    // size_t ret = 0;
    static size_t ret = 0;
    if(ret > 0)
        return ret;
    
    ret++; // sizeof(header->nSyms) == 1
    ret += header->nSyms * sizeof(*header->cw_table);
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
    // TODO...
    int i = 0;
    for(auto &x : cw_table) {
        hdr->cw_table[i].symbol = x.first;
        hdr->cw_table[i].codeword = str2bits(x.second);
        hdr->cw_table[i].nBits = x.second.length() - 1; // Bcoz 0-indexed
        ++i;
    }
}

// Computes and returns the estimated size of the compressed data.
// It is the sum of all codeword_table.nBits.
size_t get_compressed_size(HeaderStruct *hdr) {
    Log_static("Started...");
    if(!hdr)
        return -1;
    
    static size_t ret = 0;
    
    // If computed before, then no need to recompute.
    if(ret > 0)
        return ret;
        
    for(int i = 0; i < hdr->nSyms; i++)
        ret += hdr->cw_table[i].nBits;
    ret += hdr->nSyms;
    return ret;
}

// Dump the header structure to the output buffer.
void dump_header(HeaderStruct* header, byte* buff) {
    Log_static("Started...");
    if(!header || !buff)
        return; // TODO... Create a NullArgumentException class
    
    buff[0] = header->nSyms;
    size_t cw_table_size = sizeof(*header->cw_table) * header->nSyms;
    memcpy(buff+1, header->cw_table, cw_table_size);
    
}

// Returns the codeword of the symbol
// If the function is called consecutively for the same symbol then
// the cached pointer will be returned. This increases efficiency.
static HeaderStruct::codeword_table *get_cw_entry(HeaderStruct *header, uchar_t *symbol) {
    int i;
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
    BitStream bit_stream(get_compressed_size(header));
    int i;
    for(i = 0; i < ibuff_size; i++) {
        cw_entry = get_cw_entry(header, ibuff+i);

        try {
            bit_stream.push(cw_entry->codeword, cw_entry->nBits);
        } catch(std::overflow_error &e) {
            break;
        }
        
    }
    
    
}
