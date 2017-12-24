#include <iostream>
using namespace std;

template <typename T> int BasicTest(int mode)
{
    T S = T();
    if (S.getLength() != 0)
    {
        if (mode)
            cout << "'Length = 0' failed" << endl;
        return 2;
    }
    S.Append(23);
    if (S.getLength() != 1)
    {
        if (mode)
            cout << "'Length = 1' failed" << endl;
        return 4;
    }
    if (*(S.GetFirst()) != 23)
    {
        if (mode)
            cout << "'GetFirst = 23' failed" << endl;
        return 5;
    }
    if (*(S.GetLast()) != 23)
    {
        if (mode)
            cout << "'GetLast = 23' failed" << endl;
        return 6;
    }
    if (*(S.Get(0)) != 23)
    {
        if (mode)
            cout << "'Get(0) = 23' failed" << endl;
        return 7;
    }
    if (S.Get(-1) != 0)
    {
        if (mode)
            cout << "'Get(-1)' failed" << endl;
        return 7;
    }
    if (S.Get(1) != 0)
    {
        if (mode)
            cout << "'Get(1)' failed" << endl;
        return 7;
    }
    S.Append(43);
    if (S.getLength() != 2)
    {
        if (mode)
            cout << "'Length = 2' failed" << endl;
        return 9;
    }
    if (*(S.GetFirst()) != 23)
    {
        if (mode)
            cout << "'GetFirst = 23' failed" << endl;
        return 10;
    }
    if (*(S.GetLast()) != 43)
    {
        if (mode)
            cout << "'GetLast = 43' failed" << endl;
        return 11;
    }
    if (*(S.Get(0)) != 23)
    {
        if (mode)
            cout << "'Get(0) = 23' failed" << endl;
        return 12;
    }
    if (*(S.Get(1)) != 43)
    {
        if (mode)
            cout << "'Get(1) = 43' failed" << endl;
        return 12;
    }
    if (S.Get(-1) != 0)
    {
        if (mode)
            cout << "'Get(-1)' failed" << endl;
        return 12;
    }
    if (S.Get(2) != 0)
    {
        if (mode)
            cout << "'Get(2)' failed" << endl;
        return 12;
    }
    S.Prepend(53);
    if (S.getLength() != 3)
    {
        if (mode)
            cout << "'Length = 3' failed" << endl;
        return 14;
    }
    if (*(S.GetFirst()) != 53)
    {
        if (mode)
            cout << "'GetFirst = 53' failed" << endl;
        return 15;
    }
    if (*(S.GetLast()) != 43)
    {
        if (mode)
            cout << "'GetLast = 43' failed" << endl;
        return 16;
    }
    if (*(S.Get(0)) != 53)
    {
        if (mode)
            cout << "'Get(0) = 53' failed" << endl;
        return 17;
    }
    if (*(S.Get(1)) != 23)
    {
        if (mode)
            cout << "'Get(1) = 23' failed" << endl;
        return 17;
    }
    if (*(S.Get(2)) != 43)
    {
        if (mode)
            cout << "'Get(2) = 43' failed" << endl;
        return 17;
    }
    if (S.Get(-1) != 0)
    {
        if (mode)
            cout << "'Get(-1)' failed" << endl;
        return 17;
    }
    if (S.Get(3) != 0)
    {
        if (mode)
            cout << "'Get(3)' failed" << endl;
        return 17;
    }
    T A = *(S.GetSubsequence(1, 1));
    if (A.getLength() != 1)
    {
        if (mode)
            cout << "'Length = 1' failed" << endl;
        return 181;
    }
    if (*(A.GetFirst()) != 23)
    {
        if (mode)
            cout << "'GetFirst = 23' failed" << endl;
        return 182;
    }
    if (*(A.GetLast()) != 23)
    {
        if (mode)
            cout << "'GetLast = 23' failed" << endl;
        return 182;
    }
    return 0;
}

template <typename T> int SortsTest(int mode)
{
    int Answer[7] = {-2, 0, 4, 5, 5, 67, 98};
    T S = T();
    S.Append(67);
    S.Append(4);
    S.Append(5);
    S.Append(-2);
    S.Append(5);
    S.Append(98);
    S.Append(0);
    //S.Append(-2);
    //S.Append(97);
    /*cout<<"Bubble sort Processing time in mseconds: "<<1000*/bubble(&S)/*<<endl*/;
    /*for (int j = 0; j<S.getLength();j++){
        cout<<*(S.Get(j))<<" ";
    }
    cout<<endl;*/
    for (int i = 0; i<S.getLength(); i++){
        //cout<<*(S.Get(i))<<" ";
        if (*(S.Get(i))!=Answer[i])
            return 1;
    }
    T STr = T();
    STr.Append(4);
    STr.Append(5);
    STr.Append(67);
    STr.Append(-2);
    STr.Append(5);
    STr.Append(98);
    STr.Append(0);
    /*cout<<"Tree sort Processing time in mseconds: "<<1000*/TreeSort(&STr)/*<<endl*/;
    for (int i = 0; i< STr.getLength();i++){
        if (*(STr.Get(i))!=Answer[i]){
            return 2;
        }
    }
    T SQ = T();
    SQ.Append(4);
    SQ.Append(5);
    SQ.Append(67);
    SQ.Append(-2);
    SQ.Append(5);
    SQ.Append(98);
    SQ.Append(0);
    /*cout<<"Quick sort Processing time in mseconds: "<<1000*/InitQuickSort(&SQ)/*<<endl*/;
    for (int i = 0; i< SQ.getLength();i++){
        if (*(SQ.Get(i))!=Answer[i]){
            return 3;
        }
    }
    return 0;
}


template <typename T> int SearchTest (int mode)
{
    T* A = new T;
    A->Append(-67);
    A->Append(-4);
    A->Append(5);
    A->Append(12);
    A->Append(15);
    A->Append(98);
    A->Append(100);
    if (binsearch(100, A)!= 6){
        return 1;
    }
    if (binsearch(-4, A)!= 1){
        return 2;
    }
    if (binsearch(3, A)!= -1){
        return 3;
    }
    T* S = new T;
    S->Append(67);
    S->Append(4);
    S->Append(5);
    S->Append(-2);
    S->Append(5);
    S->Append(98);
    S->Append(0);
    if (BinTreeSearch(0, S)!= 6){
        return 4;
    }
    if (BinTreeSearch(-2, S)!= 3){
        return 5;
    }
    if (BinTreeSearch(3, S)!= -1){
        return 6;
    }
    if (BTreeSearch(0, S)!= 6){
        return 7;
    }
    if (BTreeSearch(-2, S)!= 3){
        return 8;
    }
    if (BTreeSearch(3, S)!= -1){
        return 9;
    }
    S->Append(54);
    S->Append(-4);
    if (BTreeSearch(-4, S)!= 8){
        return 7;
    }
    if (BTreeSearch(-2, S)!= 3){
        return 8;
    }
    if (BTreeSearch(3, S)!= -1){
        return 9;
    }
    return 0;
}