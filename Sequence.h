

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H


template<typename T> class Sequence {

public:
	virtual int getLength() = 0;
	virtual int getIsEmpty() = 0;
	virtual void Append(T item) = 0;
	virtual T* GetFirst() = 0;
	virtual T* GetLast() = 0;
	virtual T* Get(int index) = 0;
	virtual void Prepend(T item) = 0;
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
	virtual void InsertAt(int index, T item) = 0;
	virtual void Remove(T item) = 0;
    virtual void RemoveFrom (int index) = 0;
    virtual void Swap(int i1, int i2) = 0;
};


#endif //SEQUENCE_SEQUENCE_H
