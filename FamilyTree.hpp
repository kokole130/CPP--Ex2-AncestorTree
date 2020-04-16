#pragma once
#include <string>
#include <iostream>

using namespace std;

class Node{//each node in the tree
        private:
            string name;//name of the person


        public:
            Node* F;//one node for father
            Node* M;//one node for mother
            Node(string name):name(name),F(NULL),M(NULL){

        }

        string getName(){
            return this->name;
        }

        ~Node(){

        }
};

namespace family{
    class Tree {
        public:
            Node* root;
            int size;
            Tree(string name){
                this->root=new Node(name);
                size=1;
             }

        string relation(string name);
        string find(string relation);
        void display();
        void remove(string name);
        Tree& addFather(string name,string father);
        Tree& addMother(string name,string mother);

        ~Tree(){
            removeNode(&root);
        }

    private:
        void Father(Node& root,string name,string father);
        void Mother(Node* root,string name,string mother);
        void scan(Node* root);
        void printTree(Node* node, int space,string gender);
        string findrelation(Node* node,string name, string relation);
        string findGreat(Node* node, string relation);
        void FindRemoveNode(Node** root,string name);
        void removeNode(Node** root);


};
}






