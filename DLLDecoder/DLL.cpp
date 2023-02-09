/*
 * DLL.cpp
 *
 *      Author: 13027
 */
//Part 1:(20 pts) (addFirst (3pts) ,addAtFront(4 pts),push (4 pts),pop(4 pts)) + getting secret message:5 pts
//In the DLL.cpp class, get push, pop, and addFirst and addAtFront working for a doubly linked list as specified in DLL.hpp and DLL.cpp.
//For this section I've given you the test cases.  You should get the output I've given you for part 1. When you get those methods working, running this will decode the secret code 1
//
//Once you have that working, start on part 2 (note you will have to go into Coder.cpp and toggle
//comments for lines 64-110 to run part 2)
//
//Part 2: (15 pts)(insertAt(5 pts), removeAtK(5 pts)) +secret message: 5 pts
//Get  the DLL.cpp methods insertAt and removeAtK methods working for a doubly linked list.
//I've given you the test cases and the output.  When you get them working, you should be able to run this and decode the second secret code
//
//Once you have that working, start on part 3 (note that you will have to go to Coder.cpp and toggle comments for lines 112-137 to run part 3)
//
//Part 3: (8 pts) (reverse (4 pts)) + secret message: 4 pts
//For this part, you will get the method reverse working for the DLL doubly linked list class.
//This method reverses the list.  Note: it doesn't just print out the list in reverse order, it actually reverses the list, so if the original list was 3<->2<->4<->8, with 3 being first and 8 being last, the reversed list would be 8<->4<->2<->3 with 8 being first and 3 being last.
//
//once you have that working, start on part 4 (note that you will have to go to Coder.cpp and toggle
//comments for lines 139-215 to run part 4)
//
//Part 4: (11 pts) (removeX (5 pts), call by pointer) + secret message: 6 pts
//For this part, you will get the method removeX to work.  removeX removes the value x from the linked list, and uses call by pointer to change the index parameter to be the index (count) of where x occurred in the list.  So, for instance if you had:
//7<->8<->3<->5<->2<->6<->1
//And you called: removeX(3,&ind)
//When  you leave the method, you’d have
//7<->8<->5<->2<->6<->1
//And ind would hold 2
//
//Once you have this working, start on part 5.  For this you will have to go to Coder.cpp and toggle comments for lines  217- 251
//
//Part 5: (21 pts)(skip – recursive (13 pts) + secret message: 8 pts
//For this part, you will get the method skip working for the DLL doubly linked list class. This method RECURSIVELY deletes every other node.  If the boolean flag is set to true, it will delete every even node (i.e.,if the list was
//3<->2<->4<->5<->1<->7,
//the list that would result after the skip method was called would be:
//3<->4<->1.
//If the flag is set to false, the resulting list will be
//2<->5<->7
//NOTE:  For efficiency's sake, this method SHOULD NOT call removeAtK



#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	size = 0;
}
DLL::DLL(int x){  // constructor, initializes a list with one new node with data x
	DNode *n = new DNode (x);
	first = n;
	last = n;
	size=1;
}
/***************************************************************************************************/
/*Part 1																																		*/
/***************************************************************************************************/
/* write push, pop, addAtFront */
void DLL::push(int x){
	DNode *tmp = new DNode(x);
	if (size == 0) {first = tmp; last = tmp;}
	else{
		tmp -> prev = last;
		last->next = tmp;
		last = tmp;
	}
	++size;
}

int DLL::pop(){
	DNode *tmp = last; int x = last->data;
	if (size > 0){
		if (size == 1){
			first = NULL;
			last = NULL;
			delete tmp;
			--size;
			return x;
		}
		last = last->prev;
		last->next = NULL;
		delete tmp;
		--size;
		return x;
	}
	return -1;

}
void DLL::addAtFront(int x){
	DNode *tmp = new DNode(x);
	tmp->next = first;
	first->prev = tmp;
	first = tmp;
	++size;
}
void DLL::addFirst(int x){
	DNode *tmp = new DNode(x);
	first = tmp;
	last = tmp;
	++size;
}
/***************************************************************************************************/
/*Part 2																																		*/
/***************************************************************************************************/
/* write insertAt, removeAtK  here */
void DLL::insertAt(int ind, int x){
	DNode *tmp; DNode *add = new DNode(x); int i = 0;
	if (ind == 0 && size == 0){
		first = add;
		last = add;
		++size;
	}else if (ind == 0){
		add->next = first;
		first->prev = add;
		first = add;
		++size;
	}else if (ind == size){
		last->next = add;
		add->prev = last;
		last = add;
		++size;
	}else{
		tmp = first; i = 0;
		while(i != ind-1){
			tmp = tmp->next;
			++i;
		}
		DNode *n = tmp->next;
		tmp->next = add;
		add->prev = tmp;
		add->next = n;
		n->prev = add;
		++size;
	}
}

int DLL::removeAtK(int ind){
	//cout << "Size: " << size << endl;
	DNode *tmp; int x = 0, i = 0;
	if (ind == 0){
		tmp = first; x = first->data;
		first = first->next;
		delete tmp;
		--size;
		return x;
	}else if (ind == size-1){
		return pop();
	}
	for (tmp = first; i < ind; i++){
		tmp = tmp->next;
	}
	x = tmp->data;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	delete tmp;
	--size;
	return x;
}


/****************************************************************************************/
/* Part 3                                                                                                                       */
/****************************************************************************************/
/* write reverse here */
void DLL::reverse(){
	DNode *tmp;
	DNode *curr = first;
	DNode *firstN = first;
	while (curr != NULL){
		tmp = curr->prev;
		curr->prev = curr->next;
		curr->next = tmp;
		curr = curr->prev;
	}

	if (tmp != NULL){
		first = tmp->prev;
		last = firstN;
	}
}
/****************************************************************************************/
/* Part 4                                                                                                                       */
/****************************************************************************************/
/* write removeX here */
void DLL::removeX(int x, int *ind){
	DNode *tmp = first; int i = 0;
	if (first->data == x){
		removeAtK(0);
		*ind = 0;
	}else {
		while (tmp->data != x && tmp->next != NULL){
			tmp = tmp->next;
			++i;
		}
		*ind = i;
		if (tmp->data == x && i == size-1){
			*ind = i;
			pop();
		}
		else if (tmp->next == NULL) { *ind = -1;}
		else {
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			--size;
		}
	}
}

/****************************************************************************************/
/* Part 5                                                                                                                     */
/****************************************************************************************/
/* write skip here */
void DLL::skip(bool flag){
	DNode *tmp, *curr; int count = size;
	//cout << size << endl;
	if (flag == true){
		tmp = first; first = first->next; delete tmp;
		curr = first;
		for(int i = 0; i < size; i+=2){
			tmp = curr->next;
			curr->next->next->prev = curr;
			curr->next = curr->next->next;
			delete tmp;
			--size;
			curr = curr->next;
		}
		--size;
	}else {
		curr = first;
		for(int i = 0; i < size; i+=2){
			tmp = curr->next;
			curr->next->next->prev = curr;
			curr->next = curr->next->next;
			delete tmp;
			--size;
			curr = curr->next;
		}
	}
}



/***************************************************************************************************/
/*End of your part																														*/
/***************************************************************************************************/

void DLL::printList() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	cout << endl;
}
void DLL::printCode() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << alpha[tmp->data];
		tmp = tmp->next;
	}
	cout << endl;
}
DLL::~DLL(){
	DNode *tmp = first;
	DNode *tmp2 = first->next;
	while (tmp != NULL) {
		delete tmp;
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
}



