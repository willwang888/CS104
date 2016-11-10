# Declare variables
CC       = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

Scrabble: Tile.h Dictionary.o Square.h Bag.o Board.o Player.o Move.o Util.o GameCommands.o ScorePlayer.o Scrabble.cpp Game.o
	$(CC) $(CPPFLAGS) Dictionary.o Bag.o Board.o Player.o Move.o Util.o GameCommands.o ScorePlayer.o Game.o Scrabble.cpp -o Scrabble
GameCommands.o: GameCommands.cpp GameCommands.hpp Game.h Exceptions.h
	$(CC) $(CPPFLAGS) -c $< -o $@
ScorePlayer.o: ScorePlayer.cpp ScorePlayer.h AbstractAI.h
	$(CC) $(CPPFLAGS) -c $< -o $@
.PHONY: clean tests
#UNCHANGED
clean:
	-@rm Scrabble
	-@rm GameCommands.o
	-@rm ScorePlayer.o
	-@echo "--- All Clean!---"
