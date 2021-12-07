//Santiago Gonzalez de Cosio Romero A01640329
//Javier Alejandro Morales Rivadeneyra A01632535
//Jessica Sarahí Vázquez Martínez A01639945

#ifndef KEYBST_H
#define KEYBST_H
#include <iostream>
using namespace std;

struct node{
    string data;
    int key;
    node *left,
         *right;
    node(string data, int key){
        this->data=data;
        this->key=key;
        this->left= nullptr;
        this->right=nullptr;
    }
}; 
 
class keyBST{
    private:
        int size;
        node* root;
        node* insert(node* current, string data, int key);
        int height(node* current);
        void printTop(node* current, int n, int &k);
        
    public:
        keyBST();
        int length();
        bool isEmpty();
        bool insert(string data, int key);
        void printTop(int n);
};
#endif
