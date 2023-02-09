/*
 * By: Irvin Favors
 * F22-CISC220-010
 * bstNode.hpp
 */

#ifndef bstNode_HPP_
#define bstNode_HPP_

#include "Student.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

class bstNode {
public:
	bstNode *left;
	bstNode *right;
	bstNode *parent;
	int height;
	Student *student;
	bstNode();
	bstNode(string fName, string lName, int favNum, string joke);
	~bstNode();
	void printNode();

};



#endif
