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