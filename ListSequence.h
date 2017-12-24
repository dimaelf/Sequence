#include "Sequence.h"
#ifndef SEQUENCE_LISTSEQUENCE_H
#define SEQUENCE_LISTSEQUENCE_H

template <typename T> struct ListElement {
    T filling;
    ListElement* pnext;
};

template <typename T> class ListSequence : virtual public Sequence<T> {

private:
    int Length;
    int IsEmpty;
    ListElement <T>* pFirst;

    ListElement<T>* go_to(int index)
    {
        ListElement<T>* pCurrent = pFirst;
        for (int i = 0; i < index; i++)
        {
            pCurrent = pCurrent->pnext;
        }
        return pCurrent;
    }

    int map(T item)
    {
        ListElement<T>* pCurrent = pFirst;
        for (int i = 0; i < Length; i++) {
            if (item == pCurrent->filling)
                return i;
            pCurrent = pCurrent->pnext;
        }
        return -1;
    }

public:
    ListSequence() {
        Length = 0;
        IsEmpty = 0;
        pFirst = 0;
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
            Length = 1;
            pFirst = new ListElement<T>;
            pFirst->pnext = 0;
            pFirst->filling = item;
        }
        else
        {
            ListElement<T>* pCurrent = go_to(Length - 1);
            pCurrent->pnext = new ListElement<T>;
            pCurrent = pCurrent->pnext;
            pCurrent->filling = item;
            pCurrent->pnext = 0;
            Length++;
        }
    }

    T* GetFirst()
    {
        if (IsEmpty == 0)
            return 0;
        return &pFirst->filling;
    }

    T* GetLast()
    {
        if (IsEmpty == 0)
            return 0;
        return &go_to(Length-1)->filling;
    }

    T* Get(int index)
    {
        if ((IsEmpty == 0) || (index<0) || (index >= Length))
            return 0;
        return &go_to(index)->filling;
    }

    void Prepend(T item)
    {
        if (!IsEmpty)
        {
            IsEmpty = 1;
        }
        ListElement<T>* pnew = new ListElement<T>;
        pnew->filling = item;
        pnew->pnext = pFirst;
        pFirst = pnew;
        Length++;
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex)
    {
        ListSequence <T>* A = new ListSequence<T>();
        if (!((startIndex <0) || (endIndex >= Length) || (startIndex > endIndex) || (IsEmpty == 0)))
        {
            for (int i = startIndex; i <= endIndex; i++)
                A->Append(*Get(i));
        }
        return A;
    }

    void InsertAt(int index, T item)
    {
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == Length)
        {
            Append(item);
            return;
        }
        if ((index < 0) || (index > Length))
            return;
        ListElement<T>* pnew = new ListElement<T>;
        pnew->filling = item;
        pnew->pnext = go_to(index);
        go_to(index - 1)->pnext = pnew;
        Length++;
    }

    void RemoveFrom(int index)
    {
        if ((index < 0) || (index >= Length))
            return;
        ListElement<T>* ptemp = go_to(index);
        if (index == 0)
        {
            pFirst = ptemp->pnext;
        }
        else
        {
            go_to(index - 1)->pnext = ptemp->pnext;
        }
        delete ptemp;
        Length--;
        if (Length == 0)
        {
            IsEmpty = 0;
        }
    }

    void Remove(T item)
    {
        int index = map(item);
        if (index < 0)
            return;
        RemoveFrom(index);
    }

    void Swap (int i1, int i2){
        T temp = go_to(i1)->filling;
        go_to(i1)->filling = go_to(i2)->filling;
        go_to(i2)->filling = temp;
    }
};

#endif //SEQUENCE_LISTSEQUENCE_H
