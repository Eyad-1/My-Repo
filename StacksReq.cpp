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

	void printStack() const
	{
		for (int i = 0; i <= top; i++)
		{
			cout << items[i];
		}
	}

}; // end ArrayStack

void replaceGuards(ArrayStack<char>& S) {
	int size_S = 0;
	ArrayStack<char> S1spare(100);
	char x = NULL;
	while (S.isEmpty() == false) {
		S.pop(x);
		S1spare.push(x);
		size_S++;
	}
	char s = NULL;
	char* arr = new char[size_S];
	int j = 0;
	while (S1spare.isEmpty() == false) {
		S1spare.pop(s);
		arr[j] = s;
		j++;
	}
	int count_A = 0;
	for (int i = 0; i < size_S; i++) {
		if (i == 0) {
			arr[i] = 'A';
			count_A++;
		}
		else if (arr[i] == ']' && i != (size_S - 1)) {
			if (arr[i - 1] == ']' && arr[i + 1] == '[') {
				arr[i] = 'A';
				count_A++;
			}
			else if (arr[i - 1] == 'A') {
				arr[i] = 'A';
				count_A++;
			}
		}
		else if (arr[i] == '[' && i != 0) {
			if ((count_A % 2) == 0 && arr[i - 1] == 'A') {
				arr[i] = 'A';
				count_A++;
			}
		}
		else if (i == (size_S - 1)) {
			arr[i] = 'A';
		}
	}
	for (int c = 0; c < size_S; c++) {
		S.push(arr[c]);
	}
	delete[] arr;
}


int main() {
	try{
		// Declare the input stack assuming max input count is 100
		ArrayStack<char> S(100);
		
		// Read char inputs - character 'e' marks the end of the input
		char x;
		cin >> x;
		while (x != 'e') {
			S.push(x);
			cin >> x;
		}
	
		// Call replaceGuards
		replaceGuards(S);

		//Print the stack after modification
		S.printStack();
		
	} catch(...){
		cout<<"Exception";
	}
	
	return 0;
}
