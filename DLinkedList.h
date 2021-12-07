#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <iostream>

using namespace std;

struct MyNodeLL{
  string data;
  MyNodeLL* next;
  MyNodeLL* prev;

  MyNodeLL(string data, MyNodeLL* next, MyNodeLL* prev){
    this->data=data;
    this->next=next;
    this->prev=prev;
  }

  MyNodeLL(string data):MyNodeLL(data,nullptr,nullptr){ }
};

class DLinkedList{
private:
  MyNodeLL* head;
  MyNodeLL* tail;
  int size;
  void swap(MyNodeLL* x, MyNodeLL* y);
  int part(int ini, int fin);
  void quickSort(int ini, int fin);

public:
  DLinkedList();
  int length();
  void insertLast(string data);
  MyNodeLL* getAt(int pos);
  string correctQ(string &q);
  long long obtainIP(string data);
  long long convertIP(string bIP);
  void quickSort();
  int bBinaria(long long bIP);

  friend ostream& operator<<(ostream& os,const DLinkedList& ll){
    MyNodeLL* current=ll.head;
    for(int i=0;i<ll.size;i++){
      os<<current->data<<endl;
      current=current->next;
    }
    os<<endl;
    return os;
  }

};

#endif