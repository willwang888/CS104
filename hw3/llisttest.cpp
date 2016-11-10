#include "lliststring.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class LListStringTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListStringTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListStringTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		list.insert(0, "hi");
		list.insert(1, "my");
		list.insert(2, "name");
		list.insert(3, "william");
		list.insert(4, "wang");
		
		list2.insert(0, "HI");
		list2.insert(1, "MY");
		list2.insert(2, "NAME");
		list2.insert(3, "WILLIAM");
		list2.insert(4, "WANG");
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).

	}

	// Objects declared here can be used by all tests in the test case.
	LListString list, list2, list3;

};

// Test get function within bounds
TEST_F(LListStringTest, GetNominal) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	EXPECT_EQ("william", list.get(3));

	EXPECT_EQ("WILLIAM", list2.get(3));

}

// Test the get function as well as the bracket overload at the same time
TEST_F(LListStringTest, GetAndBracketOffNominal) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	try {
		list[-5];
	} catch(const std::exception& bad) {
		EXPECT_EQ((std::string)"bad location", (std::string)bad.what());
	}
	try {
		list2[500];
	} catch(const std::exception& bad) {
		EXPECT_EQ((std::string)"bad location", (std::string)bad.what());
	}
	try {
		list3[500];
	} catch(const std::exception& bad) {
		EXPECT_EQ((std::string)"bad location", (std::string)bad.what());
	}
}

// Add two non-empty lists to each other
TEST_F(LListStringTest, AddNominal) {

	LListString newList = list + list2;

	EXPECT_EQ("hi", newList.get(0));
	EXPECT_EQ("WANG", newList.get(9));
	EXPECT_EQ("HI", newList.get(5));
	EXPECT_EQ("NAME", newList.get(7));
}

// Add an empty + non-empty, non-empty + empty, and empty + empty
TEST_F(LListStringTest, AddOffNominal) {
	LListString list5 = (list3 + list);

	// Add Non-Empty to Empty list
	EXPECT_EQ(0, list5.size());

	// Add Empty to Non-Empty list
	LListString list7 = (list + list3);

	EXPECT_EQ(5, list7.size());

	// Add two empty lists
	LListString list10(list3);
	LListString list9 = (list3 + list10);

	EXPECT_EQ(0, list9.size());

}

// Assign a non-empty list to another non-empty list
TEST_F(LListStringTest, EqualsNominal) {
	list = list2;

	EXPECT_EQ("HI", list.get(0));
	EXPECT_EQ("MY", list.get(1));
	EXPECT_EQ("NAME", list.get(2));
	EXPECT_EQ("WILLIAM", list.get(3));
	EXPECT_EQ("WANG", list.get(4));
}

// Set a non-empty list to an empty list
TEST_F(LListStringTest, EqualsOffNominal) {
	list = list3;

	EXPECT_EQ(0, list.size());
}

// Construct a new list from a non-empty list
TEST_F(LListStringTest, ConstructorNominal) {
	LListString newList(list);
	EXPECT_EQ("hi", newList.get(0));
	EXPECT_EQ("my", newList.get(1));
	EXPECT_EQ("name", newList.get(2));
	EXPECT_EQ("william", newList.get(3));
	EXPECT_EQ("wang", newList.get(4));
}

// Construct a new list from a non-empty list
TEST_F(LListStringTest, ConstructorOffNominal) {
	LListString newList(list3);
	EXPECT_EQ(0, newList.size());
}

// Test bracket Off nominal within range
TEST_F(LListStringTest, BracketNominal) {
	for(int i = 0; i < list.size(); i++) {
		EXPECT_EQ(list.get(i), list[i]);
	}
}
