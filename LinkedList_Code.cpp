
#include <iostream>
using namespace std;

// ================== Class Node ========================

template<typename T>
class Node
{
private :
	T item;	
	Node<T>* next;	
public :

	Node( )
	{
		next= nullptr;
	} 

	Node( T newItem) 
	{
		item = newItem;
		next= nullptr;

	}

	void setItem( T newItem)
	{
		item = newItem;
	} 

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} 

	T getItem() const
	{
		return item;
	} 

	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node

// ================== Class Linked List ========================

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;

public:

	LinkedList()
	{
		Head = nullptr;
	}

	~LinkedList()
	{
		DeleteAll(); 
	}

	// Prints the linked list in the required format
	// DON'T CHANGE ANYTHING INSIDE THIS FUNCTION *********
	// BECAUSE THE AUTOMATIC JUDGE COMPARES FOR THIS FORMAT
	void PrintList()	const
	{
		Node<T> *p = Head;
		while(p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}

	// DO NOT CHANGE ANYTHING IN THIS FUNCTION *********
	void ReadList() 
	{
		int val;
		cin>>val;
		while(val != -1)
		{
			this->InsertEnd(val);
			cin>>val;
		}
	}

	// you should NOT change this function
	void InsertEnd(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		if (!Head)
		{
			Head = R;
			return;
		}
		Node<T> *p = Head;
		while (p->getNext())
			p = p->getNext();
		p->setNext(R);
	}

	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}


	//////////////////////////////////////////

	void sumOfConsecutives()
	{
		Node<T>* p1 = Head; if (!p1) return;
		Node<T>* p2 = p1->getNext(); if (!p2) return;

		Node<T>* pre = nullptr;
		Node<T>* post = nullptr;
		Node<T>* temp = nullptr;

		int first = 0;

		int rep = 0;

		while (p2)
		{
			if (!p1 || !p2) return;
			if (p1->getItem() == p2->getItem())
			{
				Node<T>* R = new Node<T>(p1->getItem() + p2->getItem());

				delete p1;
				temp = p2; p2 = p2->getNext(); delete temp;

				if (!pre) {
					p1 = R; Head = R; R->setNext(p2);
					if (!p2)
						return;
					if (p1->getItem() != p2->getItem())
						pre = R;
				}
				else {
					p1 = R; pre->setNext(R); R->setNext(p2);
					if (!p2)
						return;
					if (p1->getItem() != p2->getItem())
						pre = R;
				}
			}
			else
			{
				p1 = p1->getNext();
				p2 = p2->getNext();

				if (!p2)
					return;
				if (p1->getItem() != p2->getItem())
					pre = pre->getNext();
			}
		}
	}

	//////////////////////////////////////////


}; // end of class LinkedList


// ================== The Main Function ========================

/// TODO: This main is partially implemented, complete it to be exactly as specified in the requirements' document
int main()
{
	try{

		LinkedList<int> L;	
		L.ReadList();
		
		/// TODO: Call the Required Function Here  ==================
		L.sumOfConsecutives();
		L.PrintList();

	}catch(...){
		cout<<"Exception";
	}

	return 0;
}

