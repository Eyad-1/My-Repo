#include <iostream>

using namespace std;


template<typename T>
class ArrayStack
{
private:
	T* items;		// Array of stack items
	int      top;                   // Index to top of stack
	const int STACK_SIZE;

public:

	ArrayStack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	//Function getCapacity() returns the stack max size
	//added for array implementaion only
	int getCapacity()
	{
		return STACK_SIZE;
	}

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek

	//Destructor
	~ArrayStack()
	{
		delete[]items;
	}

	//Copy constructor
	ArrayStack(const ArrayStack<T>& S) :STACK_SIZE(S.STACK_SIZE)
	{
		items = new T[STACK_SIZE];
		for (int i = 0; i <= S.top; i++)
			items[i] = S.items[i];
		top = S.top;
	}

	// Prints the stack bottom up
	void printStack() const
	{
		for (int i = 0; i <= top; i++)
		{
			cout << items[i];
		}
	}

}; // end ArrayStack

template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
public:
	Node();
	Node(const T& r_Item);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
}; // end Node

template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}


template <typename T>
class LinkedQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void print() const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};

/*
Function: Queue()
The constructor of the Queue class.

*/
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

template<typename T>
void LinkedQueue<T>::print() const
{
	Node<T>* ptr = frontPtr;
	while (ptr)
	{
		cout << ptr->getItem() << " ";
		ptr = ptr->getNext();
	}
	cout << endl;
}

void ReverseEvenIndices(LinkedQueue<int>& Q) {
	//get size of Q
	int count = 0;
	LinkedQueue<int> Q1spare;
	int item1;
	while (Q.isEmpty() == false) {
		Q.dequeue(item1);
		Q1spare.enqueue(item1);
		count++;
	}
	int item2;
	while (Q1spare.isEmpty() == false) {
		Q1spare.dequeue(item2);
		Q.enqueue(item2);
	}
	int size_stack = ((count % 2 == 0) ? count / 2 : (count / 2) + 1);
	LinkedQueue<int> Q1;
	ArrayStack<int> S1(size_stack);
	int item3;
	for (int i = 0; i < count; i++) {
		if (i % 2 == 1) {
			Q.dequeue(item3);
			Q1.enqueue(item3);
		}
		else if (i % 2 == 0) {
			Q.dequeue(item3);
			S1.push(item3);
		}
	}
	int item4;
	for (int j = 0; j < count; j++) {
		if (j % 2 == 1) {
			Q1.dequeue(item4);
			Q.enqueue(item4);
		}
		else if (j % 2 == 0) {
			S1.pop(item4);
			Q.enqueue(item4);
		}
	}
}


int main()
{
	try{

		// Create the queue
		LinkedQueue<int> Q;

		// Read the queue
		int val;
		cin >> val;
		while (val != -1)
		{
			Q.enqueue(val);
			cin >> val;
		}


		/// TODO: Call your function here ============
		ReverseEvenIndices(Q);
		// Note: the required function may use stacks/queues inside it
		
		

		Q.print();


	} catch(...){
		cout<<"Exception";
	}

	return 0;
}