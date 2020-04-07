#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;
using namespace family;


string Tree::relation(string name){
    if(this->root->F->getName()==name){
        return "father";
    }
    if(this->root->M->getName()==name){
        return "mother";
    }
    if(this->root->F->M->getName()==name||this->root->M->M->getName()==name){
        return "grandmother";
    }
    if(this->root->F->F->getName()==name||this->root->M->F->getName()==name){
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
    if(node->getName()==name){
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
        if(root->getName!=NULL){
            return this->root->getName();
        }else{
            //throw
        }
    }else if(relation == "mother" || relation == "Mother"){
        if(root->M!=NULL){
            return this->root->M->getName();
        } else{ //trow;
        }
    }else if(relation == "father" || relation == "Father"){
        if(root->F!=NULL){
            return root->F->getName();
        }else{ //throw
        }
    }else if(relation == "grandmother" || relation == "Grandmother"){
        if(this->root->F->M != NULL){
            return this->root->F->M->getName();
        }else if(this->root->M->M != NULL){
            return this->root->M->M->getName();
        }else{
            //throw 
        }
    }else if(relation == "grandfather" || relation == "Grandfather"){
        if(this->root->F->F != NULL){
            return this->root->F->F->getName();
        }else if(this->root->M->F != NULL){
            return this->root->M->F->getName();
        }else{
            // throw exception
        }
    }else{
        string ans=findGreat(this->root,relation);

        if(ans==string("not found")){
            //throw
        }
        else return ans;
    }
}

string Tree::findGreat(Node* node, string relation){
    if(relation==string("Grandfather")||relation==string("grandfather")){
        if(node->F->F!=NULL){
            return node->F->F->getName;
        }
        else if(node->M->F!=NULL){
            return node->M->F->getName;
        }
        else{
            return "not found";
        }
    }
    else if(relation==string("Grandmother")||relation==string("grandmother")){
        if(node->F->M!=NULL){
            return node->F->M->getName;
        }
        else if(node->M->M!=NULL){
            return node->M->M->getName;
        }
        else{
            return "not found";
        }
    }

    if(relation.length()<6){    //there is not "great-"
        //throw
    }
    
    if(relation.substr(0,6) == "great-" || relation.substr(0,6) == "Great-"){
        string ans="not found";
        relation = relation.substr(6,relation.length());
        string mom=findGreat(node->M,relation);
        if(mom!=string("not found")){
            ans=mom;
        }
        string papy=findGreat(node->F,relation);
        if(papy!=string("not found")){
            ans=papy;
        }
        return ans;
    }
    return "not found";
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
    cout<<node->getName()<<endl;

    printTree(node->M,space);
}
 
Tree& Tree::addFather(string name,string father){
    Father(this->root,name,father);
    return *this;
}

void Tree::Father(Node* root,string name,string father){
    if(root->getName()==name){
        if(root->F==NULL){
            root->F=new Node(father);
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
    if(root->getName()==name){
        if(root->M==NULL){
            root->M=new Node(mother);
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

void Tree::remove(string name){
    if(root->getName()==name){
        root->F=NULL;
        root->M=NULL;
        delete root;
        root=NULL;
        return;
    }
   FindRemoveNode(this->root,name);

}

void Tree::FindRemoveNode(Node* root,string name){
    if(root->M==NULL){
        return;
    }
    if(root->F==NULL){
        return;
    }
    if(root->M->getName()==name){
        removeNode(root->M);
        root->M=NULL;
        delete root->M;
        return;
    }
    if(root->F->getName()==name){
        removeNode(root->F);
         root->F=NULL;
        delete root->F;
        return;
    }
    FindRemoveNode(root->F,name);
    FindRemoveNode(root->M,name);
        
}


void Tree::removeNode(Node* root){
    if(root==NULL){
        return;
    }
    removeNode((root->F));
    removeNode((root->M));
    root->F=NULL;
    root->M=NULL;
    delete root;
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
   // cout<<T.relation("Tsipora")<<endl;
   // T.display();
    T.remove("Marcel");
   // T.display();
    T.remove("Ron");
    T.display();
    return 0;
}


