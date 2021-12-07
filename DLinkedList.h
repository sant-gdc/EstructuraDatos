#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <iostream>

using namespace std;

struct MyNodeLL{
  string data;
  MyNodeLL* next;
  MyNodeLL* prev;
  int key;
  string IP;
  long long numIP;

  MyNodeLL(string data, MyNodeLL* next, MyNodeLL* prev, int key, string IP, long long numIP){
    this->data=data;
    this->next=next;
    this->prev=prev;
    this->key=key;
    this->IP=IP;
    this->numIP=numIP;
  }

  MyNodeLL(string data):MyNodeLL(data,nullptr,nullptr,1,"",0){ }
};
 
class DLinkedList{
private:
  MyNodeLL* head;
  MyNodeLL* tail;
  int size;
  void swap(MyNodeLL* x, MyNodeLL* y);
  int part(int ini, int fin);
  MyNodeLL* party(MyNodeLL* ini, MyNodeLL* fin);
  void quicky(MyNodeLL* ini, MyNodeLL* fin);
  void quickSort(int ini, int fin);
  void splitKey(MyNodeLL* current, MyNodeLL* sig);

public:
  DLinkedList();
  int length();
  void insertLast(string data, int key, string IP);
  MyNodeLL* getAt(int pos);
  string correctQ(string &q);
  long long obtainIP(string data);
  long long convertIP(string bIP);
  void transformarIP();
  void quickSort();
  void quicky();
  int bBinaria(long long bIP);
  void removeUbi(MyNodeLL* ubi);
  void splitKey();

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