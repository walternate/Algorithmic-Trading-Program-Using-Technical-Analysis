#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Share.h"
using namespace std;

class LinkedList
{
private:
	
	// The node structure used for the Linked List.
	struct Node {
		Node(Share value);
		Share value;
		Node* next;
	};

	// Private method to get the node at an index. This is optional, but you
	// will probably find it useful.
	Node* getNode(unsigned int index) const;

	// MEMBER VARIABLES
	// A pointer to the head node of the list.
	Node* head_;

	// The number of elements in the list.
	unsigned int size_;

public:
	// CONSTRUCTOR/DESTRUCTOR
	// Create a new empty Linked List.
	LinkedList();
	// Destroy this Linked List, freeing all dynamically allocated memory.
	~LinkedList();

	// ACCESSORS
	// Returns the number of elements in the list.
	unsigned int size() const;
	// Returns true if the list is empty, false otherwise.
	bool empty() const;
	// Returns the value at the given index in the list.
	Share select(unsigned int index) const;
	// Searches for the given value, and returns the index of this value.
	unsigned int search(Share val) const;

	// MUTATORS
	// Inserts a Share object at the front of the list.
	void insert_front(Share val);
	// Deletes a value from the list at the given index.
	void remove(unsigned int index);
	// Deletes value at front of list
	void remove_front();
};

#endif