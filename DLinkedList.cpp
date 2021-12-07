//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "DLinkedList.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

DLinkedList::DLinkedList(){ //Inicializador de la lista
    this->size=0;
    this->head = this->tail = nullptr;
}

int DLinkedList::length(){ //Regresa el tamano de la bitacora
    return this->size;
}

string DLinkedList::correctQ(string &q){ //Confirma que el tamano del cuarteto sea de 3, por lo contrario se agregan 0s a la izquierda
    string correct;
    correct = q;
    if(correct.size() == 3){
        return correct;
    }else{
        while(correct.size() < 3){
            correct = "0" + correct;
        }
        return correct;
    }
    /*if(q.size() == 3){
        return q;
    }else if (q.size() == 2){
        return "0"+q;
    }else{
        return "00"+q;
    }*/
}

void DLinkedList::transformarIP(){
    string q1, q2, q3, q4, port;

    for(int i=0; i<this->size; i++){
        stringstream ss(getAt(i)->IP);
        getline(ss, q1, '.');
        q1 = correctQ(q1);
        getline(ss, q2, '.');
        q2 = correctQ(q2);
        getline(ss, q3, '.');
        q3 = correctQ(q3);
        getline(ss, q4, ':');
        q4 = correctQ(q4);
        getline(ss, port, ' ');
        getAt(i)->numIP = stoll(q1+q2+q3+q4+port);
    }
}

long long DLinkedList::convertIP(string bIP){ //Convierte la direccion IP ingresada por el usuario a un long long y confirma el tamano del cuarteto
    string q1, q2, q3, q4, port;
    
    stringstream ss(bIP);
    getline(ss, q1, '.');
    q1 = correctQ(q1);
    getline(ss, q2, '.');
    q2 = correctQ(q2);
    getline(ss, q3, '.');
    q3 = correctQ(q3);
    getline(ss, q4, ':');
    q4 = correctQ(q4);
    getline(ss, port, ' ');
    
    /*string q1 = bIP.substr(0,bIP.find('.'));
    bIP = bIP.substr(bIP.find('.')+1);
    q1 = correctQ(q1);

    string q2 = bIP.substr(0, bIP.find('.'));
    bIP = bIP.substr(bIP.find('.')+1);
    q2 = correctQ(q2);

    string q3 = bIP.substr(0, bIP.find('.'));
    bIP = bIP.substr(bIP.find('.')+1);
    q3 = correctQ(q3);
    
    string q4 = bIP.substr(0, bIP.find(':'));
    bIP = bIP.substr(bIP.find(':')+1);
    q4 = correctQ(q4);
    string port = bIP.substr(0);*/

    string preBIP = q1 + q2 + q3 + q4 + port;
    return stoll(preBIP);
}

void DLinkedList::insertLast(string data, int key, string IP){ //Inserta un nuevo nodo al final de la lista
    MyNodeLL* end = this->tail;
    this->tail = new MyNodeLL(data, nullptr, end, key, IP, 0);
    if(this->size==0){
        this->head = this->tail;
    }else{
        end->next = this->tail;
    }
    this->size++;
}

MyNodeLL* DLinkedList::getAt(int pos){ //Regresa el MyNodeLL en la posicion deseada de la lista
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

long long DLinkedList::obtainIP(string data){ //Obtiene la direccion IP de la linea completa y lo transforma en long long
   string cut = data.substr(15);
   bool corto = 0;
    if(cut.find(' ') == 0){
        cut = cut.substr(1);
    }
    
    string IP = cut.substr(0, cut.find(' '));
    
    string q1 = IP.substr(0,IP.find('.'));
    IP = IP.substr(IP.find('.')+1);
    q1 = correctQ(q1);

    string q2 = IP.substr(0, IP.find('.'));
    IP = IP.substr(IP.find('.')+1);
    q2 = correctQ(q2);

    string q3 = IP.substr(0, IP.find('.'));
    IP = IP.substr(IP.find('.')+1);
    q3 = correctQ(q3);
    
    string q4 = IP.substr(0, IP.find(':'));
    IP = IP.substr(IP.find(':')+1);
    q4 = correctQ(q4);
    string port = IP.substr(0);

    string preIP = q1 + q2 + q3 + q4 + port;
    return stoll(preIP);
}

void DLinkedList::swap(MyNodeLL* x, MyNodeLL* y){ //Intercambia la data de un MyNodeLL por la del otro
    string tempData = x->data;
    x->data = y->data;
    y->data = tempData;
    string tempIP = x->IP;
    x->IP = y->IP;
    y->IP = tempIP;
    long long tempNumIP = x->numIP;
    x->numIP = y->numIP;
    y->numIP = tempNumIP;
}

int DLinkedList::part(int ini, int fin){ //Particion de pivote en quicksort
    long long pivot = (getAt(ini)->numIP);
    int x = ini + 1;

    for(int y = x; y <= fin; y++){
        long long IPtemp = (getAt(y)->numIP);
        if(IPtemp < pivot){
            MyNodeLL* currentX = getAt(x++);
            MyNodeLL* currentY = getAt(y);
            swap(currentX, currentY);
        }
    }
    MyNodeLL* iniN = getAt(ini);
    MyNodeLL* minX = getAt(x-1);
    swap(iniN,minX);
    return x-1;
}

MyNodeLL* DLinkedList::party(MyNodeLL* ini, MyNodeLL* fin){ //Particion de pivote en quicksort
    /*long long pivot = ini->numIP;
    MyNodeLL* x = ini->prev;

    for(MyNodeLL* y = ini; y != fin; y = y->next){
        long long IPtemp = y->numIP;
        if(IPtemp <= pivot){
            if(x == nullptr){
                x = ini;
            }else{
                x = x->next;
            }
            swap(x, y);
        }
    }
    if(x == nullptr){
                x = ini;
            }else{
                x = x->next;
            }
            swap(x, fin);
    return x;*/
    long long pivot = (ini->numIP);
    MyNodeLL* x = ini->next;

    for(MyNodeLL* y = x; y != fin; y = y->next){
        long long IPtemp = (y->numIP);
        if(IPtemp < pivot){
            swap(x->next, y);
        }
    }
    swap(ini,x->prev);
    return x->prev;
}

void DLinkedList::quickSort(int ini, int fin){ //Quicksort
    if (ini < fin){
        int pos = part(ini, fin);
        quickSort(ini, pos-1);
        quickSort(pos+1, fin);
    }
}

void DLinkedList::quicky(MyNodeLL* ini, MyNodeLL* fin){ //Quicksort
    if (fin != nullptr && ini != fin && ini != fin->next){
        MyNodeLL* pos = party(ini, fin);
        quicky(ini, pos->prev);
        quicky(pos->next, fin);
    }
}

void DLinkedList::quickSort(){ //Inicializa el quicksort
    transformarIP();
    quickSort(0, this->size -1);
}

void DLinkedList::quicky(){ //Inicializa el quicksort
    transformarIP();
    quicky(this->head, this->tail);
}

/*int DLinkedList::bBinaria(long long IP){ //Genera una busqueda binaria comparando el long long de la direccion IP
    int inicio = 0;
    int fin = this->size - 1;
            
    while(inicio <= fin){
        int mitad = inicio + (fin - inicio) / 2;

        if(IP == obtainIP(getAt(mitad)->data)) {
			return mitad;
		} else if(IP < obtainIP(getAt(mitad)->data)){
            fin = mitad-1;
        }else{
            inicio = mitad + 1;
        }
    }
    return inicio;
}


 
int main(){
    DLinkedList bitacora;
    ifstream lector("bitacora.txt");
    string data, linea;
    while (getline(lector, linea))
    {
        stringstream ss(linea);
        getline(ss, data, '\n');
        bitacora.insertLast(data);
    }
    lector.close();

    bitacora.quickSort();

    ofstream escritor("bitacoraOrdenada-Eq#2.txt"); //crea el archivo bitacoraCorrecta.txt con todos los registros ordenados
    if (escritor.is_open()) {
        for (int i = 0 ; i < bitacora.length() ; i++) {
            escritor << bitacora.getAt(i)->data << "\n";
        }
        escritor.close();
		cout << "La bitacora ordenada respecto a la fecha y hora se encuentra en \"bitacoraOrdenada-Eq#2.txt\"." << endl;
	}

    bool another = 1;
    int N = 1;

    while(another == 1){
        cout << "Busqueda de registros"<<endl; 
        cout<<"Favor de ingresar los datos en el siguiente formato XXX.XXX.XXX.XXX (no es necesario llenar los 3 espacios por cuarteto)"<<endl;
        string firstIP;
        cout << "Direccion IP de inicio: ";
        cin >> firstIP;
        long long IPInicial = bitacora.convertIP(firstIP + ":0000");
    
        cout<<"Igual que el formato anterior, favor de ingresar la direccion IP final"<<endl; 
        string lastIP;
        cout << "Direccion IP final: ";
        cin >> lastIP;
        long long IPFinal = bitacora.convertIP(lastIP + ":9999");

        int posIni = bitacora.bBinaria(IPInicial); 
        int posFin = bitacora.bBinaria(IPFinal); 
    
        cout << "Los registros de la direccion IP inicial a la direccion IP final son: "; 
        cout << endl;
        for (int i = posIni ; i < posFin ; i++) {
            cout << bitacora.getAt(i)->data <<endl;
        }

        string M = to_string(N);
        ofstream doc("salida"+ M +"-Eq#2.txt"); 
        if (doc.is_open()){
            for (int i = posIni ; i < posFin ; i++) {
                doc << bitacora.getAt(i)->data <<endl;
            }
            doc.close();
		    cout << "Los registros ordenados fueron guardados en salida" + M + "\"-Eq#2.txt\"." << endl;
		    }
        cout << "Gustaria realizar otra busqueda? si(1) no(0)"<<endl;
        cin >> another;
        N++;
    }
}*/
 