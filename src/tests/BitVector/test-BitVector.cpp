#include <iostream>
#include "logger.h"
#include "BitVector.h"

using namespace std;

int main(void) {
  /* (TODO)
   * Write unit test code
   */
  BitVector bit_vector(0x07);
  cout << bit_vector << endl;
  //bit_vector.appendBit(0x00, 5);
  //cout << bit_vector << endl;
  //bit_vector.appendBit(0x01, 5);
  //cout << bit_vector << endl;
  bit_vector.appendByte(0x0f);
  cout << bit_vector << endl;
  bit_vector.appendBit(0x01, 3);
  cout << bit_vector << endl;

  uchar_t *arr = (uchar_t*)bit_vector.toCharArray();
  cout << "CharArray: ";
  for(int i = 0; i < bit_vector.getNumberOfBytes(); ++i) {
    cout << hex << (int16_t)arr[i] << " ";
      //(i < bit_vector.getNumberOfBytes()) ? " " : "";
  }
  cout << endl;

  return 0;
}
