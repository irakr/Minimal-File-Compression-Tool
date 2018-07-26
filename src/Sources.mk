# Source files

# Absolute path of this file with respect to ../
CUR_DIR = src/

# Utility code directory
UTILS_DIR = $(CUR_DIR)utils/

# $(CUR_DIR)min-heap.cpp 	\

## Source file names
SOURCES = 	$(CUR_DIR)huffman-encoder.cpp $(CUR_DIR)huffman-decoder.cpp		        \
			$(CUR_DIR)huffman-compressor.cpp $(CUR_DIR)compression-driver.cpp       \
			$(CUR_DIR)header.cpp $(CUR_DIR)bit-manip.cpp $(CUR_DIR)main.cpp         \
			$(UTILS_DIR)BitVector.cpp
            
