//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "keyBST.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void swap(vector<vector<string> > &x, int i, int j){ //Intercambia registros dentro de la bitacora O(1)
    vector<string> paso;
    paso = x[i];
    x[i] = x[j];
    x[j] = paso;
}

string correctQ(string &q){ //Comprueba que sea la cantidad correcta de digitos por cuarteto. O(1)
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
}

long long obtainIP(vector<string> registro){ //Convierte la direecion IP en long lon g para su comparacion O(log n)
    string IP = registro[3];

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

int part(vector<vector<string> > &bitacora, int first, int last){
    long long pivot = obtainIP(bitacora[first]);
    int x = first + 1;

    for(int y = x; y <= last; y++){
        long long IPtemp = obtainIP(bitacora[y]);
        if(IPtemp < pivot){
            swap(bitacora, x++, y);
        }
    }
    swap(bitacora, first, x-1);
    return x-1;
}

void quickSort(vector<vector<string> > &bitacora, int first, int last){
    if (first < last){
        int pos = part(bitacora, first, last);
        quickSort(bitacora, first, pos-1);
        quickSort(bitacora, pos+1, last);
    }
}

void quickSort(vector<vector<string> > &bitacora){ //Tiene una complejidad promedio de O(nlogn) y en peor de los casos O(n2)
    quickSort(bitacora, 0, bitacora.size() -1);
}

string registroString(vector<string> registro){ //Regresa el registro completo en un string O(1)
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
    int counter = 1;
    while (getline(lector, linea)) //Recorre todas las lineas de la bitacora, separa y almacena sus contenidos O(1)
    {
        registro.clear();

        stringstream ss(linea);
        getline(ss, mes, ' ');
        registro.push_back(mes);
        getline(ss, dia, ' ');
        registro.push_back(dia);
        getline(ss, hora, ' ');
        registro.push_back(hora);
        getline(ss, dirIP, ' ');
        registro.push_back(dirIP);
        getline(ss, razon, '\n');
        registro.push_back(razon);
        bitacora[size];
        bitacora.push_back(registro);
        size++;

    }
    lector.close();

    quickSort(bitacora); //Ordena todo el documento de bitacora.txt

    ofstream escritor("bitacoraOrdenada-Eq#2.txt"); //Crea el archivo bitacoraCorrecta.txt con todos los registros ordenados
    if (escritor.is_open()) {
        for (int i = 0 ; i < bitacora.size(); i++) {
            escritor << registroString(bitacora[i]) << "\n";
            //delete bitacora.getAt(i);
        }
        escritor.close();
		cout << "La bitacora ordenada respecto a la direccion IP se encuentra en \"bitacoraOrdenada-Eq#2.txt\"." << endl;
	}
    
    //Se crea un BST para el almacenamiento de las direcciones IP con la cantidad de accesos de cada una sin repetirse O(1)
    //Obtiene la informacion del txt ya ordenado
    keyBST arbol;
    ifstream reader("bitacoraOrdenada-Eq#2.txt");
    string data, line, mon, hr, IP, day;
    string lastIP = "";
    int count = 1;
    while (getline(reader, line))
    {
        stringstream ss(line);
        getline(ss, mon, ' ');
        getline(ss, day, ' ');
        getline(ss, hr, ' ');
        getline(ss, IP, ':');
        
        if(lastIP == "" ){
            lastIP = IP;
            count--;
        }else{
            if(lastIP == IP){
                count++;
            }
            else{
                count++;
                arbol.insert(lastIP, count);
                lastIP = IP;
                count = 0;
            }
        }
    }
    arbol.insert(lastIP, count+1);
    reader.close();

    //Se muestran las IPs con mayor cantidad de accesos, dependiendo de cuantas quieren que se desplieguen
    cout<<"Imprimir las 5 mayores"<<endl;
    arbol.printTop(5);
    cout<<endl;
    cout<<"Imprimir las 10 mayores"<<endl;
    arbol.printTop(10);
}

