/*
 * Dog.hpp
 *
 * Irvin Favors
 */

#ifndef DOG_HPP_
#define DOG_HPP_
#include <bits/stdc++.h>

using namespace std;

class Dog {
	friend class Board;
	string name;
	int strength;
	int x;
	int y;

public:
	Dog();
	Dog(string n);
	bool changeStrength(int amt);
	void die();
	void printDog();
	void won();
	void reset();
};




#endif /* DOG_HPP_ */
