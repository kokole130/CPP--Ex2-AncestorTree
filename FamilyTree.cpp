#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;

void FamilyTree::addNew(string name, char sex){ //add new related to the tree
    if(start.name!=string("")&&(sex=='m'||sex=='f')){
        start.name=name;
        start.sex=sex;
        return;
    }
    else{
        return;
        // we need to throw here Exception !!!


    }
}

void FamilyTree::addNew(string name, char sex,char relation,string related){//add new related to the tree

}

string FamilyTree::findRelation(string name,char related){//find name of the related
    return "";
}
// we need to fix it- cpp and hpp files.
// we need to decide about findRelation function. 
// name, or name+related.
string FamilyTree::findRelation(string name){//find name of the related
    return "";
}

string FamilyTree::find(string name1, string name2){//find the relation between to names
    return "";
}

void FamilyTree::display(Node start){

}

void FamilyTree::remove(string name){

}
 

void FamilyTree::addFather(string father,string name){

}

void FamilyTree::addMother(string mother,string name){

}



