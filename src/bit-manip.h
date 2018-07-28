/*
 * bit-manip.h
 *
 * This file contains data structures to manipulate bits.
 */

#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <exception>
//#include <cstring>
#include <cmath>
#include "base-class.h"
#include "zz_types.h"

// Computes the number of bytes required to be able to
// store n number of bits, i.e., nBits.
#define BYTES_REQUIRED(nBits)   ceil(nBits / 8.0)

// This class provides functionality to store bits in a variable length
// byte buffer.
class BitStream : public ClassInfo {

private:
    uchar_t *m_buff;
    size_t m_size;  // Current buffer size in bytes
    size_t m_bsize; // Number of bits required to be stored
    size_t m_btop;  // Current number of useful bits in m_buff
                    // starting from m_buff[0]. Points to the next
                    // empty bit position.
    
public:
    
    BitStream(size_t nBits) : m_size(BYTES_REQUIRED(nBits)), m_bsize(nBits),
                              m_btop(0)
    {
        m_buff = new uchar_t[m_size];
    }
   	
    // Push 'n' bits to 'm_buff' from 'bits' starting from LSB.
    // Throws an exception if m_btop has reached m_size.
    void push(uint8_t bits, int n);
    
    /// Accessors for private member variables ///
    
    // Simple print the internal buffer as it is.
    uchar_t* getBitStreamRaw(void);
    
    size_t buffSize(void);
    size_t buffBSize(void);
    size_t buffBTop(void);
    
};

#endif
