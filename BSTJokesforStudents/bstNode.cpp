/*
 * By: Irvin Favors
 * F22-CISC220-010
 * bstNode.cpp
 */


#include "bstNode.hpp"

bstNode::bstNode(){
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 0;
	student = NULL;
}

bstNode::bstNode(string fName, string lName, int favNum, string joke){
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 1;
	student = new Student(fName, lName, favNum, joke);
}

bstNode::~bstNode(){
	cout << "deleting" << endl;
}

void bstNode::printNode(){
	cout << "Height of node: " << height << endl;
	cout << "Name: " << student->first << " " << student->last << endl;
	cout << "Joke: " << student->joke << endl;
	cout << "Student's Favorite Number: " << student->fav_num << endl;
	cout << "************************************************************"<<endl;
}
