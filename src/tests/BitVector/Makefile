RECIPEPREFIX = ' '

SRC_DIR = ../../
UTILS_DIR = $(SRC_DIR)utils/

# Dependencies
DEP_SRC = $(SRC_DIR)logger.cpp $(UTILS_DIR)BitVector.cpp

OUT_FILE = test-BitVector

# Compiler flags and other parameters
CXX = g++
CXX_FLAGS = -std=c++14 -g
INCLUDE_DIRS = -I$(SRC_DIR) -I$(UTILS_DIR)

build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -o $(OUT_FILE) $(OUT_FILE).cpp $(DEP_SRC)

clean:
	rm -rf *.o $(OUT_FILE)
