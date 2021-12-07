//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "MyLinkedList.h"
#include <iostream>
#include <limits> 
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

MyLinkedList::MyLinkedList(){ //Inicializador de la lista
    this->size=0;
    this->head = this->tail = nullptr;
}

MyLinkedList::~MyLinkedList(){ //Destructor de la lista
    MyNodeLL* current;
    while(this->head != nullptr){
        current = this->head->next;
        delete(this->head);
        this->head = current;
        this->size--; 
    }
}

MyNodeLL* MyLinkedList::first(){
    return this->head;
}

int MyLinkedList::length(){ //Regresa la longitud de la lista
    return this->size;
}

void MyLinkedList::insertFirst(string key, string data){ //Inserta un nuevo nodo al inicio de la lista
    MyNodeLL* prev = this->head;
    this->head = new MyNodeLL(key, data, prev);
    if(this->size == 0){
        this->tail = this->head;
    }
    this->size++;
}

string diaCorrecto(string dia){
    if(dia.size() >  1){
        return dia;
    }else{
        return "0" + dia;
    }
}

string numMes(string mes){
    if(mes == "Jan"){
        return "01";
    }else if (mes == "Feb"){
        return "02";
    }else if (mes == "Mar"){
        return "03";
    }else if (mes == "Apr"){
        return "04";
    }else if (mes == "May"){
        return "05";
    }else if (mes == "Jun"){
        return "06";
    }else if (mes == "Jul"){
        return "07";
    }else if (mes == "Aug"){
        return "08";
    }else if (mes == "Sep"){
        return "09";
    }else if (mes == "Oct"){
        return "10";
    }else if (mes == "Nov"){
        return "11";
    }else if(mes == "Dec"){ 
        return "12";
    }else{
        return "10";
    }
}

string quitaPuntos(string horaCompleta){
    string hora, min, seg;
    stringstream ss(horaCompleta);
        getline(ss, hora, ':');
        getline(ss, min, ':');
        getline(ss, seg, ' ');
    
    if(hora.size() <  2){
        hora = "0"+hora;
    }

    return hora+min+seg;
}

int fechaAgrupada(string data){  
    string mes, dia, hora;
    stringstream ss(data);
        getline(ss, mes, ' ');
        getline(ss, dia, ' ');
        getline(ss, hora, '\n');
    
    mes = numMes(mes);
    dia = diaCorrecto(dia);
    hora = quitaPuntos(hora);

    string conc = mes + dia + hora;
    int fecha = stoi(conc);

    return fecha;
}

int MyLinkedList::searchKey(string key){ //Regresa el valor en la posicion deseada de la lista
   MyNodeLL* current= this->head;
    for(int i = 0; i<this->size; i++){
        if(current->key == key){
            return i;
        }
        current=current->next;
    }
    cout<<"No se encuentra la llave " +key+ " en la tabla"<<endl;
    return -1;
}

string MyLinkedList::getAt(string key){
    MyNodeLL* current= this->head;
    for(int i = 0; i<this->size; i++){
        if(current->key == key){
            return current->data;
        }
        current=current->next;
    }
    throw invalid_argument("No se encuentra la llave " +key+ " en la tabla");
}

void MyLinkedList::getData(){
    MyNodeLL* current = this->head;
    while(current != nullptr){
        cout<<current->data<<endl;
        current = current->next;
    }
}

MyNodeLL* MyLinkedList::getNode(int pos){ //Regresa el MyNodeLL en la posicion deseada de la lista
   MyNodeLL* current = this->head;
   if(pos>=0 && pos<this->size){
        for(int  i=0; i<pos; i++){
            current = current->next;
        }
   }else{
       throw invalid_argument("No se puede acceder a la posicion " + to_string(pos)+ " en una lista de tamano " + to_string(this->size));
   }
    return current;
}

void MyLinkedList::printList(){
    MyNodeLL* current = this->head;
    while(current != nullptr){
        cout<<current->data<<endl;
        current = current->next;
    }
    cout<<"Print done"<<endl;
}

void MyLinkedList::removeFirst(){ //Elimina el primer valor de la lista
    if(this->size>0){
        MyNodeLL* temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->size--;
    }else{
        throw invalid_argument("No se puede borrar el primer elemento de una lista vacia \n");
    }
}

void MyLinkedList::removeLast(){ //Elimina el ultimo valor de la lista
    if(this->size>0){
        MyNodeLL* temp = this->head;
        while((temp->next)->next != nullptr){
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        this->size--;
    }else{
        throw invalid_argument("No se puede borrar el ultimo elemento de una lista vacia \n");
    }
}

void MyLinkedList::removeAt(int pos){ //Elimina el valor en la posicion deseada de la lista
    if(this->size>0){
        MyNodeLL* current = this->head;
        MyNodeLL* del;
        if(pos>=0 && pos<this->size){
            if(pos == 0){
                removeFirst();
            }else{
                for(int  i=0; i<pos-1; i++){
                current = current->next;
                }
                del = current->next;
                current->next = del->next;
                delete(del);
                this->size--;
            }
        }else{
        throw invalid_argument("No se puede eliminar la posicion " + to_string(pos)+ " en una lista de tamano " + to_string(this->size));
        }
    }else{
        throw invalid_argument("No se puede borrar el elemento de una lista vacia \n");
    }
}

bool MyLinkedList::isEmpty(){ //Regresa un 1 si la lista esta vacia, un 0 si la vacia tiene contenido 
    return this->size == 0;
}

void MyLinkedList::swap(MyNodeLL* x, MyNodeLL* y){ //Intercambia la data de un MyNodeLL por la del otro
    string tempData = x->data;
    x->data = y->data;
    y->data = tempData;
}

int MyLinkedList::part(int ini, int fin){ //Particion de pivote en quicksort
    int pivot = fechaAgrupada(getNode(ini)->data);
    int x = ini + 1;

    for(int y = x; y <= fin; y++){
        int IPtemp = fechaAgrupada(getNode(y)->data);
        if(IPtemp < pivot){
            MyNodeLL* currentX = getNode(x++);
            MyNodeLL* currentY = getNode(y);
            swap(currentX, currentY);
        }
    }
    MyNodeLL* iniN = getNode(ini);
    MyNodeLL* minX = getNode(x-1);
    swap(iniN,minX);
    return x-1;
}

void MyLinkedList::quickSort(int ini, int fin){ //Quicksort
    if (ini < fin){
        int pos = part(ini, fin);
        quickSort(ini, pos-1);
        quickSort(pos+1, fin);
    }
}

void MyLinkedList::quickSort(){ //Inicializa el quicksort
    quickSort(0, this->size -1);
}


