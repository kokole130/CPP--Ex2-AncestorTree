#pragma once
#include <string>
#include <iostream>

using namespace std;
namespace family{
typedef struct Node{//each node in the tree
        string name;//name of the person
        struct Node* F;//one node for father
        struct Node* M;//one node for mother
}Node;

class Tree {
    public:
        Node* root;
        Tree(string name){
            Node* temp=new Node;
            temp->M=NULL;
            temp->F=NULL;
            temp->name=name;
            root=temp;
        }

        string relation(string name);
        string find(string relation);
        void display();
        void remove(string name);
        Tree& addFather(string name,string father);
        Tree& addMother(string name,string mother);

    private:
        void Father(Node* root,string name,string father);
        void Mother(Node* root,string name,string mother);
        void scan(Node* root);
        void printTree(Node* node, int space);
        void printTrees(Node* node);
        string findrelation(Node* node,string name, string relation);



};
}






