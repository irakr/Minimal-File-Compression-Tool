/*
 * main.cpp
 *
 * Main entry point of the program.
 */

#include <iostream>
#include <exception>
#include "compression-driver.h"
#include "logger.h"

using namespace std;

#define FATAR_ERROR 2
#define SUCCESS 0

// Main entry function
int main(int argc, char **argv) {

	cout << " --- Still under construction ---" << endl;
	Log_static("Started...");

	try {
		CompressionDriver driver(argc, (const char**)(argv+1));
		driver.setCompressor("Huffman-Coding");
		cout << "Selected algorithm: " << driver.getCompressorName() << endl;
		driver.compressAll();
	}
	catch(exception &e) {
		Log_static(e.what());
		return FATAR_ERROR;
	}

	return SUCCESS;
}
