#include <string>
#include <map>
#include <set>
#include "Move.h"
#include "Dictionary.h"
#include "Board.h"
#include "Player.h"
#include "AbstractAI.h"
#include <iostream>


class ScorePlayer: public AbstractAI {
 public:

   ScorePlayer();
   ~ScorePlayer();
  std::string getName();
  // returns the name by which the AI would like to be called

  void initialize (Dictionary* dict);
  /* you can use this function to do pre-processing, such as
     constructing maps for fast lookup.
     We will call initilalize on your AI before asking it for its first move. */

  Move getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount);
  /* This will be the main function doing the work.
     You will get the board and player, and have hopefully stored the dictionary.
     You also get a map giving you the initial number of each type of tiles in the bag.
     (The board class allows you to find out how many of each type have been placed.)
     You should return a Move object describing the move your AI wants to make.
  */

  void printPrefix();
  bool checkPrefix(std::string test);
  void createMap(std::set<Tile*> currHand);
  std::map<char, int> getMap();

private:
  std::string scoreName;
  std::set<std::string> prefixes;
  std::map<char, int> letterCount;
  std::string bestCurrWord;
  int maxScore;
  int length;
};
