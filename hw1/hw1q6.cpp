#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char * argv[]) {

    // Variables: Number of words, array count, word,
       int number;
    int count = 0;
    string word;

    ifstream ifile(argv[1]);

    if(argc < 2) {
         cerr << "Please input a file." << endl;
         return 0;
    }

    // Check if the file can be opened
      if(ifile.fail()) {
            cerr << "Could not open the file. Please try again :)" << endl;
         return 1;
      }

      // If file can be opened, heck if the first line is a number
      ifile >> number;

      if(ifile.fail()) {
            cerr << "Not a number!" << endl;
            return 1;
       }   

       // Dynamically allocate an array of words in the text file
       string* words = new string[number];

      // As long as can still be read in from the text file, put in 
      // dynamically allocated array
      while(ifile >> word) {

            words[count] = word;

            count++;
       }

      for(int i = number - 1; i >= 0; i--) {
         cout << words[i] << endl;
      }

       ifile.close();

       delete [] words;

       return 0;

}
