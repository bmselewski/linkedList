//Brendan Selewski
//bms4yzc
//1/30/2020
//List.cpp


#include <iostream>
#include "List.h"
using namespace std;

List::List(){
  head = new ListNode();
  tail = new ListNode();
  count = 0;
  tail->previous = head;
  head->next = tail;


}

List::List(const List& source) {
    head=new ListNode();
    tail=new ListNode();
    head->next=tail;
    tail->previous=head;
    count=0;

    // Make a deep copy of the list
    ListItr iter(source.head->next);
    while (!iter.isPastEnd()) {
        insertAtTail(iter.retrieve());
        iter.moveForward();
    }
}

List::~List(){
  makeEmpty();
  delete tail;
  delete head;
}

// Copy assignment operator
// Called when the code looks something like list2 = list1;
// (In other words, it is called when you are trying to set an **existing** list equal to another one)
List& List::operator=(const List& source) {
    if (this == &source) {
        // The two are the same list; no need to do anything
        return *this;
    } else {
        // Clear out anything this list contained
        // before copying over the items from the other list
        makeEmpty();

        // Make a deep copy of the list
        ListItr iter(source.head->next);
        while (!iter.isPastEnd()) {
            insertAtTail(iter.retrieve());
            iter.moveForward();
        }
    }
    return *this;
}

bool List::isEmpty() const {
  if(count==0){
    return true;
  }
  else{
    return false;
  }
}

void List::makeEmpty(){
  ListItr x = first();
  while(!x.isPastEnd()){
    int z = x.retrieve();
    x.moveForward();
    remove(z);
    
  }

}
ListItr List::first(){
  ListItr x = ListItr(head->next);
  return x;
}

ListItr List::last(){
  ListItr x = ListItr(tail->previous);
  return x;
}

void List::insertAfter(int x, ListItr position){
  ListNode* z = position.current;
  ListNode* y = new ListNode();
  y->value = x;
  z->next->previous = y;
  y->next = z->next;
  z->next = y;
  y->previous = z;
  count++;
}

void List::insertBefore(int x, ListItr position){
  ListNode* z = position.current;
  ListNode* y = new ListNode();
  y->value = x;
  y->previous=z->previous;
  y->next = z;
  z->previous = y;
  y->previous->next = y;
  count++;
}

void List::insertAtTail(int x){
  ListNode*z = new ListNode();
  // ListNode*dummy = new ListNode();
  // tail->previous =z;
  z->value=x;
  //ListNode tempPrevious = *tail->previous;
  //tempPrevious.next = z;
  //z->previous = &tempPrevious;
  ListNode *tempPrevious = tail->previous;
  tail->previous = z;
  tempPrevious->next = z;
  z->previous = tempPrevious;
  z->next = tail;
  count++;
}

ListItr List:: find(int x){
  ListItr z = first();
  while( !z.isPastEnd()&&z.retrieve()!=x){
    z.moveForward();
  }
  return z;
  
}

void List:: remove(int x){
  ListItr z = find(x);
  if(!z.isPastEnd()){
    ListNode* y = z.current;
    y->previous->next = y->next;
    y->next->previous = y->previous;
    delete y;
    count--;
  }
}

int List::size() const {
  return count;
}

void printList(List& source, bool forward){
  ListItr current = NULL;
  if(forward){
    current = source.first();
    while(!current.isPastEnd()){
      cout << current.retrieve() << endl;
      current.moveForward();
    }
  }
  if(!forward){
    current = source.last();
    while(!current.isPastBeginning()){
      cout << current.retrieve() << endl;
      current.moveBackward();
    }
  }
}


