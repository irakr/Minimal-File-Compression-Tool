include src/Sources.mk

OBJECTS = $(SOURCES:.cpp=.o)

#CXX = g++
CXXFLAGS = -Wall -std=c++14
DEFINES =
INCLUDE_DIRS = -Isrc/

# Command line arg parse
ifeq ($(debug), y)
	CXXFLAGS += -g -O0
	DEFINES = -DDEBUG_ON
endif

CPPFLAGS = $(DEFINES) $(INCLUDE_DIRS)
LDFLAGS = 
OUTPUT = bin/zz

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -c -o $@

$(OUTPUT): $(OBJECTS)
	-mkdir bin
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY: build
build: $(OUTPUT)

.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(OUTPUT) bin
	
