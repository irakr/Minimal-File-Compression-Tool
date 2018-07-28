/*
 * bit-manip.cpp
 *
 */

#include "bit-manip.h"
#include "logger.h"

size_t BitStream :: buffSize(void) {
    return m_size;
}

size_t BitStream :: buffBSize(void) {
    return m_bsize;
}

size_t BitStream :: buffBTop(void) {
    return m_btop;
}


// TODO TODO TODO TODO
// Build the logic for pushing bits whose remaining bits will overflow to next byte of m_buff.
// Push 'n' bits to 'm_buff' from 'bits'(LSB first).
// Throws an exception if m_btop has reached m_size.
// XXX... Take care of endianness.
void BitStream :: push(uint8_t bits, int n) {
    Log(this, "Started...");
    
    if(m_btop + n > m_bsize)
        throw (new std::overflow_error("BitStream::push(): Cannot push more bits."));
        
    size_t m_buff_index = m_btop / 8; // Current byte number in m_buff[]
    
    // Push the codeword bits only, towards m_btop of a byte.
    // Before that check if the codeword bits will fit in the current byte position or not.
    //
    // @shifts will bring the codeword's MSBit to the m_btop position. And then you can put
    //         the codeword in that position onward in m_buff.
    //      Formula:
    //          shifts = 8 - btop_mod - n
    //
    // @leftover_bits represents the number of bits of the codeword starting from the its LSBit
    //         that will not fit in the in the the current m_buff[i]. So we need to pack them
    //         to the MSB of m_buff[i+1].
    //      Formula:
    //          leftover_bits = n - (8 - btop_mod)
    //
    // @btop_mod is a value that keeps the value of m_btop in the range of 8-bits. Its required
    //         because the computation of @shifts and @leftover_bits consider bit_positions within
    //         a byte.
    //
    int shifts, leftover_bits, btop_mod = m_btop % 8;
    if((shifts = 8 - btop_mod - n) > 0) {
        bits <<= shifts;
    }
    else {
    // Else if the codeword that we are going to pack/push will not entirely fit in the
    // current byte of m_buff.
        leftover_bits = n - (8 - btop_mod);
        for(int i = 0; i < leftover_bits; ++i) {
            if(bits & 1)
                m_buff[m_buff_index + 1] |= (1 << (7 - i));
            else
                m_buff[m_buff_index + 1] &= ~(1 << (7 - i));
            bits >>= 1;
        }
    }
    
    m_buff[m_buff_index] |= bits;
    
    m_btop += n; // Let m_btop point to next empty bit slot.
    
}

// Simple print the internal buffer as it is.
uchar_t* BitStream :: getBitStreamRaw(void) {
    Log(this, "Started...");
    
    return m_buff;
}
