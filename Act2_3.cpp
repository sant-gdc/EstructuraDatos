//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void swap(vector<vector<string>> &x, int i, int j){
    vector<string> paso;
    paso = x[i];
    x[i] = x[j];
    x[j] = paso;
}

string correctQ(string &q){
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

long long obtainIP(vector<string> registro){
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

long long convertIP(string bIP){
    string q1 = bIP.substr(0,bIP.find('.'));
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
    string port = bIP.substr(0);

    string preBIP = q1 + q2 + q3 + q4 + port;
    return stoll(preBIP);
}

int part(vector<vector<string>> &bitacora, int first, int last){
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

void quickSort(vector<vector<string>> &bitacora, int first, int last){
    if (first < last){
        int pos = part(bitacora, first, last);
        quickSort(bitacora, first, pos-1);
        quickSort(bitacora, pos+1, last);
    }
}

void quickSort(vector<vector<string>> &bitacora){
    quickSort(bitacora, 0, bitacora.size() -1);
}

string registroString(vector<string> registro){
    string completo;
    for (int i =0; i < registro.size() - 1 ; i++){
        completo  += registro[i] + " ";
    }
    completo = completo + registro[4];
    return completo; 
}

int bBinaria(vector<vector<string>> bitacora, long long IP){
    int inicio = 0;
    int fin = bitacora.size() - 1;
            
    while(inicio <= fin){
        int mitad = inicio + (fin - inicio) / 2;

        if(IP == obtainIP(bitacora[mitad])) {
			return mitad;
		} else if(IP < obtainIP(bitacora[mitad])){
            fin = mitad-1;
        }else{
            inicio = mitad + 1;
        }
    }
    return inicio;
}

int main(){
    vector<vector<string>> bitacora;
    vector<string> registro;
    ifstream lector("bitacora.txt");
    string linea, mes, hora, direccionIP, razon, dia;
    int size = 0;
    while (getline(lector, linea))
    {
        registro.clear();

        stringstream ss(linea);
        getline(ss, mes, ' ');
        registro.push_back(mes);
        getline(ss, dia, ' ');
        registro.push_back(dia);
        getline(ss, hora, ' ');
        registro.push_back(hora);
        getline(ss, direccionIP, ' ');
        registro.push_back(direccionIP);
        getline(ss, razon, '\n');
        registro.push_back(razon);
        bitacora[size];
        bitacora.push_back(registro);
        size++;
    }
    lector.close();
    
    quickSort(bitacora); //Ordena todo el documento de bitacora.txt

    ofstream escritor("bitacoraOrdenada-Eq#2.txt"); //crea el archivo bitacoraCorrecta.txt con todos los registros ordenados
    if (escritor.is_open()) {
        for (int i = 0 ; i < bitacora.size() ; i++) {
            escritor << registroString(bitacora[i]) << "\n";
        }
        escritor.close();
		cout << "La bitacora ordenada respecto a la direccion IP se encuentra en \"bitacoraOrdenada-Eq#2.txt\"." << endl;
	}

    bool another = 1;
    int N = 1;

    while(another == 1){

        cout << "Busqueda de registros"<<endl; //Se le pide al usuario que ingrese las fechas iniciales para comenzar la busqueda
        cout<<"Favor de ingresar los datos en el siguiente formato XXX.XXX.XXX.XXX (no es necesario llenar los 3 espacios por cuarteto)"<<endl;
        string firstIP;
        cout << "Direccion IP de inicio: ";
        cin >> firstIP;
        long long IPInicial = convertIP(firstIP + ":0000");
    

        cout<<"Igual que el formato anterior, favor de ingresar la direccion IP final"<<endl; //El usuario ingresa los dias finales de la busqueda
        string lastIP;
        cout << "Direccion IP final: ";
        cin >> lastIP;
        long long IPFinal = convertIP(lastIP + ":9999");

        int posIni = bBinaria(bitacora, IPInicial); //busqueda binaria de la fecha inicial mas cercana a la ingresada
        int posFin = bBinaria(bitacora, IPFinal); //Busqueda binaria de la fecha final en el ultimo instante del dia ingresado
    
        cout << "Los registros de la direccion IP inicial a la direccion IP final son: "; //Despliega todos los registros entre las fechas ingresadas
        cout << endl;
        for (int i = posIni ; i < posFin ; i++) {
            cout << registroString(bitacora[i]) <<endl;
        }

        string M = to_string(N);
        ofstream doc("salida"+ M +"-Eq#2.txt"); //Guarda los registros entre las fechas ingresadas del usuario en RegistrosUsuario.txt
        if (doc.is_open()){
            for (int i = posIni ; i < posFin ; i++) {
                doc << registroString(bitacora[i]) <<endl;
            }
            doc.close();
		    cout << "Los registros ordenados fueron guardados en \"salidaN-Eq#2.txt\"." << endl;
		    }
        cout << "Gustaria realizar otra busqueda? si(1) no(0)"<<endl;
        cin >> another;
        N++;
    }
}