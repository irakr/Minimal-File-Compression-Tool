SRC_DIR = ../../
DEP_SRC = $(SRC_DIR)header.cpp   \
        $(SRC_DIR)logger.cpp     \
        $(SRC_DIR)bit-manip.cpp	 \
        $(SRC_DIR)huffman-encoder.cpp
OUT_FILE = test-header

CXX = g++
CXX_FLAGS = -std=c++14 -g -O0 -Wall
INCLUDE_DIRS = -I$(SRC_DIR)

build:
	$(CXX) $(INCLUDE_DIRS) $(CXX_FLAGS) -o $(OUT_FILE) test-header.cpp $(DEP_SRC)

clean:
	rm -rf *.o $(OUT_FILE)
