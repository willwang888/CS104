#include <iostream>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void split (Node*& in, Node*& odds, Node*& evens) {
	// Base case
	if(in == NULL) {
		return;
	}

	Node* next = in->next;

	if(in->value % 2 != 0) {
		// Make a new list of odds
		Node* newOdd = in;
		newOdd->next = odds;
		odds = newOdd;
	} else if(in->value % 2 == 0) {
		// Made a new list of events
		Node* newEven = in;
		newEven->next = evens;
		evens = newEven;
	}

	in = next;

	split(in, odds, evens);
}

int main() {
	Node* head = NULL;

	// List of numbers 1 - 10
	for(int i = 1; i < 10; i++) {
		Node* newNode = new Node();
		newNode->next = head;
		newNode->value = i;
		head = newNode;
	}

	Node* evens = NULL;
	Node* odds = NULL;

	split(head, odds, evens);

	return 0;
}