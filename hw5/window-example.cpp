#include <QApplication>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "scrabble.h"

using namespace std;

void readConfigFile (std::string config_file_name,
					 std::string & dictionary_file_name,
					 std::string & board_file_name,
					 std::string & bag_file_name,
					 unsigned int & hand_size)
{
	ifstream configFile (config_file_name.c_str());
	string line;
    bool number = false, board = false, tiles = false, dictionary = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name);
	while (getline (configFile, line))
	{
		stringstream ss (line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
			{ ss >> hand_size; number = true; }
		else if (parameter == "BOARD:")
		    { ss >> board_file_name; board = true; }
		else if (parameter == "TILES:")
			{ ss >> bag_file_name; tiles = true; }
		else if (parameter == "DICTIONARY:")
			{ ss >> dictionary_file_name; dictionary = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!board)
		throw invalid_argument("Board file name not specified in config file");
	if (!tiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!dictionary)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int argc, char *argv[])
{
  std::string dictionaryFileName, boardFileName, bagFileName;
  unsigned int numTiles;

  QApplication app (argc, argv);

	// app.setStyleSheet("QPushButton#MyButton { background-color: red }");

  readConfigFile(argv[1],
          dictionaryFileName, boardFileName, bagFileName,
          numTiles);

  Scrabble w(&app, dictionaryFileName, boardFileName, bagFileName,
          numTiles);

  w.playGame();
  return app.exec();
  // return 0;
}
