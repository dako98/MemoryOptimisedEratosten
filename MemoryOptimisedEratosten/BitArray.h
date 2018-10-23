#ifndef _BIT_ARRAY_
#define _BIT_ARRAY_


class BitArray
{
public:


	BitArray();
	BitArray(int requiredSize);
	~BitArray();
	BitArray(const BitArray &other);
	BitArray& operator=(const BitArray &other);

	bool operator[](int index) const;
//	bool operator[](int index);				I can't think of a better way at this time
	bool SetBit(int index, bool value);

	void PrintDebug()const;

private:



	
	void ResizeUp();

	void Copy(const BitArray &other);
	void Clear();

	size_t CalculateBits(int size) const;
	size_t CalculateNeededBlocks(int neededCapacity) const;
	size_t CalculateBlock(int index) const;


	size_t size;
	size_t capacity;
	size_t blocks;

	unsigned int* elements;


};








#endif // !_BIT_ARRAY_
