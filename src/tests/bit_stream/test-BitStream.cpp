#include <iostream>
#include "../../logger.h"
#include "../../bit-manip.h"

using namespace std;

void printBuff(BitStream &bs) {
	int i;
	for(i = 0; i < bs.buffSize(); i++) {
		cout << "buff[" << i << "] : ";
		cout << hex << (int)bs.getBitStreamRaw()[i] << endl;
	}
	cout << endl;
}

int main(void) {
    BitStream bit_stream(16);
    try {
        bit_stream.push(0x1A, 5);
        printBuff(bit_stream);
        bit_stream.push(0x0f, 4);
        printBuff(bit_stream);
        bit_stream.push(0x0f, 4);
        printBuff(bit_stream);
        bit_stream.push(0x01, 1);
        printBuff(bit_stream);
        bit_stream.push(0x03, 2);
        printBuff(bit_stream);
        bit_stream.push(0x03, 2);
        printBuff(bit_stream);
    } catch(overflow_error *e) {
        //cerr << "Cannot push more bits" << endl;
        cerr << e->what() << endl;
    }
    return 0;
}
