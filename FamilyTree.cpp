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
    cout<<"      "+this->root->name<<endl;
    scan(this->root);
}

void Tree::scan(Node* root){
    if(root->M!=NULL&&root->F!=NULL){
        cout<<root->M->name<<"<    >"<<root->F->name<<endl;
        scan(root->F);
        scan(root->M);
    }
    else if(root->M!=NULL&&root->F==NULL){
        cout<<root->M->name<<"<      "<<endl;
        scan(root->M);        
    }
    else if(root->M==NULL&&root->F!=NULL){
        cout<<"     >"<<root->F->name<<endl;
        scan(root->F);
    }
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


// Tree makeTree(){
//     Tree T("Yosef");
// 	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
// 	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
// 	 .addFather("Yaakov", "Isaac")
// 	 .addMother("Yaakov", "Rivka")
// 	 .addFather("Isaac", "Avraham")
// 	 .addFather("Avraham", "Terah");
//     return T;
// }

// int main(int argc, char const *argv[])
// {
//     Tree T("Ron");
//     T.addMother("Ron","Malka");
//     T.addFather("Ron","Ezra");
//     T.addMother("Malka","Miriam");
//     T.addFather("Malka","Itzhak");
//     T.addMother("Ezra","Marcel");
//     T.addFather("Ezra","Shlomo");
//     T.display();
//     return 0;
// }


