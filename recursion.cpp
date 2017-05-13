/* 106B Recursionn problems */

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "stack.h"
#include "set.h"
#include "lexicon.h"
#include "vector.h"

using namespace std;

/* This is for problem 3 in the text book
 * Use stack of tasks to simulate recursion
 */
struct taskT {
  int n;
  char start;
  char finish;
  char temp;
};


int countHanoiMoves(int n);
void MoveSingleDisk(char start, char finish);
void MoveTower(int n, char start, char finish, char temp);
void moveTowerWithStack();
void processTask(taskT current, Stack<taskT> & tasks);
int countSubsetSumWays(Set<int> & set, int target);
void addEmbeddedWords(Set<string> & set, string target);
bool isMeasurable(int target, Vector<int> & weights);
void differentPermutation(Set<string> & set, string target);
void insertToAllPositions(Vector<Set<string> > & vec, string current, char t);


int main() {

  //cout << countHanoiMoves(3) << endl;

  //MoveTower(3, 'A', 'B', 'C');

  //moveTowerWithStack();

  // Set<int> test;
  // test.add(1);
  // test.add(3);
  // test.add(4);
  // test.add(5);  
  // cout << countSubsetSumWays(test, 11) << endl;

  // Lexicon english("EnglishWords.dat");
  // addEmbeddedWords(set, "happy");  

  Set<string> set;
  Vector<Set<string> > vec;
  //insertToAllPositions(vec, "ABC", 'D');
  differentPermutation(set, "ABCD") ;
  string result = set.toString();
  cout << result << endl;

  // for (string word : set) {
  //   if (english.contains(word)) {
  //     cout << word << endl;
  //   }
  // }

  // Vector<int> sampleWeights;
  // sampleWeights += 1, 3;
  // cout << isMeasurable(5, sampleWeights) << endl;
  
  return 0;
}


/* Function: countHanoiMoves(int n)
 * Usage:    x = countHanoiMoves(n)
 * --------------------------------
 * recursive function that computes 
 * the number of moves required to 
 * solve the Towers of Hanoi puzzle 
 * for n disks.
 * Preconditions:
 * Postconditions:
 * Key insight: to move n+1 disks, 
 * I need to move the top n disks twice
 * and the bottom large disk once, so
 * f(n+1) = 2*f(n) + 1
 */
int countHanoiMoves(int n) {
  if (n == 1) {
    return 1;
  } else {
    return 2*countHanoiMoves(n-1) + 1;
  }
}


void MoveSingleDisk(char start, char finish) {
  cout << start << " -> " << finish << endl;
}


/* the tower algorithm implementation from text book 
 * try different simple case: n == 0 or n == 1;
 */
void MoveTower(int n, char start, char finish, char temp) {
  if (n == 0) {
    //MoveSingleDisk(start, finish);
    
  } else {
    MoveTower(n - 1, start, temp, finish);
    MoveSingleDisk(start, finish);
    MoveTower(n - 1, temp, finish, start);
  }
}


/* Problem 3, text book
 * Use stack to simulate recursion
 */
void moveTowerWithStack() {
  taskT moveTower;
  moveTower.n = 3;
  moveTower.start = 'A';
  moveTower.finish = 'B';
  moveTower.temp = 'C';

  Stack<taskT> tasks;
  tasks.push(moveTower);

  while (!tasks.isEmpty()) {
    taskT current = tasks.pop();
    processTask(current, tasks);
  }
}


/* This is to simulate recursion
 * for simple case, just call moveSingleDisk
 * for more complicated cases, create three new
 * tasks and add them to the stack
 */
void processTask(taskT current, Stack<taskT> & tasks) {
  if (current.n == 1) {
    MoveSingleDisk(current.start, current.finish);
  } else {
    //need to make three new tasks and push them onto the stack
    //the order of which they are pushed on matters
    taskT a;
    a.n = current.n - 1;
    a.start = current.temp;
    a.finish = current.finish;
    a.temp = current.start;
    tasks.push(a);

    taskT b;
    b.n = 1;
    b.start = current.start;
    b.finish = current.finish;
    b.temp = current.temp;
    tasks.push(b);

    taskT c;
    c.n = current.n -1;
    c.start = current.start;
    c.finish = current.temp;
    c.temp = current.finish;
    tasks.push(c);
  }
}


/* Function: countSubsetSumWays
 * Usage:    n = countSubsetSumWays(set, target)
 * ----------------------------------------------
 * Problem 4 in text book
 * Instead of returning true or false for the subset
 * sum problem, this function calculates how many ways
 * the sum can be returned.
 * Precondition:
 * Postcondition:
 */
int countSubsetSumWays(Set<int> & set, int target) {
  if (set.isEmpty()) {
    if (target == 0) {
      return 1;
    } else {
      return 0;
    }
  } else {
    int element = set.first();
    Set<int> rest = set - element;
    return countSubsetSumWays(rest, target) +
      countSubsetSumWays(rest, target-element); 
  }
}


/* Function: addEmbeddedWords
 * Usage:    addEmbeddedWords(set, s)
 * -----------------------------------
 * Problem 5
 * This function adds all string combinations
 * According to rules specified by problem 5
 * To a set. Note the strings added are not necessarily
 * Valid English words. A different function will check 
 * That against lexicon and print out results.
 * Precondition:
 * Postcondition:
 * This one was tricky
 */
void addEmbeddedWords(Set<string> & set, string target) {
  if (target.length() == 1) {
    set.add(target);
    //return;
  } else {
    addEmbeddedWords(set, target.substr(1));

    Set<string> copy;	     //you don't want to change and use
			     //a set at the same time
    for (string current : set) {
      copy.add(current);
      string temp = target[0] + current;
      copy.add(temp);
    }
    set = copy;

    string empty = "";
    set.add(target[0]+empty);	// to avoid old style c string problem
  }
}


/* Function: differentPermutation
 * Usage:    
 * -------------------------------
 * Problem eight
 */
void differentPermutation(Set<string> & set, string target) {
  if (target.length() == 1) {
    set.add(target);
  } else {
    differentPermutation(set, target.substr(1));
    Vector<Set<string> > vec;
    for (string current : set) {
      insertToAllPositions(vec, current, target[0]);
    }

    set.clear();		// hack, make sure the intermidiate strings
				// are not shown
    for (int i = 0; i < vec.size(); i++) {
      set += vec[i];
    }
  }
}


/* Function: insertToAllPositions
 * Usage:
 * ------------------------------
 * Takes a string, add char t to all
 * possible positions of the string
 * and add each combination to a set
 * then add the set to a vector of sets
 */
void insertToAllPositions(Vector<Set<string> > & vec, string current, char t) {
  Set<string> temp;
  string empty = "";
  string x = t + empty;
  for (int i = 0; i <= current.length(); i++) {
    string s = current;
    s.insert(i, x);
    temp.add(s);
  }

  vec.add(temp);
}


/* Function: isMeasurable
 * Usage:    
 * -----------------------
 * Problem six of text book
 * Precondition:
 * Postcondition:
 */
bool isMeasurable(int target, Vector<int> & weights) {
  if (weights.size() == 1) {
    if (target == weights.get(0)) {
      return true;
    } else {
      return false;
    }
  } else {
    int currentWeight = weights.get(0);
    weights.remove(0);
    return isMeasurable(target - currentWeight, weights)
      || isMeasurable(target + currentWeight, weights)
      || isMeasurable(target, weights);
  }
}
