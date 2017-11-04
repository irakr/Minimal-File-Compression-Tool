#include <iostream>
#include <fstream>

#ifndef COMP_BASE_H_
#define COMP_BASE_H_

class Encoder;
class Decoder;

/*
 * @class
 * @Description
 * An abstract class for implementation of various compression algorithms.
 * All compression algorithm classes must inherit this class.
 */
class Compressor {
protected:
	Encoder *m_encoder;
	Decoder *m_decoder;
public:
	Encoder& Encoder() { return *m_encoder; }
	Decoder& Decoder() { return *m_decoder; }
};

/*
 * @class
 * @Description
 * Interface for all Encoders.
 * All encoding logic classes must inherit this class.
 */
class Encoder {
public:
	virtual std::fstream& encode(std::fstream&) = 0;
};

/*
 * @class
 * @Description
 * Interface for all Decoders.
 * All decoding logic classes must inherit this class.
 */
class Decoder {
public:
	virtual std::fstream& decode(std::fstream&) = 0;
};

#endif