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

	/*------------------------------------ TODO ------------------------------------ */
    // Fill the output buff appropriately using the 'header' and 'in_buff'
    int i = 0;
    register uint32_t cw_ptr = 0; // This will be used for packing cw
	int32_t places_left = sizeof(uint32_t) * 8;
    fsize_t n_bits = 0, n_bytes = 0;
    struct codeword_map_struct* cw_entry = 0;
    for(byte* in_ptr = in_buff; *in_ptr != '\0'; ++in_ptr, ++i) {
        cw_entry = get_cw_entry(in_ptr, header);
        //@@@ std::cout << "i = " << i << " (" << *in_ptr << ")" << std::endl;

        // Just shortening the long accessing statement
        n_bits += cw_entry->codeword.n_bits;
        n_bytes = (fsize_t)compute_word_len(n_bits);
		uint32_t temp = cw_entry->codeword.cw[0];
		
		// Step: Shift the codeword bits to the MSB portion.
		uint32_t dist_to_msb = sizeof(uint32_t) * 8 - n_bits;
		temp <<= dist_to_msb;
		if((places_left -= n_bits) <= 0) {
			;//cw_ptr = 
		}
		cw_ptr ^= temp;
		
		
		
	#ifdef CRAP
        // left shift the register and copy the first byte of 'cw'
        // to that 32-bit register.
        cw_ptr <<= n_bits;
        shifts += n_bits; // keep track of overflowing 32-bit register
        cw_ptr = (int32_t)cw_entry->codeword.cw[0];
        /* TODO
        for(fsize_t i = 1; i < n_bytes; ++i) {  // Follow next byte if exists
            if(cw_ptr < 0)
        }
        */
	#endif

    #ifdef CRAP
        fsize_t bytes_to_copy =
            (fsize_t)compute_word_len(cw_entry->codeword.n_bits);
        memcpy((char*)ret, (char*)(cw_entry->codeword.cw),
            bytes_to_copy);
        ret += bytes_to_copy;
        header->compressed_size += bytes_to_copy;
    #endif
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

// XXX - This function performs linear search.
//     - It will soon be replaced by some other better algorithm, most
//       probably a HASHING ALGORITHM.
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
