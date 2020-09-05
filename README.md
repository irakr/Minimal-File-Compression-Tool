# Minimal File Compression Tool (MFCT)

This project is just for my own experimentation purpose. Not really a tool.

# (Decompression code is still under development)

# Features:
- Supported file types: ASCII text files.
- Algorithms used: Huffman Coding algorithm.
- Written in C++11.

# Build instructions:
- There are two types of builds that can be generated, release and debug builds:
    - To generate release build:
       > make
    - To generate debug build:
       > make debug=y
- The output binary will be available in the bin directory with the name "zz".

# Usage guide:
- Run the file bin/zz to use the program.
- Usage:
  > zz \<filename\>
- The compressed file generated will be produced in the same directory with a
  ".compressed" string appended to its name.

# (NOTE: This program only works for ASCII text files. I do not guarantee the result of compressing other type of files and ofcourse it won't work correctly.)
