#pragma once
#include <string>
#include <iostream>

using namespace std;
namespace family{
typedef struct Node{//each node in the tree
        string name;//name of the person
        char gender;
        struct Node* F;//one node for father
        struct Node* M;//one node for mother
}Node;

class Tree {

    public:
        Node root;
        Tree(string name){
            root.name=name;
        }

        string relation(string name);
        string find(string relation);
        void display();
        void remove(string name);
        Tree& addFather(string name,string father);
        Tree& addMother(string name,string mother);

};
}






