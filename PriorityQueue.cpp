#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(unsigned int capacity)
{
	capacity_ = capacity;
	heap_ = new Share[capacity_ + 1];
	size_ = 0;
}

PriorityQueue::~PriorityQueue()
{
	delete [] heap_;
	heap_ = NULL;
}

unsigned int PriorityQueue::size() const
{
	return size_;
}

bool PriorityQueue::empty() const
{
	if (size_ == 0)
		return true;
	else
		return false;
}

bool PriorityQueue::full() const
{
	if (size_ == capacity_)
		return true;
	else
		return false;
}

Share PriorityQueue::max() const
{
	return heap_[1];
}

void PriorityQueue::enqueue(Share val)
{
	heap_[size_ + 1] = val;
	size_++;
	int i = size_;
	Share temp;

	while (heap_[i / 2].getFactor() <= heap_[i].getFactor() && i != 1)
	{
		temp = heap_[i];
		heap_[i] = heap_[i / 2];
		heap_[i / 2] = temp;
		i = i / 2;
	}
}

void PriorityQueue::dequeue()
{
	heap_[1] = heap_[size_];
	size_--;
	int i = 1;
	int childNode = 0;
	Share maxChild;
	Share temp;

	while (2 * i <= size_)
	{
		childNode = 2 * i;
		maxChild = heap_[childNode];
		if (heap_[childNode + 1].getFactor() > maxChild.getFactor())
		{
			childNode++;
			maxChild = heap_[childNode];
		}

		if (heap_[i].getFactor() < maxChild.getFactor())
		{
			temp = heap_[i];
			heap_[i] = maxChild;
			heap_[childNode] = temp;
			i = childNode;
		}
		else
			break;
	}
}