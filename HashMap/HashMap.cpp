/*
 * HashMap.cpp
 *
 *      Author: Irvin Favors
 *      F22-CISC220-010
 */

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	map = new hashNode *[101];
	for (int i = 0; i < 101; i++){
		map[i] = NULL;
	}
	first = "";
	numKeys = 0;
	mapSize = 101;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;
}
void hashMap::addKeyValue(string k, string v) {
	reHash();
	int x = calcHash(k);
	if (map[x] == NULL){
		map[x] = new hashNode(k,v);
		++numKeys;
	}else if (map[x] != NULL && map[x]->keyword == k){
		checkValsSize(x);
		map[x]->values[map[x]->currSize] = v;
		++map[x]->currSize;
	}else{
		hashcoll++;
		x = coll(x, k);
		if (map[x] == NULL){
			map[x] = new hashNode(k,v);
			++numKeys;
		}else if (map[x] != NULL && map[x]->keyword == k){
			checkValsSize(x);
			map[x]->values[map[x]->currSize] = v;
			++map[x]->currSize;
		}
	}
}

void hashMap::checkValsSize(int h){
	if (map[h]->currSize == map[h]->valuesSize){
		auto tmp = map[h]->values;
		int tmpSize = map[h]->currSize;
		map[h]->values = new string[map[h]->valuesSize*2];
		map[h]->valuesSize *= 2;
		for (int i = 0; i < tmpSize; i++){
			map[h]->values[i] = tmp[i];
		}
	}
}
int hashMap::getIndex(string k) {
	reHash();
	int x = calcHash(k);
	if (map[x] == NULL) {
		return -1;
	}
	if (map[x] != NULL && map[x]->keyword != k) x = coll(x, k);
	return x;
}

int hashMap::calcHash(string k){
	if (hashfn == true){
		return calcHash1(k);
	}
	return calcHash2(k);
}

int hashMap::calcHash2(string k){

	int hash = 0, l = k.length();
	for (int i = 0; i < l; ++i){
		hash = (hash*11 + ((int)k[l-i-1])) % mapSize;
	}
	return hash;
}
int hashMap::calcHash1(string k){
	/*
	 * Retrieves the ascii value of every character in the string,
	 * adds the value to 7 (a prime #) * hash (an int variable which updates
	 * for every character in the string), to produce a unique hash value based on the
	 * total of the ascii values of the characters within the string.
	 */
	int len = k.length(), hash = 0;
	for (int i = len - 1; i > 0; i--){
		hash = (7*hash + (int)k[i]) % mapSize;
	}
	return hash;
}
int hashMap::getClosestPrime(int n) {
	if (n & 1) n -= 2;
	else n--;
	int j;
	for (int i = n; i >= 2; i-=2){
		if (i % 2 == 0) continue;
		for (j = 3; j <= sqrt(i); j += 2){
			if (i % j == 0) break;
		}
		if (j > sqrt(i)) return i;
	}
	return 2;
}
void hashMap::reHash() {
	if (numKeys < mapSize*0.7) return;
	auto old = map;
	int newSize = getClosestPrime(mapSize*2);
	map = new hashNode *[newSize];
	int oldSize = mapSize;
	mapSize = newSize;
	numKeys = 0;

	for (int x = 0; x < mapSize; x++){
		map[x] = NULL;
	}
	for (int i = 0; i < oldSize; i++){
		if (old[i] != NULL){
			for (int j = 0; j < old[i]->currSize; j++){
				addKeyValue(old[i]->keyword, old[i]->values[j]);
			}
		}
	}
}

int hashMap::coll(int h, string k){
	if (collfn == true){
		return coll1(h, k);
	}
	return coll2(h, k);
}

int hashMap::coll1(int h, string k) {
	//Linear Probing:
	//once a value is mapped to an index, if index is occupied
	//look at the next index until you find one that is empty and then insert the value
	//
	//If you hit the end of the array (index == size of the array) loop to the beginning
	//and keep searching for an empty index
	int index = h;
	if (map[index] != NULL && map[index]->keyword == k) return index;
	while (map[index] != NULL){
		if (index == mapSize-1) index = -1;
		++index;
		++collisions;
		if (map[index] == NULL) break;
		if (map[index]->keyword == k) break;
	}
	return index;
}
int hashMap::coll2(int h, string k) {
	/*
	 * Quadratic Probing:
	 * Makes use of powers to find a new index, rather than continuously looking at the next index,
	 * in an effort to avoid clustering in a section of the array. Quadratic probing resulted in less
	 * sub-collisions for collisions that stem from indexes that have been mapped multiple times previously.
	 */
	int index = h, i = 1;
	if (map[index] != NULL && map[index]->keyword == k) return index;
	while (map[index] != NULL){
		index = (index + (int)pow(i,i)) % mapSize;
		++i; if (i == 10) i = 0;
		++collisions;
		if (map[index] == NULL) break;
		if (map[index]->keyword == k) break;
	}
	return index;
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


