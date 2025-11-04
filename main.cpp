//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Max number of total nodes (letters + parents)
const int MAX_NODES = 64;
// Global arrays for node information
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0}; // store frequency for each letter

    buildFrequencyTable(freq, "input.txt");
    int nextFree = createLeafNodes(freq);
    int root = buildEncodingTree(nextFree);

    string codes[26];
    generateCodes(root, codes);
    encodeMessage("input.txt", codes);

    return 0;
}

// Step 1: Count letters
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z') freq[ch - 'a']++;
    }
    file.close();
    cout << "Frequency table built successfully.\n";
}

// Step 2: make leaves
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: build tree using heap
int buildEncodingTree(int nextFree) {
    MinHeap heap;

    // put all leaves in heap
    for (int i = 0; i < nextFree; i++)
        heap.push(i, weightArr);

    // combine nodes until one left
    while (heap.size > 1) {
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        int parent = nextFree++;
        weightArr[parent] = weightArr[left] + weightArr[right];
        leftArr[parent] = left;
        rightArr[parent] = right;
        charArr[parent] = '*'; // non-leaf

        heap.push(parent, weightArr);
    }
    return heap.pop(weightArr); // root
}

// Step 4: iterative DFS with stack
void generateCodes(int root, string codes[]) {
    if (root < 0) return;

    stack<pair<int, string>> st;
    st.push({root, ""});

    while (!st.empty()) {
        auto [node, code] = st.top();
        st.pop();

        if (leftArr[node] == -1 && rightArr[node] == -1) {
            // leaf node
            char ch = charArr[node];
            if (ch >= 'a' && ch <= 'z')
                codes[ch - 'a'] = code;
        } else {
            if (rightArr[node] != -1)
                st.push({rightArr[node], code + "1"});
            if (leftArr[node] != -1)
                st.push({leftArr[node], code + "0"});
        }
    }
    cout << "Codes generated successfully.\n";
}

// Step 5: print codes and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}