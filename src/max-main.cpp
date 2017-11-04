#include <iostream>
#include "max-heap.h"

using namespace std;

int main(void) {
	int arr[] = {1, 4, 3, 7, 8, 9, 10};
    MaxHeap h(arr, 7);
	h.printArray();
	/*
	//MaxHeap h(50);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractMax() << " ";
    cout << h.getMax() << " ";
    h.decreaseKey(2, 1);
    cout << h.getMax();
    */
	return 0;
}