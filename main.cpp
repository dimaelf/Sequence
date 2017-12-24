#include <stdio.h>
#include <iostream>
using namespace std;

#include "ArraySequence.h"
#include "ListSequence.h"
#include "Search.cpp"
#include "Tests.cpp"

template <typename T> void menu()
{
	ListSequence <Sequence<T>*> mother = ListSequence<Sequence<T>*>();
	int ch1=1;
	int ch2;
	T item;
	while (ch1!=0)
	{
		cout << "1-create 2-add 3-Get 4-Remove 5-Sort 6-Search 0-exit" << endl;
		cin >> ch1;
		if (ch1 == 1)
		{
			cout << "1-Array 2-List" << endl;
			cin >> ch1;
            cout<<"Insert number of items"<<endl;
            cin >> ch2;
			if (ch1 == 1) {
				ArraySequence <T>* p = new ArraySequence<T>();
				mother.Append(p);
                for (int i=0; i<ch2; i++){
                    cin>>item;
                    p->Append(item);
                }
			}
			else {
				if (ch1 == 2) {
					ListSequence <T>* p = new ListSequence<T>();
					mother.Append(p);
                    for (int i=0; i<ch2; i++){
                        cin>>item;
                        p->Append(item);
                    }
				}
			}
			ch1 = 1;
		}

		if (ch1 == 2)
		{
			cout << "Insert number of sequence" << endl;
			cin >> ch1;
			ch1--;
			cout << "1-Append 2-Prepand 3-Insert" << endl;
			cin >> ch2;
			if (ch2 == 1)
			{
				cout << "Insert item" << endl;
				cin >> item;
				Sequence <T>** ptemp = mother.Get(ch1);
				if (ptemp)
				{
					(**ptemp).Append(item);
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			if (ch2 == 2)
			{
				cout << "Insert item" << endl;
				cin >> item;
				Sequence <T>** ptemp = mother.Get(ch1);
				if (ptemp)
				{
					(**ptemp).Prepend(item);
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			if (ch2 == 3) {
				cout << "Insert position" << endl;
				cin >> ch2;
				cout << "Insert item" << endl;
				cin >> item;
				Sequence <T>** ptemp = mother.Get(ch1);
				if (ptemp)
				{
					(**ptemp).InsertAt(ch2 ,item);
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			ch1 = 2;
		}

		if (ch1 == 3)
		{
			cout << "1-First 2-Last 3-Subsequence" << endl;
			cin >> ch1;
			cout << "Insert number" << endl;
			cin >> ch2;
			if (ch1 == 1)
			{
				Sequence <T>** ptemp = mother.Get(ch2-1);
				if (ptemp)
				{
					cout << *((**ptemp).GetFirst()) << endl;
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			if (ch1 == 2) {
				Sequence <T>** ptemp = mother.Get(ch2 - 1);
				if (ptemp)
				{
					cout << *((**ptemp).GetLast()) << endl;
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			if (ch1 == 3) {
				int a, b;
				cout << "Insert positions" << endl;
				cin >> a;
				cin >> b;
				a--;
				b--;
				Sequence <T>** ptemp = mother.Get(ch2 - 1);
				if (ptemp)
				{
					mother.Append((**ptemp).GetSubsequence(a, b));
				}
				else {
					cout << "Wrong number of sequence" << endl;
				}
			}
			ch1 = 3;
		}

		if (ch1 == 4)
		{
			cout << "Insert number" << endl;
			cin >> ch2;
			cout << "Insert element" << endl;
			cin >> item;
			Sequence <T>** ptemp = mother.Get(ch2 - 1);
			if (ptemp)
			{
				(**ptemp).Remove(item);
			}
			else {
				cout << "Wrong number of sequence" << endl;
			}
			ch1 = 4;
		}

		if (ch1 == 5){
			cout<<"1-Bubble 2-Tree 3-Quick 4-compare"<<endl;
			cin>>ch2;
            if (ch2!=4){
                cout<<"Set number of sequence"<<endl;
                cin>>ch1;
                if (ch2==1){
                    cout<<"Processing time in mseconds: "<<1000*bubble(*(mother.Get(ch1-1)))<<endl;
                }
                if (ch2==2){
                    cout<<"Processing time in mseconds: "<<1000*TreeSort(*(mother.Get(ch1-1)))<<endl;
                }
                if (ch2==3){
                    cout<<"Processing time in mseconds: "<<1000*InitQuickSort(*(mother.Get(ch1-1)))<<endl;
                }
            }
            else{
				ArraySequence<int>* A = new ArraySequence<int>;
                Compare(A);
				delete A;
            }
			ch1 = 5;
		}

        if (ch1 == 6){
            T x;
            cout<<"Set element to search"<<endl;
            cin>>x;
            cout<<"1-Binary 2-Binary Tree 3-B-Tree"<<endl;
            cin>>ch1;
            cout<<"Set number of sequence"<<endl;
            cin>>ch2;
            if (ch1 == 1){
                int res = binsearch(x, *(mother.Get(ch2-1)));
                if (res!=-1){
                    cout<<"Index of element = "<<res<<endl;
                }
                else{
                    cout<<"Not found"<<endl;
                }
            }
            if (ch1 == 2){
                int res = BinTreeSearch(x, *(mother.Get(ch2-1)));
                if (res!=-1){
                    cout<<"Index of element = "<<res<<endl;
                }
                else{
                    cout<<"Not found"<<endl;
                }
            }
            if (ch1==3){
                int res = BTreeSearch(x, *(mother.Get(ch2-1)));
                if (res!=-1){
                    cout<<"Index of element = "<<res<<endl;
                }
                else{
                    cout<<"Not found"<<endl;
                }
            }
        }

		for (int i = 0; i < mother.getLength(); i++)
		{
			cout << i+1 << ":";
			for (int j = 0; j < (*(mother.Get(i)))->getLength(); j++)
			{
				cout << *((*(mother.Get(i)))->Get(j))<< " ";
			}
			cout << endl;
		}
	}
}

int main()
{
	int type;
	cout << "To test?(0/1)" << endl;
	cin >> type;
    //type = 1;
	if (type == 1) {
        int result1 = BasicTest<ListSequence<float>>(1);
        int result2 = BasicTest<ArraySequence<long>>(1);
        if (result1+result2 == 0) {
            cout << "Success!!" << endl;
        }
        else {
            if (result1) {
                cout << "Error for List int ";
                cout << result1 << endl;
            }
            if (result2) {
                cout << "Error for Array float ";
                cout << result2 << endl;
            }
        }
        result1 = SortsTest<ArraySequence<char>>(1);
        result2 = SortsTest<ListSequence<float>>(1);
        if (result1+result2 == 0) {
            cout << "Success!!" << endl;
        }
        else {
            if (result1) {
                cout << "Error for Array char soting ";
                cout << result1 << endl;
            }
            if (result2) {
                cout << "Error for List float sorting ";
                cout << result2 << endl;
            }
        }
        result1 = SearchTest<ArraySequence<int>>(1);
        result2 = SearchTest<ListSequence<int>>(1);
        if (result1+result2 == 0) {
            cout << "Success!!" << endl;
        }
        else {
            if (result1) {
                cout << "Error for Array int search ";
                cout << result1 << endl;
            }
            if (result2) {
                cout << "Error for List int search ";
                cout << result2 << endl;
            }
        }
        /*ListSequence<int> *S = new ListSequence<int>;
        for (int i = 0; i < 15; i++){
            int in;
            cin>>in;
            S->Append(in);
        }
        for (int i = 0; i < 15; i++){
            cout << *(S->Get(i))<<" ";
        }
        cout<<endl;
        //int in;
        //cin>>in;
        //cout<<"Неy->"<<binsearch(1, S)<<endl;*/
		return 0;
	}
	cout << "Choose type of data(1-int, 2-float)" << endl;
	cin >> type;
	if (type == 2)
	{
		menu<float>();
	}
	else
		menu<int>();
	return 0;
}
