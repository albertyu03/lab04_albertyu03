// intbst.cpp
// Implements class IntBST
// Albert Yu, 2/9/2022

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(n == NULL) {
	    return;
    }
    if(n->left != NULL) {
    	printInOrder(n->left);
    }
    cout << n->info << " ";
    if(n->right != NULL) {
    	printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(n == NULL) {
    	return;
    }
    if(n->left != NULL) {
    	printPostOrder(n->left);
    }
    if(n->right != NULL) {
    	printPostOrder(n->right);
    }
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n == NULL) {
	return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
	if(n == NULL) {
		return 0;
	}
	return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
	if(n == NULL) {
		return NULL;
	}
	if(n->info == value) {
		return n;
	}
	if(value < n->info) {
		if(n->left == NULL) {
			return NULL;
		}
		return getNodeFor(value, n->left);
	} else if(value > n->info) {
		if(n->right == NULL) {
			return NULL;
		}
		return getNodeFor(value, n->right);
	} else {
		cout << "shouldn't get here" << endl;
		return NULL;
	}
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
	Node* cNode = root;
	while(cNode != NULL) {
		if(cNode->info < value) {
			if(cNode->right == NULL) {
				return false;
			}
			cNode = cNode->right;
		} else if(cNode->info > value) {
			if(cNode->left == NULL) {
				return false;
			}
			cNode = cNode->left;
		} else {
			return true;
		}
	}
	return false;//if cNode = null
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
	Node* n;
	if(contains(value)) {
		n = getNodeFor(value, root);
	} else {
		return NULL;
	}

	if(n->left != NULL) { //has left child
		n = n->left;
		while(n->right != NULL) {
			n = n->right;
		}
		return n;
	} else { //no left child
		while(n->parent != NULL) {
			n = n->parent;
			if(n->info < value) {
				return n;
			}
		}
		return NULL;
	}
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
	Node* n = getPredecessorNode(value);
	if(n == NULL) {
		return 0;
	} else {
		return n->info;
	}
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
        Node* n;
        if(contains(value)) {
                n = getNodeFor(value, root);
        } else {
                return NULL;
        }

        if(n->right != NULL) { //has right child
                n = n->right;
                while(n->left != NULL) {
                        n = n->left;
                }
                return n;
        } else { //no right child
                while(n->parent != NULL) {
                        n = n->parent;
                        if(n->info > value) {
                                return n;
                        }
                }
                return NULL;
        }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
	Node* n = getSuccessorNode(value);
	if(n == NULL) {
		return 0;
	} else {
		return n->info;
	}
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if(!(contains(value))) {
    	return false;
    }
    Node* n = getNodeFor(value, root);
    if(n->left == NULL && n->right == NULL) { //case 1: leaf node
    	if(n->parent == NULL) {
		root = NULL;
		delete n;
		return true;
	}
    	Node* nPar = n->parent;
	if(nPar->left == n) {
		delete n;
		nPar->left = NULL;
	} else {
		delete n;
		nPar->right = NULL;
	}
    } else if(n->left == NULL || n->right == NULL) { //case 2: internal with one child
    	if(n->parent == NULL) {
		if(n->left != NULL) {
			root = n->left;
			root->parent = NULL;
		} else {
			root = n->right;
			root->parent = NULL;
		}
		delete n;
	}
	Node* nPar = n->parent;
	Node* nChi;
	if(n->left != NULL) {
		nChi = n->left;
	} else {
		nChi = n->right;
	}
	if(nPar->left == n) {
		nPar->left = nChi;
		delete n;
	} else {
		nPar->right = nChi;
		delete n;
	}

    } else { //case 3: internal with 2 children
    	Node* nSuc = getSuccessorNode(n->info);
	int sucInf = nSuc->info;
	remove(nSuc->info);
	n->info = sucInf;
    }
    return true;
}
