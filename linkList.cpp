/* Linked list problems
   1. buildOneTwoThree
   2. length(): iterative version
   3. length(): recursive version
   4. push():   add node to head
   5. addToTail(): add node to tail
   6. printList();
   7. copyList():  iterative version
   8. copyList():  recursive version
 */



#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
using namespace std;

struct node {
  int data;
  struct node *next;
};

node *buildOneTwoThree();
int length(node *head);
int recLength(node *head);
void push(node* & head, int data);
void addToTail(node *head, int data);
void printList(node *head);
node *copyList(node *head);
node *recCopyList(node *head);

int main()
{

  node *testList = NULL;
  
  testList = buildOneTwoThree();
  addToTail(testList, 4);
  printList(testList);
  cout << endl;
  node *copy = copyList(testList);
  printList(copy);


  return 0;
}


node *buildOneTwoThree()
{
  node *head = NULL;
  node *second = NULL;
  node *third = NULL;

  head = new node;
  second = new node;
  third = new node;

  assert (head != NULL);
  head -> data = 1;
  head -> next = second;

  assert (second != NULL);
  second -> data = 2;
  second -> next = third;

  assert (third != NULL);
  third -> data = 3;
  third -> next = NULL;

  // what do second and third look like now?
  // should make them null
  
  return head;
}

int length(node *head) 
{
  int count = 0;
  node *cur = NULL;
  for (cur = head; cur != NULL; cur = cur -> next) {
    count++;
  }

  return count;
}

void printList(node *head) 
{
  for (node *cur = head; cur != NULL; cur = cur -> next) {
    cout << cur -> data << endl;
  }
}

/* Same length function, uses recursion */
int recLength(node *head)
{
  if (head == NULL) {
    return 0;
  } else {
    return 1 + recLength(head->next);
  }
}  

/* Given a linked list and data, add a new node to front of list */
void push(node* & head, int data)
{
  node *newElement = new node;
  newElement -> data = data;

  newElement -> next = head;
  head = newElement;
}  

/* Given a linked list and data, add a new node to tail of list */
void addToTail(node *head, int data)
{
  node *newElement = new node;
  newElement -> data = data;
  node *cur = NULL;
  //node *prev = NULL;

  if (head == NULL) {		// special case of empty list 
    head = newElement;
    newElement -> next = NULL;
  }
  
  // for (node *cur = head; cur!= NULL; cur = cur -> next) {
  //   prev = cur;
  // }

  for (cur = head; cur -> next != NULL; cur = cur -> next) {
    
  }
  
  cur -> next = newElement;
  newElement -> next = NULL;
}  

/* Makes an exact copy of the list, deep copying, not shallow copying */
node *copyList(node *head)
{
  node *current = head;
  node *newList = NULL;
  node *tail = NULL;		// always point to the last node of new list

  while (current != NULL) {
    if (newList == NULL) {	// the first element
      newList = new node;
      newList -> data = current -> data;
      newList -> next = NULL;
      tail = newList;
    } else {
      tail -> next = new node;
      tail = tail -> next;
      tail -> data = current -> data;
      tail -> next = NULL;
    }

    current = current -> next;
  }

  return newList;
}  

node *recCopyList(node *head)
{
  

}  
