
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

	/// TODO: ADD ANY REQUIRED FUNCTIONS HERE

	int countAnomalies()
	{
		if (!Head)
		{
			return 0;
		}
		else if (Head->getNext() == NULL)
			return 0;
		else
		{
			int count = 0;
			Node<T>* prev1 = Head;
			Node<T>* prev2 = NULL;
			Node<T>* ptr = NULL;
			prev2 = prev1->getNext();
			ptr = prev1->getNext()->getNext();
			while (ptr)
			{
				if (prev1->getItem() <= 0 || prev2->getItem() <= 0 || ptr->getItem() <= 0)
					return 0;
				else if (ptr->getItem() > (prev2->getItem() + prev1->getItem()))
					count++;
				prev1 = prev1->getNext();
				prev2 = ptr;
				ptr = ptr->getNext();
			}
			return count;
		}
	}

	void insertBeforePositive()
	{
		if (!Head)
		{
			return;
		}
		else 
		{
			Node<T>* ptr = Head;
			Node<T>* prev = NULL;
			while (ptr)
			{
				if (ptr->getItem() > 0 && ptr == Head)
				{
					Node<T>* nptr = new Node<T>;
					nptr->setItem(-(ptr->getItem()));
					nptr->setNext(ptr);
					Head = nptr;
				}
				else if (ptr->getItem() > 0 && ptr != Head)
				{
					Node<T>* nptr = new Node<T>;
					nptr->setItem(-(ptr->getItem()));
					nptr->setNext(ptr);
					prev->setNext(nptr);
				}
				prev = ptr;
				ptr = ptr->getNext();
			}
		}
	}

	void deleteSecondLargest()
	{
		if (!Head)
		{
			return;
		}
		else
		{
			Node<T>* prev = NULL;
			Node<T>* ptr = Head;
			int largest = -700;
			int largest2 = -900;
			while (ptr != NULL)
			{
				if (ptr->getItem() <= 0)
					return;
				else if (ptr->getItem() > largest)
				{
					largest2 = largest;
					largest = ptr->getItem();
				}
				else if (ptr->getItem() > largest2 && ptr->getItem() != largest)
					largest2 = ptr->getItem();
				ptr = ptr->getNext();
			}
			ptr = Head;
			prev = NULL;
			Node<T>* temp = ptr;
			while (ptr != NULL)
			{
				if (ptr == Head && ptr->getItem() == largest2)
				{
					temp = ptr->getNext();
					delete ptr;
					Head = temp;
					ptr = temp;
				}
				else if (ptr->getItem() == largest2 && ptr != Head)
				{
					temp = temp->getNext();
					prev->setNext(temp);
					delete ptr;
					ptr = temp;
				}
				else
				{
					prev = ptr;
					temp = temp->getNext();
					ptr = ptr->getNext();
				}
			}
		}
	}

	void reverseHalf() 
	{
		if (!Head)
		{
			return;
		}
		else
		{
			Node<T>* prev = NULL;
			Node<T>* ptr = Head;
			Node<T>* next;
			Node<T>* nextprev;
			int count = 0;
			while (ptr != NULL)
			{
				if (ptr->getItem() <= 0)
					return;
				else
				{
					ptr = ptr->getNext();
					count++;
				}
			}
			int mid = ((count % 2 == 0) ? count / 2 : (count / 2) + 1);
			int i = 1;
			prev = Head;
			if (Head != NULL)
				ptr = Head->getNext();
			while (i < mid)
			{
				next = ptr->getNext();
				nextprev = ptr;
				ptr->setNext(prev);
				if (i == mid - 1)
				{
					Head->setNext(next);
					Head = ptr;
				}
				ptr = next;
				prev = nextprev;
				i++;
			}
		}
	}


	//////////////////////////////////////////


}; // end of class LinkedList


// ================== The Main Function ========================

/// TODO: This main is partially implemented, complete it to be exactly as specified in the requirements' document
int main()
{
	try
	{

		//Don’t use any cin or cout in the code 
		// (except in [“choice” equals 1] part in the main function and must be exactly the same as required). 
		// Whenever you want to read or print linked list elements, just use:
		//-	 L.PrintList ( ) when you want to print the elements of linked list L to the user.
		//-	 L.ReadList ( ) when you want to read the elements of linked list L from the user.
		// Note: you must NOT change the implementation of these functions: L.PrintList() or L.ReadList().


		int choice;
		cin >> choice;
		if (choice == 1)
		{
			LinkedList<int> L1;
			L1.ReadList();
			int ca = L1.countAnomalies();
			std::cout << ca;
		}
		else if (choice == 2)
		{
			LinkedList<int> L1;
			L1.ReadList();
			L1.insertBeforePositive();
			L1.PrintList();
		}
		else if (choice == 3)
		{
			LinkedList<int> L1;
			L1.ReadList();
			L1.deleteSecondLargest();
			L1.PrintList();
		}
		else if (choice == 4)
		{
			LinkedList<int> L1;
			L1.ReadList();
			L1.reverseHalf();
			L1.PrintList();
		}
		else if (choice == 5)
		{
			
		}
	}
	catch (...) { cout << "Exception"; }
	// Note: Do [NOT] write system("pause") or cin >> c; or anything similar to halt execution
	return 0;
}

