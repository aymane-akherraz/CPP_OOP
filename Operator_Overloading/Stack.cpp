#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

struct stackElement {
    int value;
    stackElement* prev;
};

class Stack {
	stackElement* p;
public:
	~Stack();
    Stack() : p(nullptr) {}
	void push(int value);
	Stack& operator<<(int value);
	void operator>>(int &value);
	void pop(int &value);
	int top();
	friend ostream& operator<<(ostream& os, const Stack& stack);
};

ostream& operator<<(ostream& os, const Stack& stack)
{
	stackElement *ptr = stack.p;
	os << "Stack items:" << endl;
	while (ptr)
	{
		os << ptr->value << endl;
		ptr = ptr->prev;
	}
	return os;
}

Stack::~Stack()
{
	int value;
	while (p)
		pop(value);
}

int Stack::top()
{
	if (p)
		return p->value;
	 throw runtime_error("stack is empty.");
}

void Stack::push(int value)
{
	stackElement *element = new stackElement;
	element->value = value;
	element->prev = p;
	p = element;
}

Stack& Stack::operator<<(int value)
{
	push(value);
	return *this;
}

void Stack::pop(int &value)
{
	if (p == nullptr)
        throw runtime_error("stack is empty.");
	stackElement *tmp = p->prev;
	value = p->value;
	delete p;
	p = tmp;
}

void Stack::operator>>(int &value)
{
	pop(value);
}

int main()
{
	string line;
	Stack my_stack;
	cout << "How many items should be pushed onto the stack: \n";
	if (getline(cin, line))
	{
		int size;
		istringstream iss(line);
		if (iss >> size && size >= 0)
		{
			if (size)
				cout << "Enter the items values one per line:\n";
			for (int i = 0; i < size; i++)
			{
				if (getline(cin, line))
				{
					int value;
			        istringstream iss(line);
					if (iss >> value)
						my_stack << value;
					else
						cout << "Invalid number!\n";
				}
				else
					return 0;
			}
			if (size == 0)
				return 0;
			cout << my_stack;
			cout << "How many items you want to pop from the stack:\n";
			if (getline(cin, line))
			{
				int amount;
				istringstream iss(line);
				if (iss >> amount && amount >= 0)
				{
					for (int i = 0; i < amount; i++)
					{
						int popped_value;
						my_stack >> popped_value;
						cout << popped_value << endl;
					}
				}
				else
                	cout << "Invalid number!\n";
			}
		}
		else
           	cout << "Invalid number!\n";
	}
}
