#include "BitArray.h"
#include <iostream>

BitArray::BitArray()
{
	size = 0;
	blocks = 1;
	capacity = CalculateBits(blocks);
	elements = new unsigned int[blocks];

	for (size_t i = 0; i < blocks; i++)
	{
		elements[i] = 0;
	}
}

BitArray::~BitArray()
{
	Clear();
}

BitArray::BitArray(int requiredSize)
{
	size = 0;

	capacity = requiredSize;
	blocks = CalculateNeededBlocks(requiredSize);


	elements = new unsigned int[blocks];

	for (size_t i = 0; i < blocks; i++)
	{
		elements[i] = 0;
	}
}

BitArray::BitArray(const BitArray &other)
{
	Copy(other);
}

BitArray& BitArray::operator=(const BitArray &other)
{
	if (this!=&other)
	{
		Clear();
		Copy(other);
	}
	return *this;
}

bool BitArray::operator[](int index) const
{
	if (index <0 || index>capacity)
	{
		throw std::out_of_range("Out of range!");
	}

	return (elements[CalculateBlock(index)] & 1 <<
		(((sizeof(unsigned int) * 8)) - (index % (sizeof(unsigned int) * 8))-1)) !=0;
}

bool BitArray::SetBit(int index, bool value)
{
	//Not tested. Need sleep...
	while (index>capacity)
	{
		ResizeUp();
	}

	if (value == true)
	{
		return elements[CalculateBlock(index)] |= 1 <<
			(((sizeof(unsigned int) * 8) - 1) - index % (sizeof(unsigned int) * 8));
	}
	if (value == false)
	{
		return (elements[CalculateBlock(index)]) &= ~(1 <<
			(((sizeof(unsigned int) * 8) - 1) - index % (sizeof(unsigned int) * 8)));
	}
}

size_t BitArray::CalculateBits(int size) const
{
	return size * sizeof(unsigned int) * 8;
}

size_t BitArray::CalculateNeededBlocks(int neededCapacity) const
{
	size_t neededBlocks = 0;

	while (neededCapacity>=0)
	{
		neededCapacity -= (sizeof(unsigned int) * 8);
		neededBlocks++;
	}
	return neededBlocks;
}

//Test this function!!!
size_t BitArray::CalculateBlock(int index) const
{
	size_t targetBlock = CalculateNeededBlocks(index);


	if (index % (sizeof(unsigned int) * 8) == 0)
		targetBlock - 1;

	return targetBlock - 1;
}


void BitArray::ResizeUp()
{
	unsigned int* temp = new unsigned int[blocks * 2];

	for (size_t i = 0; i < blocks; i++)
	{
		temp[i] = elements[i];
	}

	for (size_t i = blocks; i < blocks*2; i++)
	{
		temp[i] = 0;
	}

	blocks *= 2;
	capacity *= 2;

	elements = temp;
	temp = nullptr;
}

void BitArray::Copy(const BitArray &other)
{
	this->elements = new unsigned int[other.blocks];

	for (size_t i = 0; i < other.blocks; i++)
	{
		this->elements[i] = other.elements[i];
	}

	this->size = other.size;
	this->capacity = other.capacity;
	this->blocks = other.blocks;
}

void BitArray::Clear()
{
	delete[] elements;
	elements = nullptr;
	size = 0;
	capacity = 0;
	blocks = 0;
}

void BitArray::PrintDebug()const
{
	std::cout << "Array contents: ";
	for (size_t i = 0; i < blocks; i++)
	{
		std::cout << elements[i]<<" ";
	}
}
