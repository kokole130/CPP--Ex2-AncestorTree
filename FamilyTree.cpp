#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;
using namespace family;


string Tree::relation(string name){
    if(this->root->F->name==name){
        return "father";
    }
    if(this->root->M->name==name){
        return "mother";
    }
    if(this->root->F->M->name==name||this->root->M->M->name==name){
        return "grandmother";
    }
    if(this->root->F->F->name==name||this->root->M->F->name==name){
        return "grandfather";
    }
    string fm=findrelation(this->root->F->M,name,"grandmother");
    string ff=findrelation(this->root->F->F,name,"grandfather");
    string mm=findrelation(this->root->M->M,name,"grandmother");
    string mf=findrelation(this->root->M->F,name,"grandfather");
    if(fm!="unrelated"){
        return fm;
    }
    else if(ff!="unrelated"){
        return ff;
    }
    else if(mm!="unrelated"){
        return mm;
    }
    else if(mf!="unrelated"){
        return mf;
    }
    else{
        return "unrelated";
    }
}

string Tree::findrelation(Node* node,string name, string relation){
    if(node==NULL){
        return "unrelated";
    }
    if(node->name==name){
        return relation;
    }
    string s1=findrelation(node->F,name,"great-"+relation.substr(0,relation.length()-6)+"father");
    string s2=findrelation(node->M,name,"great-"+relation.substr(0,relation.length()-6)+"mother");
    if(s1!="unrelated"){
        return s1;
    }
    else if(s2!="unrelated"){
        return s2;
    }
    return "";
}

string Tree::find(string relation){
    if(relation == "me"){
        return this->root->name;
    }else if(relation == "mother" || relation == "Mother"){
        return this->root->M->name;
    }else if(relation == "father" || relation == "Father"){
        return root->F->name;
    }else if(relation == "grandmother" || relation == "Grandmother"){
        if(this->root->F->M != NULL){
            return this->root->F->M->name;
        }else if(this->root->M->M != NULL){
            return this->root->M->M->name;
        }else{
            return "unrelated";
            // need to throw exception
        }
    }else if(relation == "grandfather" || relation == "Grandfather"){
        if(this->root->F->F != NULL){
            return this->root->F->F->name;
        }else if(this->root->M->F != NULL){
            return this->root->M->F->name;
        }else{
            return "unrelated";
            // need to throw exception
        }
    }else{
        return findGreat(this->root,relation);
    }
}

string Tree::findGreat(Node* node, string relation){

    string greatEnd = "";

    if(relation.substr(0,6) == "great-" || relation.substr(0,6) == "Great-"){
        string great1 = relation.substr(6,relation.length());
        greatEnd = "great-" + greatEnd;
        if(great1.length == 17){
            return (greatEnd + find(great1));
        }
        return (find(great1));
    }

    //this if case is for another string that unrelated. (dont begin at "great")
    if(greatEnd == ""){
        return "unreleated";
        // i need to throw an exception;
    }

    return greatEnd;
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
    T.addFather("Marcel","Bibi");
    T.addMother("Bibi","Tsipora");
    cout<<T.relation("Tsipora")<<endl;
    //T.display();
    return 0;
}


