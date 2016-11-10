#include "ScorePlayer.h"

using namespace std;

ScorePlayer::ScorePlayer() {
  scoreName = "";
}

ScorePlayer::~ScorePlayer() {

}

std::string ScorePlayer::getName() {
// returns the name by which the AI would like to be called
  return scoreName;
}

void ScorePlayer::initialize (Dictionary* dict) {
/* you can use this function to do pre-processing, such as
   constructing maps for fast lookup.
   We will call initilalize on your AI before asking it for its first move. */

   set<string> tempDict = dict->allWords();
   set<string>::iterator it;

   for(it = tempDict.begin(); it != tempDict.end(); it++) {
     string buffer = "";
     for(unsigned int i = 0; i < it->size(); i++) {
       buffer += (*it)[i];
       prefixes.insert(buffer);
     }
   }

 }

void ScorePlayer::printPrefix() {
 set<string>::iterator it;

 for(it = prefixes.begin(); it != prefixes.end(); ++it) {
   cout << (*it) << endl;
 }
}

// Checks against the prefix dictionary and verifies if the
bool ScorePlayer::checkPrefix(string test) {
  set<string>::iterator it;

  it = prefixes.find(test);

  if(it != prefixes.end()) {
		return true;
	} else {
		return false;
	}
}

void ScorePlayer::createMap(set<Tile*> currHand) {
  set<Tile*>::iterator it;
  map<char, int>::iterator it2;

  for(it = currHand.begin(); it != currHand.end(); ++it) {
    char temp = (*it)->getLetter();
    it2 = letterCount.find(temp);

    if(it2 != letterCount.end()) {
      it2->second++;
    } else {
      letterCount.insert(pair<char, int>(temp, 1));
    }
  }
}

std::map<char, int> ScorePlayer::getMap() {
  return letterCount;
}

Move ScorePlayer::getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount) {
  // Iterate through every instance of the board, and check every square

  // currHand now has the player's current tiles
  set<Tile*> currHand = player.getHandTiles();

  map<char, int> allTiles = createMap(currHand);

  for(int i = 0; i < board.getRows(); i++) {
    for(int j = 0; j < board.getColumns(); j++) {
      // Start Placing Vertically
      backTrackVertical()
      // Start Placing Horizontally
      backtrackHorizontal();
    }
  }

  if not prefix, backtrack once in the direction we put the word down, and try next letter
  if prefix and in dictionary
    if(not getWords) {

    }

  else if prefix and not in dictionary, continue to next

}

bool backTrackVertical(string prefix, Board& board, map<char, int>& allTiles, int startRow, int startCol,
  int currRow, int currCol) {
  string currPrefix = "";

  if(startRow = board.getRows() + 1) {
    return true;
  }
  //
  // // If reached left or right side of the board, go to next row
  // if(col == board.getColumns()) {
  //   row++;
  //   col = 0;
  // }

  if(col == 10) {
    return solveHelper(row + 1, 1);
  }

//
  else {
    // IF THE CURRENT SQUARE IS OCCUPIED
    if(board->getSquare(currRow, currCol).isOccupied()) {
      // Get the letter from the square and add it to the buffer
      currPrefix += board->getSquare(currRow, currCol).getLetter();
      backTrackVertical(currRow + 1, currCol);

    } else {
        // Recurse on the next square
        backTrackVertical(currRow + 1, currCol);
    }

    // Cycle through the player's hand for tiles
    for(int i = 1; i < 10; i++) {
      // Use the tiles that the player still has.
      // If the letter is a question mark, go through the set of english alphabet
      // which would be made by
      board[row][col] = i; // Add a tile the player has to the prefix
      if(isValid(row, col)) { //Check if the prefix is in the PREFIX DICTIONARY
        // If prefix is in prefix dictionary, check if it's in the WORD DICTIONARY
        if prefix IS in word dictionary { // If prefix is in the word dictionary

        }
        // If the prefix is NOT in the word dictionary, return false and backtrack to the previous one
        else return false
        if(backTrackHelper(row, col + 1)) {
          return backTrackHelper(row, col + 2);
        }
      }
    }
    board[row][col] = 0;

  return false;
}
