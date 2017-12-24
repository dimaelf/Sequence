#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include "ArraySequence.h"
#include "ListSequence.h"

using namespace std;

template <typename T> double bubble (Sequence<T>* S)
{
    double time0, time1;
    time0 = omp_get_wtime();
    for (int i = S->getLength() - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (*(S->Get(j)) > *(S->Get(j+1)))
            {
                S->Swap(j, j+1);
            }
            //for (int j = 0; j<S->getLength();j++){
              //  cout<<*(S->Get(j))<<" ";
            //}
            //cout<<endl;
        }
    }
    time1 = omp_get_wtime();
    return time1-time0;
}

template <typename T> struct node{
    T element;
    node* left;
    node* right;
};

template <typename T> void DesTree(node<T>* root){
    if (root == 0){
        return;
    }
    DesTree(root->right);
    DesTree(root->left);
    delete root;
}

template <typename T> void TreeWrightBack(node<T>* nod, Sequence<T>* S){
    if (nod != 0){
        TreeWrightBack(nod->left, S);
        S->Append(nod->element);
        TreeWrightBack(nod->right, S);
    }
}

template <typename T> double TreeSort(Sequence<T>* S)
{
    double time0, time1;
    time0 = omp_get_wtime();
    int length = S->getLength();
    node<T>* root = 0;
    node<T>* pCurrent;
    for (int i = 0; i<length; i++){
        if (root == 0)
        {
            root = new node<T>;
            root->element = *(S->GetFirst());
            root->left = 0;
            root->right = 0;
        }
        else{
            T el = *(S->GetFirst());
            pCurrent = root;
            while (pCurrent != nullptr){
                if (el < pCurrent->element){
                    if (pCurrent->left==0){
                        pCurrent->left = new node<T>;
                        pCurrent = pCurrent->left;
                        pCurrent->element = el;
                        pCurrent->right = 0;
                        pCurrent->left = 0;
                        pCurrent = 0;
                    }
                    else {
                        pCurrent = pCurrent->left;
                    }
                }
                else {
                    if (pCurrent->right==0){
                        pCurrent->right = new node<T>;
                        pCurrent = pCurrent->right;
                        pCurrent->element = el;
                        pCurrent->right = 0;
                        pCurrent->left = 0;
                        pCurrent = 0;
                    }
                    else {
                        pCurrent = pCurrent->right;
                    }
                }
            }
        }
        S->RemoveFrom(0);
    }
    TreeWrightBack(root, S);
    time1 = omp_get_wtime();
    DesTree(root);
    return time1-time0;
}

template <typename T> void QuickSort(Sequence<T>* S, int start, int end){
    if (start<end) {
        int pivot = *(S->Get(start));
        int is = start;
        for (int i = start+1; i<end; i++){
            if (*(S->Get(i))< pivot){
                is++;
                S->Swap(is, i);
            }
        }
        S->Swap(start, is);
        QuickSort(S, start, is);
        QuickSort(S, is+1, end);
    }
}

template <typename T> double InitQuickSort(Sequence<T>* S)
{
    double time0, time1;
    time0 = omp_get_wtime();
    if (S->getLength()< 2){
        time1 = omp_get_wtime();
        return time1-time0;
    }
    /*int SeparIndex = Separating(S, 0, S->getLength()-1);
    //omp_set_num_threads(2);
    /*#pragma omp parallel
    {
        if (omp_get_thread_num() == 1) {
            QuickSort(S, SeparIndex + 1, S->getLength() - 1);
        }
        if (omp_get_thread_num() == 0) {
            QuickSort(S, 0, SeparIndex);
        }
    }*/
    QuickSort(S, 0, S->getLength());
    //QuickSort(S,SeparIndex+1, S->getLength()-1);
    time1 = omp_get_wtime();
    return time1-time0;
}

template <typename T> void transfer(Sequence <T>* ptemp, ArraySequence<T>* pconst)
{
    for (int i = 0; i<pconst->getLength(); i++){
        ptemp->RemoveFrom(0);
    }
    for (int i = 0; i<pconst->getLength(); i++){
        (ptemp)->Append(*(pconst->Get(i)));
    }
    /*for (int i = 0; i<(*ptemp)->getLength(); i++){
        cout<<*((*ptemp)->Get(i))<<" ";
    }
    cout<<endl;*/
}

template <typename T> void Compare(Sequence<T>* A)
{
    ArraySequence<T>* pconst = new ArraySequence<T>;
    int n = 10000;
    for (int i = 0; i<n; i++){
        pconst->Append(n-i);
    }
    ArraySequence<T>* ptempA = new ArraySequence<T>;
    transfer(ptempA, pconst);
    cout<<"Bubble sort for Array processing time in seconds: "<<bubble(ptempA)<<endl;
    transfer(ptempA, pconst);
    cout<<"Tree sort for Array processing time in mseconds: "<<TreeSort(ptempA)<<endl;
    transfer(ptempA, pconst);
    cout<<"Quick sort for Array processing time in mseconds: "<<InitQuickSort(ptempA)<<endl;
    delete ptempA;

    /*ListSequence<T>* ptempL = new ListSequence<T>;
    transfer(ptempL, pconst);
    cout<<"Bubble sort for List processing time in seconds: "<<bubble(ptempL)<<endl;
    transfer(ptempL, pconst);
    cout<<"Tree sort for List processing time in mseconds: "<<TreeSort(ptempL)<<endl;
    transfer(ptempL, pconst);
    cout<<"Quick sort for List processing time in mseconds: "<<InitQuickSort(ptempL)<<endl;
    transfer(ptempL, pconst);
    delete ptempL;*/
    delete pconst;
}
