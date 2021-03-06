#include "lliststring.h"
#include <cstdlib>
#include <stdexcept> // See the comment directly below.

/**
 * This implementation uses exceptions in both versions of 'get'. 
 * You do not need to change the if-statements that use exceptions, 
 * nor do you need to test for exceptions. 
 *
 * In case you are interested, you can find more information here:
 * http://www.cplusplus.com/doc/tutorial/exceptions/
 * 
 * We will cover exceptions later this semester. 
 */

LListString::LListString()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListString::~LListString()
{
  clear();
}

bool LListString::empty() const
{
  return (size_ == 0);
}

int LListString::size() const
{
  return size_;
}

void LListString::insert(int pos, const std::string& val)
{
  // TODO: complete the insert function.
  if(pos < 0 || pos > size_) {
    throw std::invalid_argument("bad location");
  }

  // Make new node if not invalid position
  Item* newNode = new Item();
  newNode->val = val;

  // If list is empty
  if(size_ == 0 && pos == 0) {
    head_ = newNode;
    head_->prev = NULL;
    head_->next = NULL;
    tail_ = head_;
    size_++;
  } 

  // If list is not empty and insert at head
  else if(size_ != 0 && pos == 0) {
    newNode->next = head_;
    head_->prev = newNode;
    newNode->prev = NULL;
    head_ = newNode;
    size_++;
  }

  // If list is not empty and insert anywhere else
  else if(size_ != 0 && pos != 0){

    // Insert at the tail
    if(pos == size_) {
      newNode->next = NULL;
      newNode->prev =  tail_;
      tail_->next = newNode;
      tail_ = newNode;
    } else {
        Item* nextNode = getNodeAt(pos);
        Item* prevNode = getNodeAt(pos - 1);
        nextNode->prev = newNode;
        newNode->next = nextNode;
        newNode->prev = prevNode;
        prevNode->next = newNode;
    }

    size_++;
    
  }

  return;

}

void LListString::remove(int pos)
{
  // TODO: complete the remove function.
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }

  // If deleting the head node
  else if(pos == 0) {
    head_ = head_->next;
    if(head_) {
      head_->prev = NULL;
    }
    size_--;
  } 

  // If deleting anywhere else
  else {
    Item* deleteItem = getNodeAt(pos);
    if(deleteItem->next != NULL) {
      deleteItem->next->prev = deleteItem->prev;
      deleteItem->prev->next = deleteItem->next;
    } else {
      deleteItem->prev->next = NULL;
      tail_ = deleteItem->prev;
    }

    size_--;
    delete deleteItem;
  }
}

void LListString::set(int pos, const std::string& val)
{
  if(pos >= 0 && pos < size_) {
  	Item *temp = getNodeAt(pos);
    temp->val = val;	
  }
}

std::string& LListString::get(int pos)
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

std::string const & LListString::get(int pos) const
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

void LListString::clear()
{
  while(head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListString::Item* LListString::getNodeAt(int pos) const
{
  // TODO: complete the getNodeAt function.

    Item* temp = head_;
    int count = 0;

    if(pos == 0) {
      return temp;
    }

    while(count != pos) {

      if(temp->next != NULL) {
        temp = temp->next;
      }
      else {
        temp = NULL;
      }
      count++;
    }

    return temp;

}

