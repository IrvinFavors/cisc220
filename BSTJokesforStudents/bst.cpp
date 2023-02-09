/*
 * By: Irvin Favors
 * F22-CISC220-010
 * bst.cpp
 */

#include "bst.hpp"
#include "Student.hpp"
bst::bst() {
	root = NULL;
}

bst::bst(string f, string l, int n, string j){
	root = new bstNode(f,l,n,j);
}

bool bst::insert(string f, string l, int num, string j){
	bstNode *tmp = new bstNode(f, l, num, j);
	if (root == NULL) {
		root = tmp;
		return true;
	}
	else{
		bstNode *n = root;
		while (n != NULL){
			if (l < n->student->last){
				if (n->left == NULL){
					n->left = tmp;
					tmp->parent = n;
					setHeight(tmp);
					return true;
				}else{
					n = n->left;
				}
			}else if (l > n->student->last){
				if (n->right == NULL){
					n->right = tmp;
					tmp->parent = n;
					setHeight(tmp);
					return true;
				}else{
					n = n->right;
				}
			}else if (l == n->student->last){
				if (f < n->student->first){
					if (n->left == NULL){
						n->left = tmp;
						tmp->parent = n;
						setHeight(tmp);
						return true;
					}else{
						n = n->left;
					}
				}else{
					if (n->right == NULL){
						n->right = tmp;
						tmp->parent = n;
						setHeight(tmp);
						return true;
					}else{
						n = n->right;
					}
				}
			}else{
				return false;
			}
		}
	}
	return false;
}

bstNode* bst::find(string l, string f){
	if (root == NULL) return NULL;
	else {
		bstNode *n = root;
		while (n != NULL){
			if (n->student->first == f && n->student->last == l){
				n->printNode();
				return n;
			}
			else if (l < n->student->last){
				n = n->left;
			}else if (l > n->student->last) {
				n = n->right;
			}else if (l == n->student->last){
				if (f < n->student->first){
					n = n->left;
				}else {
					n = n->right;
				}
			}
		}
	}
	return NULL;
}

void bst::printTreeIO(){
	if (root == NULL){
		cout << "Empty Tree" << endl;
	}else{
		cout << endl << "Printing In Order:" << endl;
		printTreeIO(root);
	}
}

void bst::printTreeIO(bstNode *n){
	if (n == NULL) return;
	else {
		printTreeIO(n->left);
		n->printNode();
		printTreeIO(n->right);
	}
}

void bst::printTreePre(){
	if (root == NULL){
		cout << "Empty Tree" << endl;
	}else{
		cout << endl << "Printing PreOrder:" << endl;
		printTreePre(root);
	}
}

void bst::printTreePre(bstNode *n){
	if (n == NULL) return;
	else {
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void bst::printTreePost(){
	if (root == NULL){
		cout << "Empty Tree" << endl;
	}else{
		cout << endl << "Printing PostOrder:" << endl;
		printTreePost(root);
	}
}

void bst::printTreePost(bstNode *n){
	if (n == NULL) return;
	else {
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}

void bst::clearTree() {
    if (root == NULL){
        cout << "Tree already empty" << endl;
    }else {
        cout << endl << "Clearing Tree:" << endl;
        clearTree(root);
        root = NULL;
    }
}

void bst::clearTree(bstNode *tmp){
    if (tmp == NULL) return;
    else {
        clearTree(tmp->left);
        clearTree(tmp->right);
        tmp->printNode();
        delete(tmp);
    }
}

bstNode* bst::remove(string l, string f){
	bstNode *tmp = find(l,f);
	if (tmp->left == NULL && tmp->right == NULL){
		//cout << "no kids" <<endl;
		removeNoKids(tmp);
	}else if (tmp->left != NULL && tmp->right == NULL){
		//cout << "one kid" << endl;
		removeOneKid(tmp, true);
	}else if (tmp->left == NULL && tmp->right != NULL){
		//cout << "one kid" << endl;
		removeOneKid(tmp, false);
	}else if (tmp->left != NULL && tmp->right != NULL){
		//cout << "two kids" << endl;
		bstNode *n = tmp->right;
		while (n->left != NULL){
			n = n->left;
		}
		n = remove(n->student->last, n->student->first);
		n->left = tmp->left;
		n->right = tmp->right;
		n->parent = tmp->parent;
		if (tmp->right != NULL) tmp->right->parent = n;
		if (tmp->left != NULL) tmp->left->parent = n;
		if (tmp->parent->right->student->last == tmp->student->last){
			tmp->parent->right = n;
		}else{
			tmp->parent->left = n;
		}
	}
	setHeight(tmp);
	return tmp;
}

bstNode* bst::removeNoKids(bstNode *tmp){
	if (tmp->left == NULL && tmp->right == NULL){
		if (tmp->parent->left->student->last == tmp->student->last){
			tmp->parent->left = NULL;
		}else {
			tmp->parent->right = NULL;
		}
	}
	return tmp;
}

bstNode* bst::removeOneKid(bstNode *tmp, bool leftFlag){
	if (leftFlag == true){
		if (tmp->parent->right->student->last == tmp->student->last){
			tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
		}else {
			tmp->parent->left = tmp->left;
			tmp->left->parent = tmp->parent;
		}
	}else {
		if (tmp->parent->right->student->last == tmp->student->last){
			tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;
		}else {
			tmp->parent->left = tmp->right;
			tmp->right->parent = tmp->parent;
		}
	}
	return tmp;
}

void bst::setHeight(bstNode *n){
	if (n == NULL || n == root) return;
	bstNode *tmp = n->parent;
	while (tmp != NULL){
		int hL = 0, hR = 0;
		if (tmp == NULL) break;
		if (tmp->left != NULL) hL = tmp->left->height;
		if (tmp->right != NULL) hR = tmp->right->height;
		int height = max(hL, hR) + 1;
		if (height == tmp->height) break;
		tmp->height = height;
		tmp = tmp->parent;
	}

}

