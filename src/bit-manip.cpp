/*
 * bit-manip.cpp
 *
 */

#include "bit-manip.h"
#include "logger.h"

// Push 'n' bits to 'm_buff' from 'bits' starting from LSB.
// Throws an exception if m_bsize has reached m_size.
// XXX... Take care of endianness.
void BitStream :: push(uint32_t bits, int n) {
    Log(this, "Started...");
    
    if(m_bsize + n > m_size)
        throw (new std::overflow_error("BitStream::push(): Cannot push more bits."));
    
    // TODO... Finish this.
}
