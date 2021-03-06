#ifndef LLISTSTRING_H
#define LLISTSTRING_H

#include <string>

class LListString {
 public:

  struct Item {
    std::string val;
    Item *prev;
    Item *next;

    Item() {
      val = "";
      prev = NULL;
      next = NULL;
    }

    Item(std::string input) : val(input) {
      prev = NULL;
      next = NULL;
    }
  };

  /**
   * Default constructor
   */
  LListString();

  /**
   * Destructor
   */
  ~LListString();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at the index given as pos. If the 
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void insert(int pos, const std::string& val);

  /**
   * Removes the value at the index given by pos. If the 
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void remove(int pos);

  /**
   * Overwrites the old value at the index given by pos with val. If the 
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void set(int pos, const std::string& val);

  /**
   * Copy constructor (deep copy)
   */
  LListString (const LListString& other);

  /**
   * Assignment Operator (deep copy)
   */
  LListString& operator= (const LListString& other);

  /**
   * Concatenation operator.  Returns a new list consisting of 
   other appended to this.  Does not modify this.
   */
  LListString operator+ (const LListString& other) const;

  /**
   * Access Operator
   */
  std::string const & operator[] (int pos) const;

  /**
   * Returns the value at the index given by pos
   */
  std::string& get(int pos);

  /**
   * Returns the value at the index given by pos
   */
  std::string const & get(int pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();

 private:

  /** 
   * Returns a pointer to the item at the index given by pos
   *  and NULL for an invalid position
   */
  Item* getNodeAt(int pos) const;

  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif
