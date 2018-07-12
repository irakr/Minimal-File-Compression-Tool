include src/Sources.mk

OBJECTS = $(SOURCES:.cpp=.o)

#CXX = g++
CXXFLAGS = -Wall -g -std=c++14 -O0
DEFINES = -DDEBUG_ON
INCLUDE_DIRS = -Isrc/
CPPFLAGS = $(DEFINES) $(INCLUDE_DIRS)
LDFLAGS = 
OUTPUT = bin/zz

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE_DIRS) $< -c -o $@

$(OUTPUT): $(OBJECTS)
	-mkdir bin
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY: build
build: $(OUTPUT)

.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(OUTPUT) bin
	
