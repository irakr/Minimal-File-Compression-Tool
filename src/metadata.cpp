#include "metadata.h"

void hex_dump(byte *buff, fsize_t len) {
    Log_static("Started...");
    for(fsize_t i = 0; i < len ; ++i) {
        std::cout << "0x" <<
            std::hex << (uint16_t)buff[i] << std::dec << "    ";
    }
    std::cout << std::endl;
}

static inline struct header_struct* new_header() {
    struct header_struct *_new_ = new struct header_struct();
    memset(_new_, 0, sizeof(struct header_struct));
    return _new_;
}

/// Build the metadata structure
/// Only codeword table will be build here
/// Rest of the parameters should be set by the caller
/// FIXME... Better change the parameter type.
struct header_struct*
    init_header(std::unordered_map<byte, std::string> *code_word_map)
{
    Log_static("Started...");
    struct header_struct* ret = new header_struct();
    ret->n_syms = code_word_map->size();
    //std::cout << ret->n_syms << " = " << code_word_map->size();
    ret->cw_map = NULL; // This must be initialized later.
    return ret;
}

// Builds a compressed form of the byte according to the header parameters
byte* get_compressed_byte_stream(byte *in_buff, fsize_t buff_len, struct header_struct *header) {
    Log_static("Started...");

    byte *ret = new byte[buff_len + header->size()]; // Output buff will always be <=
                                    // input buff + header area, if
                                    // compression algorithm is correct.
    memset(ret, 0, buff_len + header->size());

    // First dump the header portion to 'ret' output buff
    // @info This function was the most tricky of all in this project.
    hdr_2_bytes(ret, header);
    header->compressed_size = header->size();
    //hex_dump(ret, header->size()); // Just print

    // Content portion continues from here...
    ret += header->size();

    // Fill the output buff appropriately using the 'header' and 'in_buff'
    int i = 0;
    for(byte* in_ptr = in_buff; *in_ptr != '\0'; ++in_ptr, ++i) {
        struct codeword_map_struct* cw_entry = get_cw_entry(in_ptr, header);
        //@@@ std::cout << "i = " << i << " (" << *in_ptr << ")" << std::endl;
        fsize_t bytes_to_copy =
            (fsize_t)compute_word_len(cw_entry->codeword.n_bits);
        memcpy((char*)ret, (char*)(cw_entry->codeword.cw),
            bytes_to_copy);
        ret += bytes_to_copy;
        header->compressed_size += bytes_to_copy;
        //std::cout << "cs += bytes_to_copy: " << header->compressed_size
        //    << " += " << bytes_to_copy << std::endl;
    }

    std::cout << "Compressed:" << header->compressed_size << std::endl;
    return ret;
}

// Copy every byte and even bytes of pointer members of the header_struct.
// See "Docs/In-file-Metadata.pdf" to understand visually.
// @info This function was the most tricky of all in this project.
void hdr_2_bytes(byte *out, struct header_struct *hdr) {
    Log_static("Started...");

    // Finding out the offset of 'cw_map' from the base address of 'header'
    unsigned long cw_map_offset = (unsigned long)&(hdr->cw_map) - (unsigned long)hdr;

    byte *out_ptr = out;

    // Copy upto (cw_map - 1)th byte
    memcpy((char*)out_ptr, (char*)hdr, cw_map_offset);

    // Now continue copy till cw_map end including internal struct codeword.
    out_ptr += cw_map_offset;
    cw_map_offset = (unsigned long)&(hdr->cw_map[0].codeword) - (unsigned long)(hdr->cw_map);
    unsigned long cw_offset =
        (unsigned long)&(hdr->cw_map->codeword.cw) - (unsigned long)&(hdr->cw_map->codeword);

    // Since 'cw_map' is an array.
    // Copy everything since 'cw_map' till the end of 'header_struct'
    // including internal 'codeword' struct.
    for(fsize_t i = 0; i < hdr->n_syms; ++i) {
        memcpy((char*)out_ptr, (char*)&(hdr->cw_map[i]), cw_map_offset);
        out_ptr += cw_map_offset;
        memcpy((char*)out_ptr, (char*)&(hdr->cw_map[i].codeword), cw_offset);
        out_ptr += cw_offset;
        // XXX... Unconfirmed bug.
        memcpy((char*)out_ptr, (char*)(hdr->cw_map[i].codeword.cw),
            (fsize_t)compute_word_len(hdr->cw_map[i].codeword.n_bits));
    }
}

// Lookup for the codeword of 'sym' in 'header.cw_map[]' field
// and return a pointer to the particular entry.
struct codeword_map_struct*
    get_cw_entry(byte *sym, struct header_struct* header)
{
    //Log_static("Started...");

    if(!sym || !header)
        return NULL;

    struct codeword_map_struct* ret = header->cw_map;
    for(fsize_t i = 0; i < header->n_syms; ++i) {
        if(ret[i].sym == *sym)
            return (ret + i);
    }

    return NULL;
}
