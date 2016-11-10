#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int constructionspots;
  int *buildingheights;
  string **skyline;
  string curr;

  input >> constructionspots;
  getline(input, curr); //consume the newline character for the first line.
  skyline = new string*[constructionspots];

  //you will need to keep track of the height of each building
  buildingheights = new int[constructionspots];

  for (int i = 0; i < constructionspots; i++) {
     buildingheights[i] = 0;
     skyline[i] = NULL;
  }

  while(getline(input, curr)) {
     stringstream ss;
     string extraString;

     ss << curr;
     ss >> curr;

     if (curr == "BUILD") {
        int x,y;
        string c;
        ss >> x;
        ss >> y;
        ss >> c;

        // If skyscraper already at location
        if (ss.fail() || skyline[x] != NULL || x >= constructionspots || ss >> 
         extraString) {
           output << "Error - incorrect command" << endl;
        }

        else {

           // Make the building heights the inputted building height
           buildingheights[x] = y;

           // Initialize a new array in the skyline[x]
           skyline[x] = new string[y];

           // Assign colors to every skyline
           for(int i = 0; i < y; i++) {
              skyline[x][i] = c;
           }
        }
     }

     else if (curr == "EXTEND") {

          int x,y;
          string c;

        ss >> x;
        ss >> y;
        ss >> c;

          // If no skyscraper at location, or if construction spot is wrong
        if (ss.fail() || skyline[x] == NULL || x < 0 || x > constructionspots 
         || x >= constructionspots || ss >> extraString) {
           output << "Error - incorrect command" << endl;
        }

        else {

           // Create a new array of new total height
           string* newArray = new string[buildingheights[x] + y];

           // Copy all elmeents of old array to new array
           for(int i = 0; i < buildingheights[x]; i++) {
              newArray[i] = skyline[x][i];
           }

           // Delete old array
           delete[] skyline[x];
           
           // Assign new color to the rest of the array
           for(int i = buildingheights[x]; i < buildingheights[x] + y; i++) {
              newArray[i] = c;
           }

           // Make skyline point to new array
           skyline[x] = newArray;

           // New buildingheight is old buildingheight + extension
           buildingheights[x] += y; 
        }
     }

     else if (curr == "DEMOLISH") {
        int x;
        ss >> x;

        // If no skyscraper at location
      if (ss.fail() || skyline[x] == NULL || x >= constructionspots || ss >> 
      extraString) {
         output << "Error - incorrect command" << endl;
      }

      else {

         // Set building heights to 0, and set all skyline arrays to NULL after 
       // deleting skyline
         delete [] skyline[x];
         skyline[x] = NULL;

         buildingheights[x] = 0;
      }
     }

     else if (curr == "SKYLINE") {
        int y;
        ss >> y;
        // if y < 1, output error
        if(y < 1 || ss.fail() || ss >> extraString) {
           output << "Error - incorrect command" << endl;
        }
      
      // Otherwise, print out the color at the specific index, or SKY if no 
     // color
        else {

           for(int i = 0; i < constructionspots; i++) {
              if(skyline[i] == NULL || buildingheights[i] < y) {
                 output << "SKY ";   
              }
              else {
                 output << skyline[i][y-1] << " ";
              }
           }

           output << endl;
        }
     }
  }

  // Perform all delete functions on all pointers allocated
  for(int i = 0; i < constructionspots; i++) {
     delete [] skyline[i];
  }

  delete [] skyline;

  delete [] buildingheights;

  return 0;
}
