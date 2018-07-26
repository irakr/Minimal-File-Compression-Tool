/*
 * test-header.cpp
 *
 * This is a test program that unit tests the header module.
 */

#include <iostream>
#include <cstring>
#include "zz_types.h"
#include "logger.h"
#include "header.h"
#include "huffman-encoder.h"

// Sample input buffer
byte ibuff[] = "aabbacccdbdeccgdaaadaabcda";
byte obuff[64] = ""; // compressed data of ibuff
CodewordTable cwTable = {
  {'a', "11"},
  {'e', "10011"},
  {'d', "00"},
  {'b', "101"},
  {'\n', "1000"},
  {'c', "01"},
  {'g', "10010"}
};
FrequencyTable freqTable = {
  {'g', 3.7037037037037033},
  {'e', 3.7037037037037033},
  {'d', 18.518518518518519},
  {'a', 33.333333333333329},
  {'\n', 3.7037037037037033},
  {'b', 14.814814814814813},
  {'c', 22.222222222222221}
};

int main(void) {
  HeaderStruct header;

  // Steps to build the header structure.
  build_header(&header, cwTable);
  header.header_size = get_header_size(&header);
	header.original_size = strlen((const char*)ibuff);
	header.compressed_size = get_compressed_size(&header, freqTable);
  dump_header(&header, obuff);
  std::cout << "--- HeaderStruct partial ---" << std::endl;
  for(int i = 0; i < 32; i++)
    std::cout << std::hex << (int)obuff[i] << "\t\t" << (int)((byte*)&header)[i] << std::endl;
  std::cout << "--- cw_table ---" << std::endl;

  /*
  for(int i = 0; i < header.nSyms; i++) {
    std::cout << header.cw_table[i].symbol << "\t\t" <<
          ((HeaderStruct*)obuff)->cw_table[i].symbol << std::endl;
  }
  */

  return 0;
}
