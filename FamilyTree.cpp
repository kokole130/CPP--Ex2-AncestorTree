#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;
using namespace family;


string Tree::relation(string name){

    return "";
}

string Tree::find(string relation){
    return "";
}

void Tree::display(){
    printTree(this->root,0);
}

void Tree::printTree(Node* node, int space){
    if(node==NULL){
        return;
    }
    space+=10;

    printTree(node->F,space);

    cout<<endl;
    for(int i=10;i<space;i++){
        cout<<" ";
    }
    cout<<node->name<<endl;

    printTree(node->M,space);
}

void Tree::remove(string name){

}
 
Tree& Tree::addFather(string name,string father){
    Father(this->root,name,father);
    return *this;
}

void Tree::Father(Node* root,string name,string father){
    if(root->name==name){
        if(root->F==NULL){
            Node* temp=new Node;
            temp->F=NULL;
            temp->M=NULL;
            temp->name=father;
            root->F=temp;
            return;
        }
        else{
            //throw exception already have father
        }
    }
    else{
        if(root->M!=NULL&&root->F!=NULL){
            Father(root->M,name,father);
            Father(root->F,name,father);
        }
        else if(root->M!=NULL&&root->F==NULL){
            Father(root->M,name,father);
        }
        else if(root->M==NULL&&root->F!=NULL){
            Father(root->F,name,father);
        }
    }
}

Tree& Tree::addMother(string name,string mother){
    Mother(this->root,name,mother);
    return *this;
}

void Tree::Mother(Node* root,string name,string mother){
    if(root->name==name){
        if(root->F==NULL){
            Node* temp=new Node;
            temp->F=NULL;
            temp->M=NULL;
            temp->name=mother;
            root->M=temp;
            return;
        }
        else{
            //throw exception already have father
        }
    }
    else{
        if(root->M!=NULL&&root->F!=NULL){
            Mother(root->M,name,mother);
            Mother(root->F,name,mother);
        }
        else if(root->M!=NULL&&root->F==NULL){
            Mother(root->M,name,mother);
        }
        else if(root->M==NULL&&root->F!=NULL){
            Mother(root->F,name,mother);
        }
    }
}

int main(int argc, char const *argv[])
{
    Tree T("Ron");
    T.addMother("Ron","Malka");
    T.addFather("Ron","Ezra");
    T.addMother("Malka","Miriam");
    T.addFather("Malka","Itzhak");
    T.addMother("Ezra","Marcel");
    T.addFather("Ezra","Shlomo");
    T.display();
    return 0;
}


