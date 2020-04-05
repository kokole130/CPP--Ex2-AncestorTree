#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;
using namespace family;


// Functions to make global tree
Tree makeTree(){
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
    CHECK_THROWS(T.find("Isaac"));
    CHECK_THROWS(T.find("Avraham"));
    CHECK_THROWS(T.find("Terah"));
    CHECK(T.find("Rivka")==string("grandmother"));
    T.addFather("Rachel","Roni");
    T.addMother("Rachel","Mimi");
    CHECK_THROWS(T.remove("mishu"));
    CHECK_THROWS(T.remove("yeled"));
    CHECK_THROWS(T.remove("tarah"));
    T.remove("Rachel");
    CHECK_THROWS(T.find("mother"));
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

TEST_CASE("Unrelated"){
    Tree T = makeTree();
    CHECK(T.relation("Monika") == string("unrelated"));
    T.addMother("Isaac","Monika");
    CHECK(T.relation("Monika") == string("great-great-great-grandmother"));
    CHECK(T.relation("Rachely") == string("unrelated"));
	CHECK(T.relation("xyz") == string("unrelated"));
	CHECK(T.relation("kk") == string("unrelated"));
}

TEST_CASE("Find function"){
    Tree T = makeTree();
    CHECK(T.find("great-great-grandfather") == string("Terah"));
    CHECK(T.find("great-grandfather") == string("Avraham"));
    CHECK(T.find("grandfather") == string("Isaac"));
    CHECK(T.find("grandmother") == string("Rivka"));
    CHECK(T.find("mother") == string("Rachel"));
    CHECK(T.find("father") == string("Yaakov"));
}

TEST_CASE("Relation function") {
    Tree T2 = makeTree();
    CHECK(T2.relation("yaakov")==string("father"));
    CHECK(T2.relation("Rachel")==string("mother"));
    CHECK(T2.relation("Rivka")==string("grandmother"));
    CHECK(T2.relation("Isaac")==string("grandfather"));
    CHECK(T2.relation("Avraham")==string("great-grandfather"));
    CHECK(T2.relation("Terah")==string("great-great-grandfather"));
}

TEST_CASE("Addfather function") {
    Tree T("a");
    T.addFather("a","aa");
    CHECK(T.relation("aa")==string("father"));
    CHECK(T.find("father") == string("aa"));
    T.addFather("aa","aaa");
    CHECK(T.relation("aaa")==string("grandfather"));
    CHECK(T.find("grandfather") == string("aaa"));
    T.addFather("aaa","aaaa");
    CHECK(T.relation("aaaa")==string("great-grandfather"));
    CHECK(T.find("great-grandfather") == string("aaaa"));
    T.addFather("aaaa","aaaaa");
    CHECK(T.relation("aaaaa")==string("great-great-grandfather"));
    CHECK(T.find("great-great-grandfather") == string("aaaaa"));
    T.addFather("aaaaa","aaaaaa");
    CHECK(T.relation("aaaaaa")==string("great-great-great-grandfather"));
    CHECK(T.find("great-great-great-grandfather") == string("aaaaaa"));
    T.addFather("aaaaaa","aaaaaaa");
    CHECK(T.relation("aaaaaaa")==string("great-great-great-great-grandfather"));
    CHECK(T.find("great-great-great-great-grandfather") == string("aaaaaa"));
}

TEST_CASE("Addmother function") {
    Tree T("a");
    T.addMother("a","aa");
    CHECK(T.relation("aa")==string("mother"));
    CHECK(T.find("mother") == string("aa"));
    T.addMother("aa","aaa");
    CHECK(T.relation("aaa")==string("grandmother"));
    CHECK(T.find("grandmother") == string("aaa"));
    T.addMother("aaa","aaaa");
    CHECK(T.relation("aaaa")==string("great-grandmother"));
    CHECK(T.find("great-grandmother") == string("aaaa"));
    T.addMother("aaaa","aaaaa");
    CHECK(T.relation("aaaaa")==string("great-great-grandmother"));
    CHECK(T.find("great-great-grandmotherr") == string("aaaaa"));
    T.addMother("aaaaa","aaaaaa");
    CHECK(T.relation("aaaaaa")==string("great-great-great-grandmother"));
    CHECK(T.find("great-great-great-grandmother") == string("aaaaaa"));
    T.addMother("aaaaaa","aaaaaaa");
    CHECK(T.relation("aaaaaaa")==string("great-great-great-great-grandmother"));
    CHECK(T.find("great-great-great-great-grandmother") == string("aaaaaa"));
}

TEST_CASE("Empty string") {
    Tree T = makeTree();
    CHECK_THROWS(T.remove("")); // remove the whole tree.
    CHECK_THROWS(T.find(""));
    CHECK_THROWS(T.addFather("Terah",""));
    CHECK_THROWS(T.addMother("Terah",""));
    CHECK_THROWS(T.addFather("","Moses"));
    CHECK_THROWS(T.addFather("","Hava"));
    CHECK_THROWS(T.addFather("",""));
    CHECK_THROWS(T.addMother("",""));
}