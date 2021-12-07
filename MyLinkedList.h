//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945
#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H
#include <iostream>

using namespace std;

struct MyNodeLL{
    string data;
    string key;
    MyNodeLL* next;

    MyNodeLL(string key, string data, MyNodeLL* next){
        this->key = key;
        this->data = data;
        this->next = next;
    }

    MyNodeLL(string key, string data):MyNodeLL(key,data,nullptr){}
};

class MyLinkedList{
    private:
        MyNodeLL* head;
        MyNodeLL* tail;
        int size;
        void swap(MyNodeLL* x, MyNodeLL* y);
        void quickSort(int ini, int fin);
        int part(int ini, int fin);
    public:
        MyLinkedList();
        ~MyLinkedList();
        int length();
        MyNodeLL* first();
        void insertFirst(string key, string data);
        string getAt(string key);
        void getData();
        MyNodeLL* getNode(int pos);
        bool isEmpty();
        void removeFirst();
        int searchKey(string key);
        void removeLast();
        void removeAt(int pos);
        void quickSort();
        void printList();
        friend ostream& operator<<(ostream& os, const MyLinkedList& ll){
            MyNodeLL* current = ll.head;
            for(int i=0; i<ll.size; i++){
                os<<current->data<<",";
                current = current->next;
            }
            return os;
        }

};

#endif