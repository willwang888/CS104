CXX = g++
CPPFLAGS = -g -Wall

all: Scrabble

Scrabble: Scrabble.cpp Bag.o Board.o Player.o Square.o Dictionary.o
	$(CXX) $(CPPFLAGS) Scrabble.cpp Bag.o Player.o Square.o Dictionary.o \
	Board.o -o Scrabble

Bag.o: Bag.h Bag.cpp
	$(CXX) $(CPPFLAGS) -c Bag.cpp -o Bag.o

Board.o: Board.h Board.cpp
	$(CXX) $(CPPFLAGS) -c Board.cpp -o Board.o

Player.o: Player.h Player.cpp
	$(CXX) $(CPPFLAGS) -c Player.cpp -o Player.o

Square.o: Square.h Square.cpp
	$(CXX) $(CPPFLAGS) -c Square.cpp -o Square.o

Dictionary.o: Dictionary.h Dictionary.cpp
	$(CXX) $(CPPFLAGS) -c Dictionary.cpp -o Dictionary.o
