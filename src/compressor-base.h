#ifndef COMP_BASE_H_
#define COMP_BASE_H_

#include <iostream>
#include <fstream>
#include "base-class.h"

// Typedef for a raw byte
typedef unsigned char byte;

// Typedef for a file size
typedef long int fsize_t;

class Encoder;
class Decoder;

/*
 * @class
 * @Description
 * An abstract class for implementation of various compression algorithms.
 * All compression algorithm classes must inherit this class.
 */
class Compressor : public ClassInfo {
protected:
	std::string m_name; // Registered name of the compression algorithm
	
	Encoder *m_encoder;
	Decoder *m_decoder;
public:
	std::string name() const { return m_name; }
	
	Encoder& encoder() { return *m_encoder; }
	Decoder& decoder() { return *m_decoder; }
};

/*
 * @class
 * @Description
 * Interface for all Encoders.
 * All encoding logic classes must inherit this class.
 */
class Encoder : public ClassInfo {
public:
	virtual std::fstream& encode(std::fstream&) = 0;
};

/*
 * @class
 * @Description
 * Interface for all Decoders.
 * All decoding logic classes must inherit this class.
 */
class Decoder : public ClassInfo {
public:
	virtual std::fstream& decode(std::fstream&) = 0;
};

#endif