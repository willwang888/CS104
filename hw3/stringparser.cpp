#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "stackstring.h"

using namespace std;

// Check if good character
bool isGood(char c) {
  if((c >= 'a' && c <= 'z') || c == '<' || c == '>'|| c == '+' || 
    c == '-' || c == '(' || c == ')' || c == ' ') {
    return true;
  } 
  return false;
}

// Run tests on the line to see if it's not malformed
bool isGoodLine(string line) {
  int openParenCount = 0;
  int closeParenCount = 0;
  int letterCount = 0;
  bool isOpenParen = false;
  bool isCloseParen = false;
  int operationPlus = 0;
  int operationMinus = 0;

  for(unsigned int i = 0; i < line.size(); i++) {
    // If line has uppercase letters or anything other than good operations,
    // return false
    if(!isGood(line[i])) {
      return false;
    }

    if(isalpha(line[i])) {
      letterCount++;
    }

    // Check if no more than 1 of the same operation between parentheses
    if(line[i] == '(') {
      openParenCount++;
      isOpenParen = true;
      isCloseParen = false;
      if((operationMinus > 1) || (operationMinus >= 1 && operationPlus >= 1)) {
        return false;
      } 
      operationMinus = 0;
      operationPlus = 0;
    } else if(line[i] == ')') {
      closeParenCount++;
      isOpenParen = false;
      isCloseParen = true;
      if((operationMinus > 1) || (operationMinus >= 1 && operationPlus >= 1)) {
        return false;
      }
      operationMinus = 0;
      operationPlus = 0;
    }

    if(isOpenParen || isCloseParen) {
      if(line[i] == '+') {
        operationPlus++;
      } else if(line[i] == '-') {
        operationMinus++;
      } 
    }

    if((line[i] == '<' || line[i] == '>') && i > 0) {
      if(isalpha(line[i - 1])) {
        return false;
      }
    }

    // If two operations are next to each other, or if operation is right before 
    // closed brackets, // return false
    if((line[i] == '+' || line[i] == '-') && (i > 0 && i < line.size() - 1)) {
      if(line[i + 1] == '+' || line[i + 1] == '-' || line[i + 1] == ')' || 
        line[i - 1] == '(') {
        return false;
      }
    }

  }

  // If last or first element is an operation, return false
  if(line[0] == '+' || line[0] == '-' || isalpha(line[0]) || 
    line[line.size() - 1] == '+' || line[line.size() - 1] == '-' || 
    isalpha(line[line.size() - 1])) {
    return false;
  }

  // If lines has no letters in it, return false
  if(letterCount == 0) {
    return false;
  }

  // Check if correct number of parentheses and if there ARE parentheses
  if(openParenCount == closeParenCount && 
    (openParenCount != 0 && closeParenCount != 0)) {
    return true;
  } else {
    return false;
  }

}

// Subtract two strings
string subract(string& one, string& two) {
  // Find position of the substring in the first string
  int position = one.find(two);
  int length = two.size();

  try {
    one.erase(position, length);
  } catch (std::out_of_range notInRange){
  }
  return one;
}

// Cut first character off the string
string cutFirst(string& one) {
  one.erase(one.begin());
  return one;
}

// Cut last character off the string
string cutLast(string& one) {
  one.erase(one.size() - 1);
  return one;
}

// Test if the current string is an operation
bool isOperation(const string& test) {
  if(test == "<" || test == ">" || test == "+" || test == "-") {
    return true;
  }
  else {return false;}
}

// Evalutate current operation
string evaluateOp(string& first, string& second, string& op) {

  switch(op[0]) {
    case '+':
      first += second;
      break;
    case '-':
      first = subract(first, second);
      break;
    case '<':
      cutLast(first);
      break;
    case '>':
      cutFirst(first);
      break;
  }
  return first;
}

// Evaluate carrots on a string
string carrotOperator(int countLeftPoint, int countRightPoint, string& test) {
  for(int i = 0; i < countLeftPoint; ++i) {
    cutLast(test);
  }

  for(int i = 0; i < countRightPoint; ++i) {
    cutFirst(test);
  }

  return test;
}

// Check if the stack has only carrots and letters
bool hasCarrotLetters(StackString inputStack) {
  StackString temp;
  string tempString;
  while(!inputStack.empty()) {
    tempString = inputStack.top();
    temp.push(tempString);
    if(tempString != "<" && tempString != ">" && !isalpha(tempString[0])) {
      return false;
    }
    inputStack.pop();
  }
  return true;
}

// Main evaluation function: Will perform double stack 
// evaluation on word and op stacks
string evaluate(ofstream& output, StackString& inputWordStack, 
  StackString& inputOpStack, StackString& tempStack, StackString& myStack, 
  string& final, int& myCount, int& tempCount,
  int& wordCount, int& opCount) {

  string eval1;
  string evalOp;
  string eval2;
  int counting = 0;

  // If it's closed parentheses, evaluate the two stacks and 
  // push it back onto the temp stack
  while(!inputWordStack.empty() && !inputOpStack.empty()) {
    counting++;
    if(counting >= 2) {
      evalOp = inputOpStack.top();
      inputOpStack.pop();
      opCount--;
      eval2 = inputWordStack.top();
      inputWordStack.pop();
      wordCount--;
      final = evaluateOp(eval2, final, evalOp);
    }
    else {
      eval1 = inputWordStack.top();
      inputWordStack.pop();
      wordCount--;
      evalOp = inputOpStack.top();
      inputOpStack.pop();
      opCount--;
      eval2 = inputWordStack.top();
      inputWordStack.pop();
      wordCount--;
      final = evaluateOp(eval2, eval1, evalOp);
    }
  }

  // While the wordstack is not empty, empty it
  while(!inputWordStack.empty() && inputOpStack.empty()){
    final = inputWordStack.top();
    inputWordStack.pop();
    wordCount--;
  }

  // After evaluating both stacks, push back onto myStack
  myStack.push(final);
  myCount++;

// --------- IF MYSTACK ONLY HAS CARROTS AND LETTERS LEFT, EVALUATE ------ //
  if(hasCarrotLetters(myStack)) {
    while(!myStack.empty()) {
      tempStack.push(myStack.top());
      tempCount++;
      myStack.pop();
      myCount--;
    }

    int leftCounter = 0;
    int rightCounter = 0;
    while(tempCount != 0) {
        string part1;

// ------------- RETRIEVE FIRST THING IN THE TEMP STACK ---------- //
        part1 = tempStack.top();
        tempStack.pop();
        tempCount--;

// ------ IF FIRST THING IS A CARROT OPERATOR, COUNT THEM------ //
        if(part1 == "<" || part1 == ">") {
          if(part1 == "<") {
            leftCounter++;
          } else if(part1 == ">") {
            rightCounter++;
          }
          // While the next operator is still a carrot, keep a count of carrots
          while(tempStack.top() == "<" || tempStack.top() == ">" ) {
            if(tempStack.top() == "<") {
              leftCounter++;
            } else if(tempStack.top() == ">") {
              rightCounter++;
            }
            tempStack.pop();
            tempCount--;
          }
// ------------- CARROTS DONE COUNTING ------------ //
          part1 = tempStack.top();
          final = carrotOperator(leftCounter, rightCounter, part1);
        }
      }
    }
  return final;
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  string curr;

  // Get whole line
  while(getline(input, curr)) {
    stringstream ss(curr);
    string newString;
    string buffer = "";
    char c; 
    string toEnd = "";
    string final = "";
    int myCount = 0;
    int tempCount = 0;
    int wordCount = 0;
    int opCount = 0;

    StackString myStack;
    StackString tempStack;
    StackString opStack;
    StackString wordStack;

// ---------- Check if the whole line is good or not ---------- //
    if(isGoodLine(curr)) {

      // Get up until first white space, PUSH EVERYTHING ONTO MYSTACK
      while(ss >> newString) {
        unsigned int i = 0;

        // Cycle through the newString to get individual characters
        while(i < newString.size()) {
          // Assign c the current value of newString
          c = newString[i];
          i++;

// --- PUSH STRING TO MYSTACK UNTIL END PARENTHESES IS FOUND ---- //
          if((c != ')') && (c == '<' || c == '>' || c == '+' || 
            c == '-' || c == '(')) {
            
            if(buffer.size() != 0) {
              myStack.push(buffer);
              myCount++;
              buffer = "";
            }

            string toPush = "";
            toPush += c;
            myStack.push(toPush);
            myCount++;
          } 

          else if(isalpha(c)) {
            buffer += c;
          }

// ---------- IF END PARENTHESES IN MYSTACK FOUND ---------- // 
          else if(c == ')') {
            if(buffer != toEnd) {
                myStack.push(buffer);
                myCount++;
                buffer = "";
            }            

// ------- WHILE TOP STRING IS NOT EQUAL TO (---------//
            while(myStack.top() != "(") {
                if(myStack.top() == "") {
                  myStack.pop();
                  myCount--;
                }
                string pushing = myStack.top();
                myStack.pop();
                myCount--;
                tempStack.push(pushing);
                tempCount++;
            }
// -------- IF FOUND OPEN PARENTHESES (------- //

            // Take out open parentheses when I see them
            myStack.pop();
            myCount--;

            // Start "result" as empty string
            string result = "";
            int leftCounter = 0;
            int rightCounter = 0;

            while(tempCount != 0) {
              string part1;
              string part2;
              string part3;

// ---------- RETRIEVE FIRST THING IN THE TEMP STACK ---------- //
              part1 = tempStack.top();
              tempStack.pop();
              tempCount--;

// ----------- IF FIRST THING IS A CARROT OPERATOR----------- //
              leftCounter = 0;
              rightCounter = 0;
              if(part1 == "<" || part1 == ">") {
                if(part1 == "<") {
                  leftCounter++;
                } else if(part1 == ">") {
                  rightCounter++;
                }

                // While the next operator is still a carrot
                while(tempStack.top() == "<" || tempStack.top() == ">" ) {
                  if(tempStack.top() == "<") {
                    leftCounter++;
                  } else if(tempStack.top() == ">") {
                    rightCounter++;
                  }
                  tempStack.pop();
                  tempCount--;
                }
// ------- CARROTS DONE COUNTING, GET NEXT STRING ------------ //
                part1 = tempStack.top();

// --------IF THE NEXT STRING IS A PARENTHESE ------------- //
                if(part1 == "(") {
                  for (int j = 0; j < leftCounter; ++j) {
                    opStack.push("<");
                    opCount++;
                  } 

                  for(int j = 0; j < rightCounter; ++j) {
                    opStack.push(">");
                    opCount++;
                  }
                }

// ------  IF THE NEXT STRING IS NOT A PARENTHESIS, THEN IT'S A WORD ----- //
                else if(!isOperation(part1) && part1 != ")" && part1 != "(") {
                  // Evaluate the expression and push onto word stack
                  toEnd = part1;
                  part1 = carrotOperator(leftCounter, rightCounter, part1);

                  // Push onto the word stack and take out of temp stack
                  wordStack.push(part1);
                  wordCount++;
                  tempStack.pop();
                  tempCount--; 

                  // If after the carrot expression is an operator, push it 
                  // onto the operator stack
                  if(tempCount != 0) {
                    if(isOperation(tempStack.top())) {
                      opStack.push(tempStack.top());
                      opCount++;
                      tempStack.pop();
                      tempCount--; 
                    } 
                  } 
                }
              }
// ------------ IF PART1 IS A STRING OF LETTERS AND NOT CARROT ------//
              else {
                // If part 1 is NOT a + or -, then push onto word stack, 
                // else push onto opStack
                if(!isOperation(part1)) {
                  wordStack.push(part1);
                  wordCount++; 
                } else {
                  opStack.push(part1);
                  opCount++;
                }

                // If there is still something in the tempStack
                if(tempCount != 0) {
                  part2 = tempStack.top();

                  if(isOperation(part2)) {
                    opStack.push(part2);
                    opCount++;
                  } else {
                    wordStack.push(part2);
                    wordCount++;
                  }
                  tempStack.pop();
                  tempCount--;
                }
              }
            }
// --------------- EVALUATE EVERYTHING HERE ------------- //
            final = evaluate(output, wordStack, opStack, tempStack, myStack, 
              final, myCount, tempCount, wordCount, opCount);          
          }
          }
        }
        output << final << endl;
      } 
      
      else {
        output << "Malformed" << endl;
      }
  }
  return 0;
}