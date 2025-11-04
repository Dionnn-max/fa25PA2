//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

// This MinHeap stores indexes of nodes.
// It orders them based on their weights (from weightArr).
struct MinHeap {
    int data[64]; // stores node indexes
    int size;     // current number of elements

    MinHeap() { size = 0; }

    // add a new node index into the heap
    void push(int idx, int weightArr[]) {
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    // remove and return the smallest node index
    int pop(int weightArr[]) {
        if (size == 0) return -1;
        int root = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);
        return root;
    }

    // move node up until heap property is fixed
    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else break;
        }
    }

    // move node down until heap property is fixed
    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;

            // pick the smallest child
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]])
                smallest = left;
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]])
                smallest = right;

            // stop if already in correct order
            if (smallest == pos) break;

            swap(data[pos], data[smallest]);
            pos = smallest;
        }
    }
};

#endif
