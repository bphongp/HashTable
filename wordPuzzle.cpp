// Bamphiane Annie Phongphouthai
// bp8qg
// October 13, 2017
// wordPuzzle.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "hashTable.h"
#include "timer.h"

using namespace std;

// max grid size
#define MAXROWS 500
#define MAXCOLS 500

// need global table[][]
char table[MAXROWS][MAXCOLS];
timer t;

bool readInTable (string filename, int &rows, int &cols); 
char* getWordInTable (int startRow, int startCol, int dir, int len, int numRows, int numCol );

int main (int argc, char ** argv){
  while (1){
    if ( argc < 3 ) {//check for error
            cout << "Error: Input was less than 3, invalid" << endl;
            break;
    }
    //read in dictionary and get number of words
    string dictionary = argv[1];
    int numLines = 0;
    ifstream fileStream( dictionary.c_str() );
    string temp;
    while ( getline(fileStream, temp ) ) {
      numLines ++;
    }
    fileStream.close();
	
    hashTable *hTable = new hashTable(numLines);

    //read in dictionary and save words to table created
    fileStream.open(dictionary.c_str() );
    string current;
    while(fileStream.good()){
       getline(fileStream, current);
       if (current.length() > 2)
         hTable->insert(current);
       }
       fileStream.close();	
       string gridFile = argv[2];      //passed readInTable()
       fileStream.open (gridFile.c_str());
       int rows, columns;

       if ( !readInTable( gridFile.c_str(), rows, columns ) ){
           cout << "Error reading grid file, try again." << endl;
           break;
       }
       t.start();

        int numWordsFound = 0;
        string result;
        string direction;

        // search each combo for row, col, dir, length for the word
        for ( int r= 0; r < rows; r++ ) {
            for ( int c = 0; c< columns; c++ ) {
                for ( int d = 0; d < 8; d++) {
                    for ( int l = 3; l<= hTable->maxWordNum; l++ ) {
                        string word = getWordInTable (r,c,d,l, rows,columns);
                        if (word.length() < l)
			  break;
                        if ( hTable->contains(word)){
                            numWordsFound++;
			    switch (d) { 
			      case 0:
				direction="N";
				break;
			      case 1:
				direction = "NE";
				break;
			      case 2:
				direction = "E";
				break; 
			      case 3:
				direction = "SE";
				break; 
			      case 4:
				direction = "S";
				break; 
			      case 5:
				direction = "SW";
				break; 
			      case 6:
				direction = "W";
				break;
			      case 7:
				direction = "NW";
				break; 
			    }
			    //cout<<direction<<"("<<r<<","<<c<<
			    //"): \t"<<word<<endl;
			    stringstream ss;
			    ss<<direction<<"("<<r<<","<<c<<"): \t"<<word<<endl;
			    result+=ss.str();
			}//end if(hTable
                    }//end for l
                }//end for d
            }//end for c
        }//end for r
        // stop time after search is done
        t.stop();
        cout << result;
        cout << numWordsFound << " words found." << endl;
        double time = t.getTime();
        cout << "Found words in " << time << " seconds." << endl;
	int shellTime= (int)(time*1000);
	cout<< shellTime <<endl;//averagetime.sh read in
	break;
	}//end while
  return 0;
}//end main

char* getWordInTable (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
  static char output[256];
  if ( len >= 255 )//array size is 256 make sure not greater than that
    len = 255;

  // the position in the output array
  int pos = 0, r = startRow, c = startCol;
  for ( int i = 0; i < len; i++ ) {
    if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) ) //check if in bounds
      break;

    // set the next character in the output array to the next letter
    // in the table
    output[pos++] = table[r][c];

    // move in the direction specified by the parameter
    switch (dir) { // assumes table[0][0] is in the upper-left
    case 0:
      r--;
      break; // north
    case 1:
      r--;
      c++;
      break; // north-east
    case 2:
      c++;
      break; // east
    case 3:
      r++;
      c++;
      break; // south-east
    case 4:
      r++;
      break; // south
    case 5:
      r++;
      c--;
      break; // south-west
    case 6:
      c--;
      break; // west
    case 7:
      r--;
      c--;
      break; // north-west
    }
  }

  // set the next character to zero (end-of-string)
  output[pos] = 0;

  // return the string (a C-style char* string, not a C++ string
  // object)
  return output;
}

bool readInTable (string filename, int &rows, int &cols) 
{

  // a C++ string to hold the line of data that is read in
  string line;

  // set up the file stream to read in the file (takes in a C-style
  // char* string, not a C++ string object)
  ifstream file(filename.c_str());

  if ( !file.is_open() )//false if there is an error
    return false;
  file >> rows;//first line num rows
  getline (file,line); //end of line return 
  file >> cols;//2nd line num of columns
  getline (file,line); // end of line return
  getline (file,line);//3rd line data
  file.close();

  // convert the string into table 2d array
  int pos = 0; // the current position in data
  for ( int r = 0; r < rows; r++ ) {
    for ( int c = 0; c < cols; c++ ) {
      table[r][c] = line[pos++];
    }
  }
  return true;
}
