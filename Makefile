include src/Sources.mk

OBJECTS = $(SOURCES:.cpp=.o)

#CXX = g++
CXXFLAGS = -Wall -g
CPPFLAGS = 
DEFINES = 
INCLUDE_DIRS = -Isrc/
LDFLAGS = 
OUTPUT = bin/test.out

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
	