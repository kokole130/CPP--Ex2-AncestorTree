#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;

/*findRelation - gets a name and return the string of all connective family ,
for example T.findRelation("kar") return "wife/cousin" - because in adam tree
the way to arrive "ham" is with "hava" (adam's wife) and then "ham" (hava's cousin).
by the way - if there is not name like this in the tree we should throw exception.
*/

/*find - the opposite function - gets a connective string and return the name of the person
who sustains this relation - for example - T.find("wife/cousin") return "ham"
by the way - if there is not relation like this in the tree we should throw exception*/

/* remove - gets a name and remove him and all his parent and all their relations
from the tree - for example - T.remove("ham") will remove "ham","yefet","kar" and "posher"
by the way - if there is not name like this in the tree we should throw exception.*/

/*addFather/Mother - gets a name of father/mother and name for this son we want to add his father/mother
and add it to the tree. by the way - if there exist a name of his father/mother we should throw exception.*/

//-------------------- use this information for execute the checks correctly------------------//


// Functions to make global trees - T,T2.
FamilyTree makeTree(){
    FamilyTree T;   
    T.addNew("adam",'m');
    T.addNew("adam", 'm');
    T.addNew("hava", 'f', 'w', "adam");
    T.addNew("shem", 'm', 'c', "adam");
    T.addNew("ham", 'm', 'c', "hava");
    T.addNew("yefet", 'm', 's', "ham");
    T.addNew("kar", 'f', 'w', "ham");
    T.addNew("posher", 'm', 'c', "ham");
    return T;
}

FamilyTree makeTree2(){
    FamilyTree T2;
    return T2;
}

// Test Cases

TEST_CASE("Unrelated Case"){
    FamilyTree T = makeTree();
    CHECK(T.findRelation("zz", 's') == string("unrelated"));
	CHECK(T.findRelation("gg", 'c') == string("unrelated"));
	CHECK(T.findRelation("kk", 'w') == string("unrelated"));
	CHECK(T.findRelation("vvf", 'g') == string("unrelated"));
	CHECK(T.findRelation("ddf", 'f') == string("unrelated"));
	CHECK(T.findRelation("tth", 'm') == string("unrelated"));
	CHECK(T.findRelation("uuk", 'u') == string("unrelated"));
	CHECK(T.findRelation("qq", 'a') == string("unrelated"));
	CHECK(T.findRelation("qqe", 'c') == string("unrelated"));
	CHECK(T.findRelation("rqwdd", 'c') == string("unrelated"));
}

TEST_CASE("Father/Mother find Case"){
    FamilyTree T = makeTree();
    T.addFather("adam","shmuel");
    T.addMother("adam","Dana");
    CHECK(T.find("adam","father") == string("shmuel"));
    CHECK(T.find("adam","mother") == string("Dana"));
    T.addFather("adam","shmueli");
    T.addMother("adam","Danit");
    CHECK(T.find("adam","father") == string("shmuel"));
    CHECK(T.find("adam","mother") == string("Dana"));
    T.addFather("adam","dan");
    T.addMother("adam","ziva");
    CHECK(T.find("adam","father") == string("shmuel"));
    CHECK(T.find("adam","mother") == string("Dana"));
    T.addFather("adam","ron");
    T.addMother("adam","rona");
    CHECK(T.find("adam","father") == string("shmuel"));
    CHECK(T.find("adam","mother") == string("Dana"));
    T.addFather("adam","kfir");
    T.addMother("adam","rivka");
    CHECK(T.find("adam","father") == string("shmuel"));
    CHECK(T.find("adam","mother") == string("Dana"));
}

TEST_CASE("Exception Case") {
    FamilyTree T2 = makeTree2();
    CHECK_THROWS(T2.findRelation("ron"));
    CHECK_THROWS(T2.findRelation("omri"));
    CHECK_THROWS(T2.findRelation("yogev"));
    CHECK_THROWS(T2.findRelation("dag"));
    CHECK_THROWS(T2.findRelation("sos"));
    CHECK_THROWS(T2.findRelation("hamor"));
    CHECK_THROWS(T2.findRelation("ori"));
    CHECK_THROWS(T2.findRelation("shani"));
    CHECK_THROWS(T2.findRelation("dana"));
    CHECK_THROWS(T2.findRelation("avi"));
    CHECK_THROWS(T2.findRelation("avichai"));
    CHECK_THROWS(T2.findRelation("avihai"));

    FamilyTree T = makeTree();
    T.remove("adam"); // remove the whole tree.
    CHECK_THROWS(T2.findRelation("avi"));
    CHECK_THROWS(T2.findRelation("avichai"));
    CHECK_THROWS(T2.findRelation("avihai"));
    CHECK_THROWS(T2.find("adam","mother"));
    CHECK_THROWS(T2.find("adam","cousin"));
    CHECK_THROWS(T2.find("adam","father"));
}

TEST_CASE("remove function") {
    FamilyTree T = makeTree();
    T.addFather("yaakov","adam");
    T.addMother("zipi","adam");
    T.addMother("mira","hava");
    T.addFather("yagai","hava");
    T.addNew("yaakov",'m','s',"haim");
    T.addNew("juli",'f','c',"mira");
    CHECK(T.findRelation("adam",'c')==string("shem"));
    CHECK(T.findRelation("adam",'f')==string("yaakov"));
    CHECK(T.findRelation("adam",'m')==string("zipi"));
    T.remove("adam");//remove all the tree
    CHECK(T.findRelation("shem")==string("unrelated"));
    CHECK(T.findRelation("yaakov")==string("unrelated"));
    CHECK(T.findRelation("zipi")==string("unrelated"));

    FamilyTree T2 = makeTree2();
    T2.addNew("adam", 'm');
	T2.addNew("hava", 'f', 'w', "adam");
	T2.addNew("shem", 'm', 'c', "adam");
	T2.addNew("ham", 'm', 'c', "hava");
	T2.addNew("yefet", 'm', 's', "ham");
	T2.addNew("kar", 'f', 'w', "ham");
	T2.addNew("posher", 'm', 'c', "ham");
    T2.addFather("yaakov","adam");
    T2.addMother("zipi","adam");
    T2.addMother("mira","hava");
    T2.addFather("yagai","hava");
    T2.addNew("yaakov",'m','s',"haim");
    T2.addNew("juli",'f','c',"mira");
    T2.addNew("koral",'f','w',"yefet");
    T2.addNew("moshe",'m','g',"posher");
    T2.addNew("menash",'m','g',"shem");
    T2.addNew("tikva",'f','c',"mira");
    T2.addNew("roni",'f','w',"shem");
    T2.addNew("ben",'m','s',"roni");
    T2.addNew("lior",'m','g',"shem");
    T2.addNew("miri",'f','w',"ben");
    CHECK(T.findRelation("ham")==string("wife/cousin"));
    CHECK(T.findRelation("yefet")==string("wife/cousin/sibling"));
    CHECK(T.findRelation("kar")==string("wife/cousin/wife"));
    T2.remove("hava");//remove hava (wife of the original tree's person)
    CHECK(T.findRelation("ham")==string("unrelated"));
    CHECK(T.findRelation("yefet")==string("unrelated"));
    CHECK(T.findRelation("kar")==string("unrelated"));
    CHECK(T.findRelation("zipi")==string("mother"));
    CHECK(T.findRelation("mira")==string("unrelated"));
}

TEST_CASE("Find relation with relation assign"){
    FamilyTree T = makeTree();
    T.addFather("yaakov","adam");
    T.addMother("zipi","adam");
    T.addMother("mira","hava");
    T.addFather("yagai","hava");
    T.addNew("haim",'m','s',"yaakov");
    T.addNew("juli",'f','c',"mira");
    T.addNew("koral",'f','w',"yefet");
    T.addNew("moshe",'m','g',"posher");
    T.addNew("menash",'m','g',"shem");
    T.addNew("tikva",'f','c',"mira");
    CHECK(T.findRelation("hava")==string("wife"));
    CHECK(T.findRelation("ham")==string("wife/cousin"));
    CHECK(T.findRelation("posher")==string("wife/cousin/cousin"));
    CHECK(T.findRelation("mira")==string("wife/mother"));
    CHECK(T.findRelation("yaakov")==string("father"));
    CHECK(T.findRelation("juli")==string("wife/mother/cousin"));
    CHECK(T.findRelation("shem")==string("cousin"));
    T.addNew("roni",'f','w',"shem");
    T.addNew("ben",'m','s',"roni");
    T.addNew("lior",'m','g',"shem");
    T.addNew("miri",'f','w',"ben");
    CHECK(T.findRelation("ben")==string("cousin/wife/sibling"));
    CHECK(T.findRelation("menash")==string("cousin/grand parent"));
    CHECK(T.findRelation("miri")==string("cousin/wife/sibling/wife"));
    CHECK(T.findRelation("kar")==string("wife/cousin/wife"));
    CHECK_THROWS(T.findRelation("bar"));
    CHECK_THROWS(T.findRelation("rivka"));

}

TEST_CASE("finds relation between 2 nodes in the tree"){
    FamilyTree T = makeTree();
    T.addFather("yaakov","adam");
    T.addMother("zipi","adam");
    T.addMother("mira","hava");
    T.addFather("yagai","hava");
    T.addNew("haim",'m','s',"yaakov");
    T.addNew("juli",'f','c',"mira");
    T.addNew("koral",'f','w',"yefet");
    T.addNew("moshe",'m','g',"posher");
    T.addNew("menash",'m','g',"shem");
    T.addNew("tikva",'f','c',"mira");
    T.addNew("roni",'f','w',"shem");
    T.addNew("ben",'m','s',"roni");
    T.addNew("lior",'m','g',"shem");
    T.addNew("miri",'f','w',"ben");
    CHECK(T.find("shem","hava")==string("cousin/wife"));
    CHECK(T.find("yaakov","mira")==string("father/wife/mother"));
    CHECK(T.find("ham","posher")==string("cousin"));
    CHECK(T.find("kar","adam")==string("wife/cousin/wife"));
    CHECK(T.find("yefet","zipi")==string("sibling/cousin/wife/mother"));
    CHECK(T.find("koral","posher")==string("wife/sibling/cousin"));
    CHECK(T.find("roni","miri")==string("sibling/wife"));
    CHECK(T.find("miri","ham")==string("wife/sibling/wife/cousin/wife/cousin"));
    CHECK(T.find("moshe","yagai")==string("grand parent/cousin/cousin/father"));
    CHECK_THROWS(T.find("shem","yael"));
    CHECK_THROWS(T.find("yam","baroch"));
    CHECK_THROWS(T.find("zlil","hava"));
}