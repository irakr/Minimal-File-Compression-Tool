#include <iostream>
#include "../metadata.h"

using namespace std;

int main() {
    cout << "sizeof(codeword_map_struct) = " << sizeof(codeword_map_struct)
            << std::endl;
    cout << "sizeof(header_struct) = " << sizeof(header_struct)
            << std::endl;
    struct header_struct* newHeader = new_header();
    return 0;
}
