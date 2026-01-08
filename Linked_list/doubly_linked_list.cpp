#include <iostream>
 
using namespace std;

class Node
{
public:
	Node(int val);
	~Node();
	int value;
	int index;
	Node *next;
	Node *prev;
};

Node::Node(int val) : value(val), prev(nullptr), next(nullptr)
{
	cout << "+Node" << endl;
}

Node::~Node()
{
	cout << "-Node" << endl;
}

class List
{
public:
	List();
	~List();
	size_t size();
	Node* at(int idx);
	List(const List &src);
	List& operator=(const List &src);
	void push_front(int value);
	void push_back(int value);
	bool pop_front(int &value);
	bool pop_back(int &value);
	void insert_at(int idx, int value);
	void remove_at(int idx);
private:
	Node *head;
	Node *tail;
	size_t list_size;
};

List::List() : head(nullptr), tail(nullptr), list_size(0) {}

List::~List()
{
	Node *tmp;
	while (head)
	{
		tmp = head->next;
		delete head;
		head = tmp;
	}
	head = nullptr;
	tail = nullptr;
	list_size = 0;
}

List::List(const List &src)
{
	if (src.head)
	{
		Node *ptr = src.head;
		head = new Node(ptr->value);
		head->index = ptr->index;
		if (src.list_size == 1)
			tail = head;
		Node *tmp = head;
		ptr = ptr->next;
		while (ptr)
		{
			tmp->next = new Node(ptr->value);
			tmp->next->index = ptr->index;
			tmp->next->prev = tmp;
			if (ptr->next == nullptr)
				tail = tmp->next;
			tmp = tmp->next;
			ptr = ptr->next;
		}
	}
	else
	{
		head = nullptr;
		tail = nullptr;
	}
	list_size = src.list_size;
}

List& List::operator=(const List &src)
{
	if (this != &src)
	{
		Node *tmp;
		while (head)
		{
			tmp = head->next;
			delete head;
			head = tmp;
		}
		head = nullptr;
		tail = nullptr;
		list_size = 0;
		Node *ptr = src.head;
		while (ptr)
		{
			this->push_back(ptr->value);
			ptr = ptr->next;
		}
	}
	return *this;
}

Node*  List::at(int idx)
{
	if (idx >= 0 && idx < (int)list_size)
	{
		if (idx == (list_size - 1))
			return tail;
		else if (idx == (list_size - 2))
			return tail->prev;
		Node* ptr = head;
		while (ptr)
		{
			if (ptr->index == idx)
				return ptr;
			ptr = ptr->next;
		}
	}
	return nullptr;
}

void List::push_back(int value)
{
	if (tail)
	{
		tail->next = new Node(value);
		tail->next->prev = tail;
		tail = tail->next;
		tail->index = list_size;
	}
	else
	{
		head = new Node(value);
		tail = head;
		tail->index = 0;
	}
	list_size++;
}

bool List::pop_back(int &value)
{
	if (!head)
		return false;
	value = tail->value;
	if (head == tail)
	{
		delete head;
		tail = nullptr;
		head = nullptr;
	}
	else
	{
		Node *new_tail = tail->prev;
		delete tail;
		tail = new_tail;
		tail->next = nullptr;
	}
	list_size--;
	return true;
}

void List::push_front(int value)
{
	Node* new_head = new Node(value);
	new_head->next = head;
	if (head == nullptr)
		tail = new_head;
	else
		head->prev = new_head;
	head = new_head;
	head->index = 0;
	Node *ptr = head->next;
	while (ptr)
	{
		ptr->index++;
		ptr = ptr->next;
	}
	list_size++;
}

bool List::pop_front(int &value)
{
	Node *tmp = head;
	if (head)
	{
		head = head->next;
		head->prev = nullptr;
	}
	else
		return false;
	value = tmp->value;
	delete tmp;
	list_size--;
	if (list_size == 0)
	{
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node *ptr = head;
		while (ptr)
		{
			ptr->index--;
			ptr = ptr->next;
		}
	}
	return true;
}

void List::insert_at(int idx, int value)
{
	if (idx < 0 || idx > (int)list_size)
		return ;
	else if (idx == 0)
		push_front(value);
	else if (idx == list_size)
		push_back(value);
	else
	{
		Node *new_node = new Node(value);
		Node *tmp = at(idx);
		tmp->prev->next = new_node;
		new_node->prev = tmp->prev;
		new_node->next = tmp;
		tmp->prev = new_node;
		new_node->index = idx;
		Node *ptr = new_node->next;
		while (ptr)
        {
            ptr->index++;
            ptr = ptr->next;
        }
		list_size++;
	}
}

void List::remove_at(int idx)
{
	int value;
	if (idx < 0 || idx >= (int)list_size)
		return ;
	else if (idx == 0)
		pop_front(value);
	else if (idx == (list_size - 1))
		pop_back(value);
	else
	{
		Node *tmp = at(idx);
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		Node *ptr = tmp->next;
		delete tmp;
		while (ptr)
		{
			ptr->index--;
			ptr = ptr->next;
		}
		list_size--;
	}
}

size_t List::size()
{
	return list_size;
}

void printList(List &list)
{
	size_t size = list.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << "list[" << i << "] == " << list.at(i)->value << endl;
	}
}

int main()
{
	List list1;
	list1.push_front(1);
	list1.push_front(2);
	list1.push_front(3);
	list1.push_front(4);
	cout << "list1" << endl;
	printList(list1);
	cout << endl;

	List list2(list1);
	cout << "list2" << endl;
	printList(list2);
	cout << endl;

	list1.insert_at(1, 6);
	list2.remove_at(2);

	cout << "list1" << endl;
	printList(list1);
	cout << "list2" << endl;
	printList(list2);
	cout << endl;
	return 0;
}
