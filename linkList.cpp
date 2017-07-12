/* Linked list problems
   1. buildOneTwoThree
   2. length(): iterative version
   3. length(): recursive version
   4. push():   add node to head
   5. addToTail(): add node to tail
   6. printList();
   7. copyList():  iterative version
   8. copyList():  recursive version
   9. deAllocate():don't forget recursive version
   10 insert():    in sorted order, iterative version, pending
   11 insert():    in sorted order, recursive version, pending
   12 deleteFromList():   pending
 */

/* Nick's linked list problems
   1. count(): return the number of times an int occurs in a list
   2. getNth(): return the nth element of the list
   3. deleteList(): deallocates all the memory and sets head to null
   4. pop():    return head node data, delete head node, makes head node point to next
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
int count(node *head, int searchFor);
int getNth(node *head, int index);
void deleteList(node *head);
void recDeleteList(node *head);
int pop(node* & head);
void insertNth(node* & head, int index, int data);

int main()
{

  node *testList = NULL;
  
  //testList = buildOneTwoThree();
  insertNth(testList, 0, 13);
  insertNth(testList, 0, 100);

  insertNth(testList, 1, 42);
  
  insertNth(testList, 1, 5);
  insertNth(testList, 4, 27);
  printList(testList);



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
  if (head == NULL) {
    return NULL;
  } else {
    node *cur = new node;
    cur -> data = head -> data;
    cur -> next = recCopyList(head -> next);
    return cur;
  }
}  

int count(node *head, int searchFor)
{
  int count = 0;
  for (node *cur = head; cur != NULL; cur = cur -> next) {
    if ((cur -> data) == searchFor) {
      count++;
    }
  }

  return count;
}  


int getNth(node *head, int index)
{

  int count = 0;
  for (node *cur = head; cur != NULL; cur = cur -> next) {
    if (count == index) {
      return cur -> data;
    }
    count++;
  }

  assert(0);  			// if we get here, then the client asked an index
				// that was out of bounds
}  


void deleteList(node *head)
{
  while (head != NULL) {
    node *next = head -> next;
    delete head;
    head = next;
  }

  head = NULL;
}  


// see how compact this is?
void recDeleteList(node *head)
{
  if (head != NULL) {
    recDeleteList(head -> next);
    delete head;
  }
}  


/* pop() returns the data head point to, delete that cell and move head
 * to point to the next cell. Note head is passed by reference here so 
 * you can modify it. 
 */
int pop(node* & head)
{
  assert (head != NULL);
  int result = head -> data;
  node* temp = head;
  head = head -> next;
  delete temp;
  return result;
}  


/* insertNth() inserts a new cell with content of data at the Nth place of the list
 * valid range of index is [0 .. length], pay attention to special cases such as
 * empty list, head, and tail
 * this was a bit tricky
 * can I refactor this?
 */
void insertNth(node* & head, int index, int data)
{
  assert (index >=0 && index <= length(head));
  node *cur = head;
  int count = 0;

  if (index == 0) {		// special case for adding the first cell
    node *temp = head;
    head = new node;
    head -> data = data;
    head -> next = temp;
  } else {
    while (count < index - 1) { // need to point at the position before the intend
      cur = cur -> next;
      count++;
    }
    node *temp = cur -> next;
    cur -> next = new node;
    (cur -> next) -> data = data;
    (cur -> next) -> next = temp;
  }

  
  // if (head == NULL) {		// special case for empty list
  //   head = new node;
  //   head -> data = data;
  //   head -> next = NULL;
  // } else {
  //   if (index == 0) {		// special case for adding at first position
  //     node *temp = head;
  //     head = new node;
  //     head -> data = data;
  //     head -> next = temp;
  //   } else {
  //     while (count < index - 1) { // need to point at the position before the intend
  // 	cur = cur -> next;
  // 	count++;
  //     }
  //     node *temp = cur -> next;
  //     cur -> next = new node;
  //     (cur -> next) -> data = data;
  //     (cur -> next) -> next = temp;
  //   }
  // }
  
}  
