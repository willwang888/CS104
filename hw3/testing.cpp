#include "lliststring.h"
#include <iostream>

using namespace std;

int main() {
  LListString* list = new LListString();   

  int size = 0;

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, "Gandalf");
  size++;

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == "Gandalf") {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // TODO: Continue adding tests for your program, or start your own file with your
  // own tests. Remember to submit a file that is named correctly!

  list->insert(1, "hello");
  size++;
  list->insert(2, "my");
  size++;
  list->insert(3, "name");
  size++;
  list->insert(4, "is");
  size++;
  list->insert(5, "william");
  size++;
  list->insert(6, "wang");
  size++;

  cout << "List has size " << list->size() << " after one insertion." << endl;
  cout << "1 IN THE LIST IS: " << list->get(1) << endl;

  string val;

  list->remove(4);
  size--;
  list->remove(2);
  size--;
  list->insert(2, "hiasldkfjlasd");
  size++;
  list->insert(5, "HUSADFKHASD");
  size++;
  list->remove(5);
  size--;

  for(int i = 0; i < list->size(); i++) {
    val = list->get(i);
    cout << i << " INDEX IS: " << val << endl;
  }

  cout << "List size is: " << size << endl;
  cout << "List size should be: " << 6 << endl;

  // TEST COPY CONSTRUCTOR
  LListString* list2 = new LListString(*list);

  cout << "LIST TWO IS: " << endl;

  for(int i = 0; i < list2->size(); i++) {
    val = list2->get(i);
    cout << i << " INDEX IS: " << val << endl;
  }

  LListString* list3 = new LListString(list + *list2);

  cout << "LIST THREE IS: " << endl;

  for(int i = 0; i < list3->size(); i++) {
    val = list3->get(i);
    cout << i << " INDEX IS: " << val << endl;
  }

  *list2 = *list3;

  cout << "THE NEW LIST TWO IS: " << endl;

  for(int i = 0; i < list2->size(); i++) {
    val = list2->get(i);
    cout << i << " INDEX IS: " << val << endl;
  }

  cout << "list3[0] is: " << (*list3)[0] << endl;
  cout << "EXPECTED: Gandalf" << endl;

  // Clean up memory.
  delete list;
  delete list2;
  delete list3;

  return 0;
}