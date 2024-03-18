/******************************************************************************
Author: Matthew Alvarez
Course: CSCI 115 Lab
Assignment: Lab 7

Notes: 
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int HASHSIZE = 4001; // Prime number declared for global scope

class HashArray {
private:
    pair<string, int> hashTable[HASHSIZE];  // preferred to struct
    int* updates = new int[HASHSIZE];
    int* cost = new int[HASHSIZE];
    int numElements;
    int numProbes;

    // return ascii values added together
    int hashFunction(const string& key) {
        unsigned int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % HASHSIZE; // Simple hash function
        }
        return hash;
    }

    // return 1 if array index is empty
    bool isEmpty(int index)  {
        return hashTable[index].first == "";
    }

public:
    //constructor
    HashArray() {
        numElements = 0;
        numProbes = 0;
        for (int i = 0; i < HASHSIZE; ++i) {
            hashTable[i] = make_pair("", 0);
            updates[i] = 0;
            cost[i] = 0;
        }
    }

    void update(const string& key) {
        int index = hashFunction(key);
        int i = 0;
        //find word in array or empty index
        while (!isEmpty(index) && hashTable[index].first != key) {
            index = (index + i) % HASHSIZE; // Linear probing
            i++;
            numProbes++;
            cost[size()] = probes();
        }
        // index is empty
        if (isEmpty(index)) {
            hashTable[index] = make_pair(key, 1);
            numElements++;
            numProbes = 0;
        }
        // index found
        else {
            hashTable[index].second++;
            updates[size()]++;
        }
    }

    // # of unique ele
    int size() {
        return numElements;
    }

    // # of times array accessed
    int probes() {
        return numProbes;
    }

    // print stats
    void printStatistics() {
        cout << "Unique words count: " << size() << endl;
        cout << "Cost ratios:" << endl;

        for (int i = 1; i <= size(); i++) {
            // # probes at level / # updates at level
            double ratio = (updates[i] != 0) ? static_cast<double>(cost[i]) / updates[i] : 0.0; //if Update = 0, cout = 0.0
            cout << "[" << i << "]: " << fixed << setprecision(2) << ratio;  //fixed to precision 2
            
            // commas and structure
            if (i != size()) {
                cout << ", ";
            }
            else {
                cout << endl;
            }
            if (i % 10 == 0) {
                cout << endl;
            }
        }
    }
};

int main() {
    HashArray hashRJ;

    ifstream inputFile("RomeoAndJuliet.txt");
    string word;
    while (inputFile >> word) { // Read from standard input until EOF
        //update every word 
        hashRJ.update(word);
    }

    hashRJ.printStatistics();

    return 0;
}