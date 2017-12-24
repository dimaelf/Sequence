#include "Sequence.h"
using namespace std;
#ifndef SEQUENCE_ARRAYSEQUENCE_H
#define SEQUENCE_ARRAYSEQUENCE_H

template <typename T> class ArraySequence : virtual public Sequence<T>{

private:
    int Length;
    int IsEmpty;
    int VocantPlaces;
    T* pointer;

    int map(T item)
    {
        for (int i = 0; i < Length; i++) {
            if (item == *(pointer + i))
                return i;
        }
        return -1;
    }

public:
    ArraySequence() {
        Length = 0;
        IsEmpty = 0;
        VocantPlaces = 0;
        pointer = 0;
    }

    int getLength() {
        return Length;
    }

    int getIsEmpty() {
        return IsEmpty;
    }

    void Append(T item)
    {
        if (!IsEmpty)
        {
            IsEmpty = 1;
            VocantPlaces = 0;
            Length = 1;
            pointer = (T*)malloc(sizeof(T));
            *pointer = item;
        }
        else
        {
            if (VocantPlaces!=0)
            {
                *(pointer + Length) = item;
                VocantPlaces--;
                Length++;
            }
            else
            {
                T* pold = pointer;
                pointer = (T*)malloc(2 * Length*sizeof(T));
                for (int i = 0; i < Length; i++)
                    *(pointer + i) = *(pold + i);
                VocantPlaces = Length - 1;
                *(pointer + Length) = item;
                Length++;
                free(pold);
            }
        }
    }

    T* GetFirst()
    {
        if (IsEmpty == 0)
            return 0;
        return pointer;
    }

    T* GetLast()
    {
        if (IsEmpty == 0)
            return 0;
        return (pointer + Length - 1);
    }

    T* Get(int index)
    {
        if ((IsEmpty == 0)||(index<0)||(index>=Length))
            return 0;
        return (pointer + index);
    }

    void Prepend (T item)
    {
        if (!IsEmpty)
        {
            IsEmpty = 1;
            VocantPlaces = 0;
            Length = 1;
            pointer = (T*)malloc(sizeof(T));
            *pointer = item;
        }
        else
        {
            if (VocantPlaces)
            {
                for (int i = Length; i > 0; i--)
                {
                    *(pointer + i) = *(pointer + i - 1);
                }
                *pointer = item;
                VocantPlaces--;
                Length++;
            }
            else
            {
                T* pold = pointer;
                pointer = (T*)malloc(2 * Length*sizeof(T));
                for (int i = Length; i >0; i--)
                    *(pointer + i) = *(pold + i-1);
                VocantPlaces = Length - 1;
                *pointer = item;
                Length++;
                free(pold);
            }
        }
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex)
    {
        ArraySequence <T>* A = new ArraySequence<T>();
        if (!((startIndex <0) || (endIndex >= Length) || (startIndex > endIndex)||(IsEmpty==0)))
        {
            for (int i = startIndex; i <= endIndex; i++)
                A->Append(*Get(i));
        }
        return A;
    }

    void InsertAt(int index, T item)
    {
        if (index < 0)
            return;
        if (index > Length)
            return;
        if (VocantPlaces)
        {
            for (int i = Length; i > index; i--)
            {
                *(pointer + i) = *(pointer + i - 1);
            }
            *(pointer + index) = item;
            VocantPlaces--;
            Length++;
        }
        else
        {
            T* pold = pointer;
            pointer = (T*)malloc(2 * Length*sizeof(T));
            for (int i = Length; i >index; i--)
                *(pointer + i) = *(pold + i - 1);
            VocantPlaces = Length - 1;
            *(pointer+index) = item;
            Length++;
            for (int i = 0; i < index; i++)
                *(pointer + i) = *(pold + i);
            free(pold);
        }
    }

    void RemoveFrom(int index)
    {
        if ((index < 0) || (index >= Length))
            return;
        if (Length == 1)
        {
            IsEmpty = 0;
            free(pointer);
            pointer = 0;
            VocantPlaces = 0;
            Length = 0;
            return;
        }
        for (int i = index; i < Length-1; i++) {
            *(pointer + i) = *(pointer + i + 1);
        }
        Length--;
        VocantPlaces++;
    }

    void Remove(T item)
    {
        int index = map(item);
        if (index < 0)
            return;
        RemoveFrom(index);
    }

    void Swap (int i1, int i2){
        T temp = *(pointer+i1);
        *(pointer+i1) = *(pointer+i2);
        *(pointer+i2) = temp;
    }

};

#endif //SEQUENCE_ARRAYSEQUENCE_H
