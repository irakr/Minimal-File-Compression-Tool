#include <iostream>

#define DEBUG_ON
#include "../logger.h"

#include "../min-heap.h"

using namespace std;

typedef unsigned char byte;

int main() {
    MinHeap<byte, double> minheap;
    MinHeapNode<byte, double> nodes[5];
    nodes[0].data = 'a';
    nodes[0].freq = 10.1;
    nodes[1].data = 'b';
    nodes[1].freq = 20.2;
    nodes[2].data = 'c';
    nodes[2].freq = 30.3;
    nodes[3].data = 'd';
    nodes[3].freq = 40.4;
    nodes[4].data = 'e';
    nodes[4].freq = 50.5;
    for(int i = 0; i < 5; i++)
        minheap.push(&nodes[i]);

    printMinheap(minheap);
    // Lets check whether printMinHeap() is const on the argument.
    printMinheap(minheap);
    return 0;
}
