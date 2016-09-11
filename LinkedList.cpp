#include "LinkedList.h"

LinkedList::Node::Node(Share data)
{
	value = data;
	next = NULL;
}

LinkedList::LinkedList()
{
	head_ = NULL;
	size_ = 0;
}

LinkedList::~LinkedList()
{
	Node* nodePtr = head_;
	Node* nextNode = NULL;
	while (nodePtr != NULL)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
		size_--;
	}
	nextNode = NULL;
}

unsigned int LinkedList::size() const
{
	return size_;
}

bool LinkedList::empty() const
{
	if (size_ == 0)
		return true;
	else
		return false;
}

Share LinkedList::select(unsigned int index) const
{
	Node* nodePtr = head_;
	Share val;
	for (int i = 0; i <= index; i++)
	{
		val = nodePtr->value;
		nodePtr = nodePtr->next;
	}
	return val;
}

unsigned int LinkedList::search(Share value) const
{
	Node* nodePtr = head_;
	for (int i = 0; i < size_; i++)
	{
		if (nodePtr->value == value)
			return i;
		else
			nodePtr = nodePtr->next;
	}
}

// 
LinkedList::Node* LinkedList::getNode(unsigned int index) const
{
	Node* nodePtr = head_;
	for (int i = 0; i < index; i++)
		nodePtr = nodePtr->next;
	return nodePtr;
}

void LinkedList::insert_front(Share value)
{
	if (size_ == 0)
	{
		Node* newNode = new Node(value);
		head_ = newNode;
		newNode->next = NULL;
	}
	else
	{
		Node* newNode = new Node(value);
		Node* nextNode = head_;
		head_ = newNode;
		newNode->next = nextNode;
	}
	size_++;
	return;
}

void LinkedList::remove(unsigned int index)
{
	if (index == 0)
		return remove_front();
	else
	{
		Node* delNode = head_;
		Node* nextNode = NULL;
		Node* prevNode = NULL;
		for (int i = 0; i < index; i++)
		{
			nextNode = delNode->next->next;
			prevNode = delNode;
			delNode = delNode->next;
		}
		delete delNode;
		prevNode->next = nextNode;
		size_--;
		return;
	}
}

void LinkedList::remove_front()
{
	if (size_ == 1)
	{
		Node* delNode = head_;
		delete delNode;
		head_ = NULL;
	}
	else
	{
		Node* delNode = head_;
		head_ = delNode->next;
		delete delNode;
	}
	size_--;
	return;
}