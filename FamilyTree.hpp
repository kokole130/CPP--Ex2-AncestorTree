#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct Node{//each node in the tree
        string name;//name of the person
        char sex;
        struct Node* F;//one node for father
        struct Node* M;//one node for mother
        struct Node* W;//one node for wife
        vector<struct Node> S;//dynamic list for sibling
        vector<struct Node> C;//dynamic list for cousin
        vector<struct Node> U;//dynamic list for uncle
        vector<struct Node> A;//dynamic list for aunt
        vector<struct Node> G;//dynamic list for grand parent

}Node;

class FamilyTree {

    public:
        Node start;
        FamilyTree(){
            start.name="";
        }

        void addNew(string name, char sex);
        void addNew(string name, char sex,char relation,string related);
        string findRelation(string name,char related);
        string findRelation(string name); // we need to fix it. 
        string find(string name1, string name2);
        void display(Node start);
        void remove(string name);
        void addFather(string father,string name);
        void addMother(string mother,string name);

};







