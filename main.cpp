//Equipo 2
//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "MyHashtable.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

string registroString(vector<string> registro){ //Regresa el registro completo en un string 
    string completo;
    for (int i =0; i < registro.size() - 1 ; i++){
        completo  += registro[i] + " ";
    }
    completo = completo + registro[4];
    return completo;
}

int main(){
    //Se crea un vector de vectores que almacena los registros de la bitacora
    vector<vector<string> > bitacora;
    vector<string> registro;
    ifstream lector("bitacora2.txt");
    string linea, mes, hora, dirIP, razon, dia;
    int size = 0;
    while (getline(lector, linea)) //Recorre todas las lineas de la bitacora, separa y almacena sus contenidos 
    {
        registro.clear();

        stringstream ss(linea);
        getline(ss, mes, ' ');
        registro.push_back(mes);
        getline(ss, dia, ' ');
        registro.push_back(dia);
        getline(ss, hora, ' ');
        registro.push_back(hora);
        getline(ss, dirIP, ':');
        registro.push_back(dirIP);
        getline(ss, razon, '\n');
        registro.push_back(razon);
        bitacora[size];
        bitacora.push_back(registro);
        size++;

    }
    lector.close();

    //Ahora los vamos a insertar en la tabla 
    MyHashTable bitacoraKey;
    for(int i = 0; i<bitacora.size(); i++){
        bitacoraKey.put(bitacora[i][3], bitacora[i][0]+" "+bitacora[i][1]+" "+bitacora[i][2]);
    }

    //Se crea el menu
    MyLinkedList lista; 
    string answer = "si";
    string entryIP;
    while(answer == "si"){
        cout<<"Favor de ingresar la direccion IP sin puerto que desea acceder"<<endl; //El usuario ingresa la direccion IP sin puerto deseada
        cin>>entryIP;

        int pos = bitacoraKey.getPos(entryIP);
        lista = bitacoraKey.getLL(pos);
        if(entryIP == lista.first()->key){
            cout<<"La direccion IP: "<<entryIP<<" tiene "<<lista.length()<<" accesos"<<endl;
            lista.quickSort();
            bitacoraKey.getLista(pos);
            
        }else{
            cout<<"No existe la direccion IP ingresada"<<endl;
        }

        cout<<"Gusta ver los accesos de otra direccion IP? Responder: si / no"<<endl;
        cin>>answer;

    }
}