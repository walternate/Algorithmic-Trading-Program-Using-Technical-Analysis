#include "HashTable.h"


// Constructor
HashTable::HashTable(unsigned int capacity)
{
	table = new LinkedList[capacity];
	capacity_ = capacity;
	size_ = 0;
}

// Destructor
HashTable::~HashTable()
{
	delete [] table;
	table = NULL;
}

// Member Functions
bool HashTable::search(string key, Share &stock)
{
	unsigned int index = hashIndex(key);
	unsigned int items = table[index].size();

	for (int i = 0; i < items; i++)
	{
		if (table[index].select(i).getTicker() == key)
		{
			stock = table[index].select(i);
			return true;
		}
	}
	return false;
}

void HashTable::insert(Share stock)
{
	string key = stock.getTicker();
	unsigned int index = hashIndex(key);
	table[index].insert_front(stock);
}

void HashTable::remove(string key)
{
	unsigned int index = hashIndex(key);
	unsigned int items = table[index].size();

	for (int i = 0; i < items; i++)
	{
		if (table[index].select(i).getTicker() == key)
			return table[index].remove(i);
	}
}

unsigned int HashTable::hashIndex(string key)
{
	int index = 1;

	for (int i = 0; i < key.length(); i++)
		index *= key[i];

	return (index % capacity_);
}