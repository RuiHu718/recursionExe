/* 106B Recursionn problems */

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "stack.h"
#include "set.h"
#include "lexicon.h"
#include "vector.h"
#include "gwindow.h"
#include "random.h"
#include "gobjects.h"

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


/* Constants */
const double MIN_AREA = 10000;	// Smallest square that will be split
const double MIN_EDGE = 20;	// Smallest edge length allowd
const double HALF_INCH_TICK = 20;


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
string digitLetter(char ch);
void listMnemonics(string str);
void recursiveMnemonics(string prefix, string rest);
void listCompletions(string digits, Lexicon & lex);
void recursiveMnemonicsEnglish(string prefix, string rest, Lexicon & lex);
void expandWords(string word, Lexicon & lex);
void subdivideCanvas(GWindow & gw, double x, double y,
		     double width, double height);
void drawRuler(double x, double y, double w, double h, GWindow & gw);
bool solvable(int start, Vector<int> & squares);
void writeChar(int n);
bool isSubsequence(string big, string small);

bool canOfferUniversalCoverage(Set<string>& cities,
			       Vector< Set<string> >& locations,
			       int numHospitals,
			       Vector< Set<string> >& result);

void generateNewSet(Set<string> & set);
Set<string> generateInsertions(string s);
Set<string> generateDeletions(string s);
Set<string> generateChanges(string s);
int editDistance(string s1, string s2);
void myEditDistance(int & n, string target, Set<string> & set);
bool isBalanced(string s);


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


  // addEmbeddedWords(set, "happy");  

  // Set<string> set;
  // Vector<Set<string> > vec;
  //insertToAllPositions(vec, "ABC", 'D');
  // differentPermutation(set, "ABCD") ;
  // string result = set.toString();
  // cout << result << endl;

  // for (string word : set) {
  //   if (english.contains(word)) {
  //     cout << word << endl;
  //   }
  // }

  // Vector<int> sampleWeights;
  // sampleWeights += 1, 3;
  // cout << isMeasurable(5, sampleWeights) << endl;

  //listMnemonics("72547");

  // Lexicon english("EnglishWords.dat");
  // listCompletions("72547", english);
  //expandWords("rakis", english);

  //GWindow gw;
  //drawRuler(gw.getWidth() - 5, gw.getHeight() / 2,
  //	    10, HALF_INCH_TICK, gw);
  //drawRuler(0, 100, 100, HALF_INCH_TICK, gw);
  //gw.add(new GLine(0, 0, gw.getWidth(), gw.getHeight()));
  //gw.add(new GLine(0, gw.getHeight(), gw.getWidth(), 0));

  //subdivideCanvas(gw, 0, 0, gw.getWidth(), gw.getHeight());

  // Vector<int> test;
  // test.add(3);
  // test.add(6);
  // test.add(4);
  // test.add(1);
  // test.add(3);
  // test.add(4);
  // test.add(2);
  // test.add(5);
  // test.add(3);
  // test.add(0);  
  // cout << solvable(1, test) << endl;

  //writeChar(9);

  //cout << isSubsequence("ccmputer", "ccpe") << endl;


  Set<string> cities;
  cities += "A";
  cities += "B";
  cities += "C";
  cities += "D";
  cities += "E";
  cities += "F";  

  Vector<Set<string> > locations;
  Set<string> temp;
  temp += "A";
  temp += "B";
  temp += "C";
  locations.add(temp);

  temp.clear();
  temp += "A";
  temp += "C";
  temp += "D";
  locations.add(temp);

  temp.clear();
  temp += "B";
  temp += "F";
  locations.add(temp);

  temp.clear();
  temp += "C";
  temp += "E";
  temp += "F";
  locations.add(temp);

  //cout << cities.toString() << endl;
  //cout << locations.toString() << endl;
  // Vector<Set<string> > result;
  
  // cout << canOfferUniversalCoverage(cities, locations, 3, result) << endl;
  // cout << result.toString() << endl;


  // Set<string> test;
  // test += "hello";
  //generateNewSet(test);
  //cout << test.toString() << endl;
  //cout << test.contains("hello") << endl;
  // int n = 0;
  // myEditDistance(n, "bhllo", test);
  // cout << n << endl;

  // string s1 = "football";
  // string s2 = "cookies";
  // cout << editDistance(s1, s2) << endl;

  cout << isBalanced("()[]{}{[()]}") << endl;
  
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


/* Function: digitLetter(char ch)
 * Usage:    string s = digitLetter('A')
 * -------------------------------------
 * Part of problem ten from the text book
 * Given a number, returns a string according
 * To the phone dial pad
 * Precondition:
 * Postcondition:
 */
string digitLetter(char ch) {
  switch(ch) {
  case '0' : return ("0");
  case '1' : return ("1");
  case '2': return ("ABC");
  case '3': return ("DEF");
  case '4': return ("GHI");
  case '5': return ("JKL");
  case '6': return ("MNO");
  case '7': return ("PRS");
  case '8': return ("TUV");
  case '9': return ("WXY");
  default:  return ("Illegal digit"); // this is not right
  }
}


/* Function: listMnemonics(string str)
 * Usage:    listMnemonics("2154")
 * -----------------------------------
 * Problem ten, wrapper function
 */
void listMnemonics(string str) {
  recursiveMnemonics("", str);
}


/* Function: recursiveMnemonics(string prefix, string rest)
 * Usage:    recursiveMnemonics("", "1234")
 * ---------------------------------------------------------
 * Problem ten, heavy lifting here
 * Precondition:
 * Postcondition:
 */
void recursiveMnemonics(string prefix, string rest) {
  if (rest == "") {
    cout << prefix << endl;
  } else {
    string options = digitLetter(rest[0]);
    for (int i = 0; i < options.length(); i++) {
      recursiveMnemonics(prefix+options[i], rest.substr(1));
    }
  }
}


/* Function: listCompletions(string digits, Lexicon & lex)
 * Usage:    listCompletions("12345", english)
 * --------------------------------------------------------
 * Problem eleven
 */
void listCompletions(string digits, Lexicon & lex) {
  recursiveMnemonicsEnglish("", digits, lex);
}


/* Function: recursiveMnemonicsEnglish(string prefix, string rest, Lexicon & lex)
 * Usage:    recursiveMnemonicsEnglish("", "12345", english)
 * -------------------------------------------------------------------------------
 * Problem eleven, heavy lifting here
 */
void recursiveMnemonicsEnglish(string prefix, string rest, Lexicon & lex) {
  if (rest == "") {
    expandWords(prefix, lex);
  } else {
    string options = digitLetter(rest[0]);
    for (int i = 0; i < options.length(); i++) {
      recursiveMnemonicsEnglish(prefix+options[i], rest.substr(1), lex);
    }
  }
}


/* Function: expandWords(string word, Lexicon & lex) 
 * Usage:    expandWords("rakis", english)
 * -------------------------------------------------
 * Helper function for problem eleven
 * Given a prefix, expand it by trying all letter combinations
 * The recursion will terminate when the current string can't possiblely
 * Form a valid word.
 */
void expandWords(string word, Lexicon & lex) {
  if (!lex.containsPrefix(word)) {
    return; 			// recursion ends here
  } else {
    if (lex.contains(word)) {
      cout << word << endl;
    }

    string allLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < allLetters.length(); i++) {
      string newWord = word + allLetters[i];
      expandWords(newWord, lex);
    }

  }
}


/* Function: subdivideCanvas
 * Usage:    subdivideCanvas(gw, x, y, width, height);
 * ---------------------------------------------------
 * Decomposes the specified rectangular region on the canvas recursively
 * by splitting that rectangle randomly along its larger dimention. 
 */
void subdivideCanvas(GWindow & gw, double x, double y,
		     double width, double height) {
  if (width * height >= MIN_AREA) {
    if (width > height) {
      double mid = randomReal(MIN_EDGE, width - MIN_EDGE);
      subdivideCanvas(gw, x, y, mid, height);
      subdivideCanvas(gw, x + mid, y, width - mid, height);
      gw.drawLine(x + mid, y, x + mid, y + height);
    } else {
      double mid = randomReal(MIN_EDGE, height - MIN_EDGE);
      subdivideCanvas(gw, x, y, width, mid);
      subdivideCanvas(gw, x, y + mid, width, height - mid);
      gw.drawLine(x, y + mid, x + width, y + mid);
    }
  }
}


/* Function: drawRuler
 * Usage:    drawRuler(10, 10, 20, 20);
 * --------------------------------------------------
 * Problem 14 of the text book
 * similar to binary search in essence
 */
void drawRuler(double x, double y, double w, double h, GWindow & gw) {
  gw.add(new GLine(x, y, x + w, y));
  if (h > HALF_INCH_TICK / 16) {
    gw.add(new GLine(x + w/2, y, x + w/2, y + h));
    drawRuler(x, y, w/2, h / 2, gw);
    drawRuler(x + w/2, y, w / 2, h / 2, gw);
  }
}


/* Function: solvable
 * Usage:    bool x = solvable(0, squares)
 * ---------------------------------------
 * Professor Zelenski's assignment 3, problem 5
 * Precondition:
 * Postcondition:
 * For myself: seems to work, but need to test some more
 * the recursive insight is this: at every step you have two
 * choices, and you should try them both, each one will either
 * lead you to the goal or reach a dead end. Dead end can be defined
 * in the following ways: index out of bounds, or reach a square which
 * has been visited before. 
 */
bool solvable(int start, Vector<int> & squares) {
  Vector<int> temp = squares;
  if ((start > temp.size() - 1) || (start < 0)) {
    return false;
  }
  if (temp[start] == 0) {
    return true;
  } else if (temp[start] == -1) {
    return false;
  } else {
    int value = temp[start];
    temp.set(start, -1);	// mark the current square as visited
    return solvable(start + value, temp) || solvable(start - value, temp);
  }
}


/* Function: writeChar
 * Usage:    writeChar(9)
 * -----------------------
 * Section practice
 */
void writeChar(int n) {
  if (n < 1) {
    throw "Invalid input.";
  } else if (n == 1) {
    cout << "*";
  } else if (n == 2) {
    cout << "**";
  } else {
    cout << "<";
    writeChar(n - 2);
    cout << ">";
  }
}


/* Function: isSubsequence
 * Usage;    bool x = isSubsequence("computer", "com")
 * ----------------------------------------------------
 * Section practice
 */
bool isSubsequence(string big, string small) {
  if (small == "") {
    return true;
  } else {
    int index = big.find(small[0]);
    if (index == string::npos) {
      return false;
    } else {
      return isSubsequence(big.substr(index + 1), small.substr(1));
    }
  }
}


/* Function: canOfferUniversalCoverage
 * Usage:    
 * -----------------------------------
 * Assignment problem from 106B 2013
 * Precondition
 * Postcondition
 * Remain: I don't think the current implementation of the result part
 * is correct, test and fix this.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
			       Vector< Set<string> >& locations,
			       int numHospitals,
			       Vector< Set<string> >& result) {

  if (numHospitals == 0) {	// there was a bug here, the order of which
				// the first two if tests appears, think about
				// this some more
    if (cities.isEmpty()){
      return cities.isEmpty();
    } else {
      result.remove(result.size() - 1);
      return cities.isEmpty();
    }
  } else if (locations.size() == 0) {
    result.remove(result.size() - 1);    
    return false;
  } else {
    Vector<Set<string> > temp = locations;
    Vector<Set<string> > temp2 = locations;    
    temp.remove(0);
    temp2.remove(0);
    Set<string> copy = cities;

    //Vector<Set<string> > resultTemp = result;
    result.add(locations[0]);

    return canOfferUniversalCoverage(copy -= locations[0], temp2,
    				     numHospitals - 1, result)
      || canOfferUniversalCoverage(cities, temp, numHospitals, result);
  }
}

 
/* Function: generateNewSet
 * Usage:    generateNewSet(set);
 * ------------------------------
 * Generates a new set of strings according to the following rule:
 * for each string in the original set, expand it in three ways: insert
 * change, and remove. Note we are only making one step change here. 
 * The result will be all strings that are one distance away from the
 * original strings. The original strings are not kept.
 * Parameters and return values:
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */
void generateNewSet(Set<string> & set) {
  Set<string> result;
  for (string s : set) {
    result += generateInsertions(s);
    result += generateDeletions(s);
    result += generateChanges(s);
  }

  set.clear();
  set = result;
}


/* Function: generateInsertions
 * Usage:    set = generateInsertions("hello");
 * --------------------------------------------
 * Given a string, generates a set of new strings which
 * are one insertion away from the original string.
 * Parameters and return values
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */
Set<string> generateInsertions(string s) {
  Set<string> result;
  for (int i = 0; i <= s.length(); i++) {
    for (int j = 0; j < 26; j++) {
      string temp = s;
      char ch = 'a' + j;
      string empty = "";
      result.add(temp.insert(i, empty + ch));
    }
  }

  return result;
}


/* Function: generateDeletions
 * Usage:    set = generateDeletions("hello");
 * --------------------------------------------
 * Given a string, generates a set of new strings which
 * are one deletion away from the original string.
 * Parameters and return values
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */
Set<string> generateDeletions(string s) {
  Set<string> result;
  for (int i = 0; i < s.length(); i++) {
    string temp = s;
    result.add(temp.erase(i, 1));
  }

  return result;
}


/* Function: generateChanges
 * Usage:    set = generateChanges("hello");
 * --------------------------------------------
 * Given a string, generates a set of new strings which
 * are one change away from the original string.
 * Parameters and return values
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */
Set<string> generateChanges(string s) {
  Set<string> result;
  for (int i = 0; i < s.length(); i++) {
    for (int j = 0; j < 26; j++) {
      string temp = s;
      char ch = 'a' + j;
      string empty = "";
      result.add(temp.replace(i, 1, empty + ch));
    }
  }

  return result;
}


/* Function: editDistance
 * Usage:    n = editDistance("hello", "aello");
 * ---------------------------------------------
 * 106X section problem
 * Parameters and return values
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */

// int editDistance(string s1, string s2) {
//   int n = 0;
//   Set<string> set;
//   set += s1;
//   myEditDistance(n, s2, set);

//   return n;
// }


/* Function: myEditDistance
 * Usage:    myEditDistance(n, target, set);
 * ---------------------------------------------
 * 106X section problem
 * Parameters and return values
 * Preconditions:
 * Postconditions:
 * Assumptions:
 */
void myEditDistance(int & n, string target, Set<string> & set) {
  if (set.contains(target)) {
    return;
  } else {
    generateNewSet(set);
    n++;
    myEditDistance(n, target, set);
  }
}


/* This came from section solution
 * I still don't quite understrand this 
 * TODO: figure this one out
 */

int editDistance(string s1, string s2) {
  if (s1 == "") {
    return s2.length();
  } else if (s2 == "") {
    return s1.length();
  }
  // try three possibilities for the "zeroth" character:
  int add = 1 + editDistance(s1, s2.substr(1));
  int del = 1 + editDistance(s1.substr(1), s2);
  int sub = editDistance(s1.substr(1), s2.substr(1));
  if (s1[0] != s2[0]) {
    sub += 1;
  }
  return min(add, min(del, sub));
}


/* Function: isBalanced
 * Usage:    isBalanced("{}()")
 * --------------------------------
 * Strategy: a string is balanced if it meets one the following two conditions:
 * 1. it is empty string
 * 2. it contains "()", "[]", or "{}" as substring AND if you remove "()", "[]"
 * or "{}" from the original string, then the new string is still balanced
 */
bool isBalanced(string s) {
  if (s == "") {
    return true;
  } else {
    int n = -1;
    if (s.find("()") != string::npos) {
      n = s.find("()");
    }
    if (s.find("[]") != string::npos) {
      n = s.find("[]");
    }
    if (s.find("{}") != string::npos) {
      n = s.find("{}");
    }
    
    return (n != -1) && isBalanced(s.erase(n, 2));
  }
}
