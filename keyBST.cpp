//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#include "keyBST.h"
#include <iostream>

using namespace std;

keyBST::keyBST(){ //Crea el BST O(1)
    this->size = 0;
    this->root = nullptr;
} 

int keyBST::length(){ //Regresa la longitud del BST O(1)
    return this->size;
}

bool keyBST::isEmpty(){ //Regresa booleano sobre si el BST esta vacio o no O(1)
    return this->size==0;
}

node* keyBST::insert(node* current, string data, int key){ //Inserta valor y key en el BST, mejor caso O(1), peor caso O(n)
    if(current == nullptr){
        return new node(data, key);
    }else if(key < current->key){
        node* nvo = insert(current->left, data, key);
        if(nvo != nullptr){
            current->left = nvo;
            return current;
        }else{
            return nullptr;
        }
    }else{
        node* nvo = insert(current->right, data, key);
         if(nvo != nullptr){
            current->right = nvo;
            return current;
        }else{
            return nullptr;
        }
    }
}

bool keyBST::insert(string data, int key){ //Inicializa el insert en el nodo raiz O(1)
    if(this->root == nullptr){
        this->root = new node(data, key);
        this->size++;
        return true;
    }else{
        node* nvo = insert(this->root, data, key);
        if(nvo != nullptr){
            this->size++;
            return true;
        }else{
            return false;
        }
    }
}

void keyBST::printTop(int n){ //Imprime las direcciones IP con mayor cantidad de accesos, recibiendo la cantidad que quiere que se imprima
                              //Complejidad O(1) ya que inicializa la busqueda
    if(this->size < n){
        cout<<"La bitacora tiene menos que "<<n<<" direcciones IP."<<endl;
    }else{
        int k = 0;
        printTop(this->root, n, k);
    }
    
}

void keyBST::printTop(node* current, int n, int &k){ //Recorrido de busqueda de los valores mayores del arbol O(log n) mejor caso, O(n) peor caso
    if(current != nullptr){
        printTop(current->right, n, k);
        k++;
        if(k <= n){
            cout<<k<<"."<<" "<<current->data<<" con "<<current->key<<" accesos registrados"<<endl;
        }
        printTop(current->left, n, k);
    }
}
