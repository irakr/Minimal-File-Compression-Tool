RECIPEPREFIX = ' '

SRC_DIR = ../../
DEP_SRC = $(SRC_DIR)bit-manip.cpp   \
        $(SRC_DIR)logger.cpp
OUT_FILE = test-BitStream

CXX = g++
CXX_FLAGS = -std=c++14 -g

build:
	$(CXX) $(CXX_FLAGS) -o $(OUT_FILE) test-BitStream.cpp $(DEP_SRC)

clean:
	rm -rf *.o $(OUT_FILE)
