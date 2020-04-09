#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;
using namespace family;

/*function that returns the relation by the name*/

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
    string fm=findrelation(this->root->F->M,name,"grandmother");//recursive call for father's mother subtree
    string ff=findrelation(this->root->F->F,name,"grandfather");//recursive call for father's father subtree
    string mm=findrelation(this->root->M->M,name,"grandmother");//recursive call for mother's mother subtree
    string mf=findrelation(this->root->M->F,name,"grandfather");//recursive call for mother's father subtree
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
/*Side recursive function that checks the name of this relation and returns his relation- if exist*/
string Tree::findrelation(Node* node,string name, string relation){
    if(node==NULL){
        return "unrelated";
    }
    if(node->getName()==name){
        return relation;
    }
    string s1=findrelation(node->F,name,"great-"+relation.substr(0,relation.length()-6)+"father");
    /*recursive call to check the "great" times */ 
    string s2=findrelation(node->M,name,"great-"+relation.substr(0,relation.length()-6)+"mother");
    if(s1!="unrelated"){
        return s1;
    }
    else if(s2!="unrelated"){
        return s2;
    }
    return "";
}
/* function that gets a relation of someone on the tree and returns his name  - if exist*/
string Tree::find(string relation){
    if(relation == "me"){
        if(root!=NULL){
            return this->root->getName();
        }else{
            throw std::logic_error("Root isn't exist\n");
        }
    }else if(relation == "mother" || relation == "Mother"){
        if(root->M!=NULL){
            return this->root->M->getName();
        } else{ 
            throw std::logic_error("Mother isn't exist\n");
        }
    }else if(relation == "father" || relation == "Father"){
        if(root->F!=NULL){
            return root->F->getName();
        }else{
            throw std::logic_error("Father isn't exist\n");
        }
    }else if(relation == "grandmother" || relation == "Grandmother"){
        if(this->root->F->M != NULL){
            return this->root->F->M->getName();
        }else if(this->root->M->M != NULL){
            return this->root->M->M->getName();
        }else{
            throw std::logic_error("Grandmother isn't exist\n"); 
        }
    }else if(relation == "grandfather" || relation == "Grandfather"){
        if(this->root->F->F != NULL){
            return this->root->F->F->getName();
        }else if(this->root->M->F != NULL){
            return this->root->M->F->getName();
        }else{
            throw std::logic_error("Grandfather isn't exist\n"); 
        }
    }else{
        string fm = findGreat(this->root->F,relation);//recursive call at father's subtree
        string mm = findGreat(this->root->M,relation);//recursive call at mothers's subtree
        string mf = findGreat(this->root->M,relation);//recursive call at mother's subtree
        string ff = findGreat(this->root->F,relation);//recursive call at father's subtree

        if( fm != "not found"){
            return fm;
        }else if( mm != "not found"){
            return mm;
        }else if( ff != "not found"){
            return ff;
        }else if( mf != "not found"){
            return mf;
        }else{
            throw std::invalid_argument("The relation isn't exist\n");
        }
    }
    return "";
}
/* Side recursive function that checks the relation and returns his name - if exist */
string Tree::findGreat(Node* node, string relation){
    //recursive call at father's subtree
    if(relation == "grandfather" || relation == "Grandfather"){
        if(node->F!=NULL){
            return node->F->getName();
        }else{
            return "not found";
        }
    }
    //recursive call at mother's subtree
    else if(relation == "grandmother" || relation == "Grandmother"){
        if(node->M != NULL){
            return node->M->getName();
        }else{
            return "not found";
        }
    }

    if(relation.length() < 5){    //there is not "great- and not grandmother\grandfather"
        return "not found";
    }

    string ans = "not found";

    //if the sub stirng is "Great-" cut this string and call to this recursive function
    if( relation.substr(0,6) == "great-" || relation.substr(0,6) == "Great-"){
        relation = relation.substr(6,relation.length()-6);
        
        if(node->M != NULL){
            string mom = findGreat(node->M,relation);
            if(mom != "not found"){
                ans=mom;
            }
        }
        if(node->F != NULL){
            string papy = findGreat(node->F,relation);
            if(papy != "not found"){
                ans=papy;
            }
        }
        return ans;
    }
    return "not found";
}
/* Function that draw the tree*/
void Tree::display(){
    printTree(this->root,0,"Root");
}
/*Side recursive function that gets the root of the tree, numbers of spaces and gender and print the tree*/
void Tree::printTree(Node* node, int space,string gender){
    if(node==NULL){
        return;
    }
    space+=10;

    printTree(node->F,space,"F");

    cout<<endl;
    for(int i=10;i<space;i++){
        cout<<" ";
    }
    cout<<gender+":"+node->getName()<<endl;

    printTree(node->M,space,"M");
}
 /* Function that gets a name and father name and add the father to the tree */
Tree& Tree::addFather(string name,string father){
    Father(this->root,name,father);
    return *this;
}
/* Side recursive function that gets a root,name and father name and add the father at the correction 
position */
void Tree::Father(Node* root,string name,string father){
    if(root->getName()==name){
        if(root->F==NULL){
            root->F=new Node(father);
            size++;
            return;
        }
        else{
            throw std::logic_error("Father is exist\n");
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
 /* Function that gets a name and mother name and add the father to the tree */
Tree& Tree::addMother(string name,string mother){
    Mother(this->root,name,mother);
    return *this;
}
/* Side recursive function that gets a root,name and mother name and add the mother at the correction 
position */
void Tree::Mother(Node* root,string name,string mother){
    if(root->getName()==name){
        if(root->M==NULL){
            root->M=new Node(mother);
            size++;
            return;
        }
        else{
            throw std::logic_error("Mother is exist\n");
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
/* Function that gets a name and remove this name and all his subtree from the tree  - if exist*/
void Tree::remove(string name){
    if(root->getName()==name){
        throw std::logic_error("You cant remove the root\n");
    }
    int s=this->size;
    cout<<"size before:"<<s<<endl;
   FindRemoveNode(this->root,name);
   if(this->size==s){
       //cout<<"size after:"<<s<<endl;
       throw std::logic_error("There is not a name in the tree\n");
   }
   cout<<"size after:"<<this->size<<endl;

}
/*Side recursive function that find the node we want to remove */
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
        return;
    }
    if(root->F->getName()==name){
        removeNode(root->F);
         root->F=NULL;
        return;
    }
    FindRemoveNode(root->F,name);
    FindRemoveNode(root->M,name);
        
}

/* Side recursive function that remove each node from this subtree */
void Tree::removeNode(Node* root){
    if(root==NULL){
        return;
    }
    removeNode((root->F));
    removeNode((root->M));
    root->F=NULL;
    root->M=NULL;
    delete root;
    this->size--;
}

int main(int argc, char const *argv[])
{    Tree T("Yosef");
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
    T.addFather("Terah","Yigal");
    T.addMother("Terah","Miri");
     T.addFather("Rivka","Baroh");
    T.addMother("Rivka","Zipi");
    T.display();
//     T.remove("Isaac"); 
//    T.display();
    T.remove("Rivka");
    T.display();
    return 0;
}


