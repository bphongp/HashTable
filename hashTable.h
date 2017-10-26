
//Bamphiane Annie Phongphouthai
//bp8qg
//October 13,2017
//hashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <list>

using namespace std;

class hashTable {
    public:
        hashTable( int size );
        ~hashTable();
        bool contains ( const string & str )const;
        bool insert (const string & str );
        int capacity;
        int maxWordNum;

    private:
        vector<list<string> > *buckets;//buckets to deal with collisions
        int hashFunc(string key)const;
        int getNextPrimeNumber (unsigned int n);
        bool checkifPrime (unsigned int pn);
	int tableSize;
};

#endif
