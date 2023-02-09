/*
 * Dog.cpp
 *
 * Irvin Favors
 */

#include "Dog.hpp"

using namespace std;

Dog::Dog(string n){
	name = n;
	strength = 50;
	x = 0;
	y = 0;
}

Dog::Dog(){
	name = "flash";
	strength = 50;
	x = 0;
	y = 0;
}

bool Dog::changeStrength(int amt){
	strength+=amt;
	printDog();
	if (strength <= 0){die(); return false;}
	return true;
}

void Dog::die(){
	cout << "Sadly the life of " << name << " has ended :(" << "\n";
}

void Dog::printDog(){
	cout << "Name: " << name << " Strength: " << strength << "\n";
}

void Dog::won(){
	cout << name << " has successfully made it out of the forest!" << "\n";
}

void Dog::reset(){
	strength=50;
	x = 0;
	y = 0;
}

