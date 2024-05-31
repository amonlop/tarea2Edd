#ifndef HASHTABLEID.H
#define HASHTABLEID.H

#include <iostream>
#include <string>

using namespace std;

class HashTableID {
    private:
        int size;
        int *table; //?
        int (*hashing_method)(int, int, int);

    

};


#endif