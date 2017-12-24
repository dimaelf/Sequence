#include <iostream>
//#include "ArraySequence.h"
#include "Sort.cpp"
#include "ListSequence.h"

using namespace std;



template <typename T> int binsearch(T x, Sequence<T>* S)
{
    int start, mid, end;
    start = 0;
    end = S->getLength() - 1;
    while (1){
        if (start > end){
            return -1;
        }
        mid = (start+end)/2;
        if (x == *(S->Get(mid))){
            return mid;
        }
        if (x < *(S->Get(mid))){
            end = mid-1;
        }
        else {
            start = mid+1;
        }
    }
    return -1;
}


template <typename T> struct NodNum{
    T element;
    NodNum* left;
    NodNum* right;
    int num;
};

template <typename T> NodNum<T>* CreateBinTree(Sequence<T>* S)
{
    int length = S->getLength();
    NodNum<T>* root = 0;
    NodNum<T>* pCurrent;
    for (int i = 0; i<length; i++){
        if (root == 0)
        {
            root = new NodNum<T>;
            root->element = *(S->Get(i));
            root->left = 0;
            root->right = 0;
            root->num = i;
        }
        else{
            T el = *(S->Get(i));
            pCurrent = root;
            while (pCurrent != nullptr){
                if (el < pCurrent->element){
                    if (pCurrent->left==0){
                        pCurrent->left = new NodNum<T>;
                        pCurrent = pCurrent->left;
                        pCurrent->element = el;
                        pCurrent->right = 0;
                        pCurrent->left = 0;
                        pCurrent->num = i;
                        pCurrent = 0;
                    }
                    else {
                        pCurrent = pCurrent->left;
                    }
                }
                else {
                    if (pCurrent->right==0){
                        pCurrent->right = new NodNum<T>;
                        pCurrent = pCurrent->right;
                        pCurrent->element = el;
                        pCurrent->right = 0;
                        pCurrent->left = 0;
                        pCurrent->num = i;
                        pCurrent = 0;
                    }
                    else {
                        pCurrent = pCurrent->right;
                    }
                }
            }
        }
    }
    return root;
}

template <typename T> void DesBinTree(NodNum<T>* root){
    if (root == 0){
        return;
    }
    DesBinTree(root->right);
    DesBinTree(root->left);
    delete root;
}

template <typename T> int BinTreeSearch(T el, Sequence<T>* S)
{
    NodNum<T>* root = CreateBinTree(S);
    NodNum<T>* pCurrent = root;
    while (pCurrent != 0){
        if (pCurrent->element == el){
            int ans = pCurrent->num;
            DesBinTree(root);
            return ans;
        }
        if (pCurrent->element > el){
            //cout<<"left"<<endl;
            pCurrent = pCurrent->left;

        }
        else{
            if (pCurrent->element<el){
               //cout<<"right"<<endl;
                pCurrent = pCurrent->right;

            }
        }
        if (pCurrent == 0){
            DesBinTree(root);
            return -1;
        }
    }
    DesBinTree(root);
    return -1;
}


template <typename T> struct ElemNum
{
    T element;
    int num;
};

template <typename T> struct Bleaf;

template <typename T> struct BRoot
{
    ElemNum<T>* pElements;
    int NumElements;
    Bleaf<T>* children;
    int NumChildren;
};

template <typename T> struct Bleaf{
    ElemNum<T>* pElements;
    int NumElements;
    BRoot<T>* parent;
};

template <typename T> void DesBTree(BRoot<T>* root){
    for (int i = 0; i<root->NumChildren; i++){
        free((root->children+i)->pElements);
    }
    free(root->children);
    free(root->pElements);
    delete root;
}

template <typename T> BRoot<T>* CreateBTree(Sequence<T> *S)
{
    ElemNum<T>* seq = (ElemNum<T>*)malloc(S->getLength()* sizeof(ElemNum<T>));
    ListSequence<T> A;
    for (int i = 0; i<S->getLength();i++){

        A.Append(*(S->Get(i)));
    }
    bubble(&A);
    /*for (int i = 0; i<A.getLength();i++){

        cout<<*(A.Get(i))<<" ";
    }
    cout<<endl;*/
    for (int i = 0; i<S->getLength(); i++){
        (seq+i)->element = *(S->Get(i));
        (seq+i)->num = i;
    }
    for (int i = S->getLength() - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if ((seq+j)->element > (seq+j+1)->element)
            {
                int tnum;
                T Tel;
                tnum = (seq+j)->num;
                (seq+j)->num = (seq+j+1)->num;
                (seq+j+1)->num = tnum;
                Tel = (seq+j)->element;
                (seq+j)->element = (seq+j+1)->element;
                (seq+j+1)->element = Tel;
            }
        }
    }
    /*for (int i = 0; i<S->getLength(); i++){
        cout<<(seq+i)->element<<" - "<<(seq+i)->num<<" ";
    }
    cout<<endl;*/
    auto tpr = 4;
    int parts = S->getLength()/tpr;
    int res = S->getLength()%tpr;
    BRoot<T>* root = new BRoot<T>;

    if (parts == 0){
        root->NumChildren = 0;
        root->children = 0;
        root->NumElements = S->getLength();
        root->pElements = (ElemNum<T>*)malloc(S->getLength()*sizeof(ElemNum<T>));
        root->pElements = seq;
        /*for (int i = 0; i<root->NumElements; i++){
            cout<<(root->pElements+i)->element<<" - "<<(root->pElements+i)->num<<" ";
        }
        cout<<endl;*/
    }
    else{
        parts++;
        root->NumChildren = parts;
        root->children = (Bleaf<T>*)malloc(parts*sizeof(Bleaf<T>));
        root->NumElements = parts - 1;
        root->pElements = (ElemNum<T>*)malloc((parts-1)*sizeof(ElemNum<T>));
        for (int i = 0; i < parts-2; i++){
            (root->pElements+i)->element = (seq+tpr*(i+1)-1)->element;
            //cout<< (root->pElements+i)->element<<" ";
            (root->pElements+i)->num = (seq+tpr*(i+1)-1)->num;
        }
        if (res==1){
            (root->pElements+parts-2)->element = (seq+tpr*(parts-1)-2)->element;
            //cout<< (root->pElements+parts-2)->element<<" ";
            //cout<<endl;
            (root->pElements+parts-2)->num = (seq+tpr*(parts-1)-2)->num;
            for (int i = 0; i<root->NumChildren-2; i++){
                (root->children+i)->NumElements = tpr-1;
                (root->children+i)->pElements =  (ElemNum<T>*)malloc((tpr-1)* sizeof(ElemNum<T>));
                for (int j = 0; j<tpr-1; j++){
                    *((root->children+i)->pElements+j) = *(seq+tpr*i+j);
                    //cout<<((root->children+i)->pElements+j)->element<<' ';
                }
            }
           //cout<<endl;
            (root->children+root->NumChildren-2)->NumElements = tpr-2;
            (root->children+root->NumChildren-2)->pElements =  (ElemNum<T>*)malloc((tpr-1)* sizeof(ElemNum<T>));
            for(int j = 0; j<tpr-2;j++){
                *((root->children+root->NumChildren-2)->pElements+j) = *(seq+tpr*(root->NumChildren-2)+j);
                //cout<<((root->children+root->NumChildren-2)->pElements+j)->element<<' ';
            }
            //cout<<endl;
            (root->children+root->NumChildren-1)->NumElements = 2;
            (root->children+root->NumChildren-1)->pElements =  (ElemNum<T>*)malloc((tpr-1)* sizeof(ElemNum<T>));
            for (int j = 0; j<2; j++){
                *((root->children+root->NumChildren-1)->pElements+j) = *(seq+tpr*(root->NumChildren-1)+j-1);
                //cout<<((root->children+root->NumChildren-1)->pElements+j)->element<<' ';
            }
            //cout<<endl;
        }
        else{
            (root->pElements+parts-2)->element = (seq+tpr*(parts-1)-1)->element;
            //cout<< (root->pElements+parts-2)->element<<endl;
            (root->pElements+parts-2)->num = (seq+tpr*(parts-1)-1)->num;
            for (int i = 0; i<root->NumChildren-1; i++){
                (root->children+i)->NumElements = tpr-1;
                (root->children+i)->pElements =  (ElemNum<T>*)malloc((tpr-1)* sizeof(ElemNum<T>));
                for (int j = 0; j<tpr-1; j++){
                    *((root->children+i)->pElements+j) = *(seq+tpr*i+j);
                    //cout<<((root->children+i)->pElements+j)->element<<' ';
                }
                //cout<<endl;
            }
            (root->children+root->NumChildren-1)->NumElements = tpr-1;
            (root->children+root->NumChildren-1)->pElements =  (ElemNum<T>*)malloc((tpr-1)* sizeof(ElemNum<T>));
            if (res == 0){
                res = 4;
            }
            for (int j = 0; j<res; j++){
                *((root->children+root->NumChildren-1)->pElements+j) = *(seq+tpr*(root->NumChildren-1)+j);
                //cout<<((root->children+root->NumChildren-1)->pElements+j)->element<<' ';
            }
            //cout<<endl;
        }
    }
    return root;
}

template <typename T> int BTreeSearch(T el, Sequence<T>* S){
    BRoot<T>* root = CreateBTree(S);
    int i = 0;
    while ((el>(root->pElements+i)->element)&&(i!= root->NumElements-1)){
        i++;
    }
    if (el == (root->pElements+i)->element){
        int ans = (root->pElements+i)->num;
        DesBTree(root);
        return ans;
    }
    Bleaf<T>* pCurrent;
    if (el<(root->pElements+i)->element){
        pCurrent = (root->children+i);
    }
    else{
        pCurrent = (root->children+i+1);
    }
    int j = 0;
    while ((el!=(pCurrent->pElements+j)->element)&&(j!= pCurrent->NumElements-1)){
        j++;
    }
    if (el==(pCurrent->pElements+j)->element){
        int ans = (pCurrent->pElements+j)->num;
        DesBTree(root);
        return ans;
    }
    //DesBTree(root);
    return -1;
}
