//Bamphiane Annie Phongphouthai
//bp8qg
//10/13/2017
//hashTable.cpp
#include "hashTable.h"


hashTable::hashTable(int size){ //constructor
    buckets = new vector< list <string> >; 
    maxWordNum = 0;
    size <<=1; // more buckets multiply by 2
    tableSize = size;
    if (!checkifPrime(size))
      size<<=1;
      size = getNextPrimeNumber(size);
    buckets->resize(size);
    capacity = size;                        // store size
    for ( int i = 0; i < size; i++ ){
        list<string> temp;
        buckets->push_back(temp);
    }
}

// destructor
hashTable::~hashTable(){
    delete buckets;
}

bool hashTable::contains(const string & str )const{// retrieve correct list from vector
    list<string> & theList = buckets->at(hashFunc(str));
    bool finding =(find(theList.begin(),theList.end(),str) !=(theList.end()));
    return finding;
}

bool hashTable::insert(const string & str ){
    if (!( this->contains(str) ))
    {
        buckets->at(hashFunc(str)).push_back(str);
        int len = str.length();
        if ( len > maxWordNum)//store max word
            maxWordNum = len;
        return true;
    }
    return false;
}

int hashTable::hashFunc(string key)const{
  unsigned int hashVal = 1;
    int len = key.length()/2 +1;
    for ( int i = 0; i < len; i ++)
    {
        hashVal *= ((key[i]*37) % tableSize);
        hashVal <<= 1;
    }
    hashVal %= capacity;
    return hashVal;
    /*unsigned int hashVal =0;
  for ( int i = 0; i < key.length(); i ++){
    hashVal=(int)key[i];
      }
      return hashVal;*/
}

bool hashTable::checkifPrime (unsigned int pn){
    if( pn <= 1 )
      return false;
    if( pn == 2 ) //2 is prime but all other even is not
      return true; 
    if( pn%2 == 0 )
      return false; 
    for(int i = 3; i*i <= pn; i += 2){ //check all numbers and go up to sqrt(pn)
      if( pn%i == 0 )
	return false;
    }
  return true;
}

int hashTable::getNextPrimeNumber (unsigned int n)
{
  /*while(!checkifPrime(n++));
    return n;*/
  unsigned int num = n+1;
  bool getPrime = true;
  while(getPrime){
    if(!checkifPrime(num))
      num++;
    else
      getPrime = false;
  }
  return num;
}
