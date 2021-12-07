//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945
#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include "MyLinkedList.h"
#include "MyLinkedList.cpp"

class MyHashTable{
    private:
            MyLinkedList* tabla;
            int size; //Cantidad de valores que hay almacenados en la tabla
            int sizeA; //Tamano del arreglo 
            void rehashing();
    public:
            MyHashTable();
            bool isEmpty();
            int getPos(string key);
            int sizeCompleto();
            void put(string key, string data);
            string get(string key);
            void getLista(int pos);
            MyLinkedList getLL(int pos);
            void remove(string key); //tarea, que aviente error si no hay llave
            ~MyHashTable();
            

};
#endif