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


int main() {

  //cout << countHanoiMoves(3) << endl;
  //MoveTower(3, 'A', 'B', 'C');
  moveTowerWithStack();
  
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
