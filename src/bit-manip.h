/*
 * bit-manip.h
 *
 * This file contains data structures to manipulate bits.
 */

#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <exception>
#include "base-class.h"
#include "zz_types.h"

// This class provides functionality to store bits in a variable length
// byte buffer.
class BitStream : public ClassInfo {

private:
    uchar_t *m_buff;
    size_t m_size; // Current buffer size
    size_t m_bsize; // Current number of valid bits in m_buff
                    // starting from m_buff[0].
    
public:
    
    BitStream(size_t s) : m_size(s) {
        m_buff = new uchar_t[s];
    }
    
    // Push 'n' bits to 'm_buff' from 'bits' starting from LSB.
    // Throws an exception if m_bsize has reached m_size.
    void push(uint32_t bits, int n);
    
};

#endif
