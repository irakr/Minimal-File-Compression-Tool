/*
 * main.cpp
 * 
 * Main entry point of the program.
 */

#include <iostream>
#include "compression-engine.h"

using namespace std;

// Main entry function
int main(int argc, char **argv) {
	
	cout << " --- Still under construction ---" << endl;
	
	CompressionEngine engine(argc, (const char**)(argv+1));
	engine.setCompressor("Huffman-Coding");
	cout << "Selected algorithm: " << engine.getCompressorName() << endl;
	engine.compressAll();
	
	return 0;
}