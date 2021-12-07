//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "MyHashTable.h"
#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

MyHashTable::MyHashTable(){ //Constructor de la hashtable. Complejidad O(1)
    this->size=0;
    this->sizeA=11;
    this->tabla= new MyLinkedList[this->sizeA];
}

MyHashTable::~MyHashTable(){ //Destructor de la hashtable. Complejidad O(n)
    int tam = 0;
    for(int i = 0; i<this->sizeA; i++){
        tam = this->tabla[i].length();
        if(tam > 0){
            this->tabla[i].~MyLinkedList();
            this->size -= tam;
        }
    }
}

int MyHashTable::sizeCompleto(){
    return this->sizeA;
}

int MyHashTable::getPos(string key){ //Hash del key insertado. Complejidad O(n)
    size_t hashC=hash<string>{}(key);
    int hashCode = static_cast<int>(hashC);
    return abs(hashCode)%this->sizeA;
}

void MyHashTable::getLista(int pos){
    this->tabla[pos].getData();
}

MyLinkedList MyHashTable::getLL(int pos){
    return this->tabla[pos];
}

bool MyHashTable::isEmpty(){ //Regresa booleano si la lista tiene contenido o si esta vacia. Complejidad O(1)
    return this->size==0;
}

void MyHashTable::rehashing(){ //Crece el tamano de la tabla *2+1 y reacomoda todos los key ya presentes. Complejidad O(n)
    MyLinkedList* base = this->tabla;
    int tamano = this->sizeA;
    this->sizeA = (this->sizeA*2) +1;
    this->tabla = new MyLinkedList[this->sizeA];

    for(int i = 0; i<tamano; i++){
        if(base[i].isEmpty() == 0){
            MyNodeLL* current = base[i].first();
            while(current != nullptr){
                int pos = getPos(current->key);
                this->tabla[pos].insertFirst(current->key, current->data);
                current = current->next;
            }
            base[i].~MyLinkedList();
        }
    }
}

void MyHashTable::put(string key, string value){ //Inserta key y valor a la hashtable. Complejidad O(1)
    float tam = this->size;
    float tamA = this->sizeA;
    float factor = tam/tamA;
    if(factor >= 0.75){
        rehashing();
    }
    int pos = getPos(key);
    this->tabla[pos].insertFirst(key, value);
    this->size++;
}

string MyHashTable::get(string key){ //Obtiene valor del key ingresado. Complejidad O(1) en mejor de los casos, O(n) en peor. 
    int pos = getPos(key);
    MyLinkedList* lista = &this->tabla[pos];
    return lista->getAt(key);
}

void MyHashTable::remove(string key){ //Elimina el key. Complejidad O(n)
    int pos = getPos(key);
    if(this->tabla[pos].searchKey(key) >= 0){
        int posL = this->tabla[pos].searchKey(key);
        this->tabla[pos].removeAt(posL);
        this->size--;
    }
}