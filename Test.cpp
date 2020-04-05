#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;
using namespace family;


// Functions to make global tree
Tree& makeTree(){
    Tree T("Yosef");
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
    return T;
}


// Test Cases

TEST_CASE("Unrelated Case"){
    Tree T = makeTree();
    CHECK(T.relation("Omri") == string("unrelated"));
	CHECK(T.relation("Dan") == string("unrelated"));
	CHECK(T.relation("Shmuel") == string("unrelated"));
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.relation("Rachel") == string("mother"));
	CHECK(T.relation("sava") == string("unrelated"));
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.relation("Quar") == string("unrelated"));
	CHECK(T.relation("quar") == string("unrelated"));
	CHECK(T.relation("Rivka") == string("grandmother"));
}

TEST_CASE("find Case"){
    Tree T = makeTree();
    CHECK(T.find("grandmother") == string("Rivka"));
    CHECK(T.find("grandfather") == string("Isaac"));
    CHECK(T.find("Mother") == string("Rachel"));
    T.remove("Terah");
    T.addFather("Avraham", "Omer");
    CHECK(T.find("great-great-grandfather") == string("Omer"));
    T.addMother("Isaac","Dana");
    CHECK(T.find("great-grandmother") == string("Dana"));
    T.addMother("Omer","Olga");
    CHECK(T.find("Olga") == string("great-great-great-great-grandmother"));
    T.remove("Yaakov");
    CHECK_THROWS(T.find("dana"));
    CHECK_THROWS(T.find("avi"));
    CHECK_THROWS(T.find("avichai"));
    CHECK_THROWS(T.find("avihai"));
}

TEST_CASE("Exception Case") {
    Tree T = makeTree();
    T.remove("Yosef"); // remove the whole tree.
    CHECK_THROWS(T.find("ron"));
    CHECK_THROWS(T.find("omri"));
    CHECK_THROWS(T.find("yogev"));
    CHECK_THROWS(T.find("dag"));
    CHECK_THROWS(T.find("sos"));
    CHECK_THROWS(T.find("hamor"));
    CHECK_THROWS(T.find("ori"));
    CHECK_THROWS(T.find("shani"));
    CHECK_THROWS(T.find("dana"));
    CHECK_THROWS(T.find("avi"));
    CHECK_THROWS(T.find("avichai"));
    CHECK_THROWS(T.find("avihai"));
}

TEST_CASE("remove function") {
    Tree T = makeTree();
    CHECK(T.find("father") == string("Yaakov"));
    CHECK(T.find("mother") == string("Rachel"));
    T.remove("Isaac");
    CHECK_THROWS(T.find("Isaac")));
    CHECK_THROWS(T.find("Avraham"));
    CHECK_THROWS(T.find("Terah"));
    CHECK(T.find("Rivka")==string("grandmother"));
    T.addFather("Rachel","Roni");
    T.addMother("Rachel","Mimi");
    CHECK_THROWS(T.remove("mishu"));
    CHECK_THROWS(T.remove("yeled"));
    CHECK_THROWS(T.remove("tarah"));
    T.remove("Rachel");
    CHECK_THROWS(T.find("mother");
    
}

TEST_CASE("relation function"){
    Tree T = makeTree();
    CHECK(T.relation("Rivka")==string("grandmother"));
    CHECK(T.relation("mishu")==string("unrelated"));
    CHECK(T.relation("yeled")==string("unrelated"));
    CHECK(T.relation("gibor")==string("unrelated"));
    CHECK(T.relation("mami")==string("unrelated"));
    CHECK(T.relation("gidi")==string("unrelated"));
    T.addFather("Rivka","Baroh");
    T.addMother("Rivka","Zipi");
    CHECK(T.relation("Baroh")==string("great-grandfather"));
    CHECK(T.relation("Zipi")==string("great-grandmother"));
    T.addFather("Terah","Yigal");
    T.addMother("Terah","Miri");
    CHECK(T.relation("Yigal")==string("great-great-grandfather"));
    CHECK(T.relation("Miri")==string("great-great-grandmother"));
    CHECK(T.relation("parent")==string("unrelated"));
    CHECK(T.relation("Yiga")==string("unrelated"));


}

TEST_CASE("check the find function"){
    Tree T = makeTree();
    T.addFather("Terah","Yigal");
    T.addMother("Terah","Miri");
    T.addFather("Rivka","Baroh");
    T.addMother("Rivka","Zipi");
    CHECK(T.find("father")==string("Yaakov"));
    CHECK(T.find("great-grandfather")==string("Avraham"));
    CHECK(T.find("great-great-grandfather")==string("Terah"));
    CHECK_THROWS(T.find("great-grandmother")); 
    CHECK(T.find("great-grear-great-grandfather")==string("Yigal"));
    CHECK(T.find("grandmother")==string("Rivka"));
    CHECK(T.find("great-grandmother")==string("Zipi"));
    CHECK_THROWS(T.find("great-great-great-great-grandmother")); 
    T.remove("Isaac");
    CHECK_THROWS(T.find("great-great-grandmother"));
    CHECK_THROWS(T.find("great-great-grandfather"));
    T.remove("Rivka");
    CHECK_THROWS(T.find("grandmother"));
    CHECK_THROWS(T.find("grandfather"));
 

}