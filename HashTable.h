#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Share.h"
#include "LinkedList.h"

class HashTable
{
public:
	// Constructor
	HashTable(unsigned int capacity);

	// Destructor
	~HashTable();

	// Member Functions
	bool search(string key, Share &stock);
	void insert(Share stock);
	void remove(string key);

private:
	// Private Member Variables
	unsigned int capacity_;
	unsigned int size_;
	LinkedList* table;

	// Private Functions
	unsigned int hashIndex(string key);
};

#endif