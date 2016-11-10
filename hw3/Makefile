# BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: llisttest stringparser stackstring.o

llisttest: llisttest.cpp lliststring.o
	$(CXX) $(CPPFLAGS) llisttest.cpp lliststring.o $(GTEST_LL) -o llisttest

llistring.o: lliststring.h lliststring.cpp 
	$(CXX) $(CPPFLAGS) -c lliststring.cpp -o lliststring.o

stackstring.o: stackstring.h stackstring.cpp lliststring.o
	$(CXX) $(CPPFLAGS) -c lliststring.o stackstring.cpp -o stackstring.o

stringparser: lliststring.o stackstring.o stringparser.cpp
	$(CXX) $(CPPFLAGS) lliststring.o stackstring.o stringparser.cpp -o stringparser

