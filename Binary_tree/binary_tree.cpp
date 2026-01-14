#include <iostream>
#include <sstream>

using namespace std;

class treeElement
{
public:
	int value;
	treeElement *left;
	treeElement *right;
	treeElement(int value);
};

treeElement::treeElement(int value)
		: value(value), left(nullptr), right(nullptr) {}

class BinaryTree
{
	treeElement* root;
public:
	BinaryTree();
	void print(ostream& os);
	void insert(const int& value);
	void operator<<(const int& value);
	void insert(const int& value, treeElement* p);
	void print_in_order(ostream& os ,treeElement *p);
};

BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::operator<<(const int& value)
{
	insert(value);
}

void BinaryTree::insert(const int& value, treeElement* p)
{
	if (value < p->value)
	{
		if (p->left)
			insert(value, p->left);
		else
			p->left = new treeElement(value);
	}
	else
	{
		if (p->right)
            insert(value, p->right);
        else
            p->right = new treeElement(value);
	}
}

void BinaryTree::insert(const int& value)
{
	if (root == nullptr)
		root = new treeElement(value);
	else
		insert(value, root);
}

void BinaryTree::print_in_order(ostream& os ,treeElement *p)
{
	if (p->left)
		print_in_order(os, p->left);
	os << p->value << endl;
	if (p->right)
		print_in_order(os, p->right);
}

void BinaryTree::print(ostream& os)
{
	if (root)
		print_in_order(os, root);
}

ostream& operator<<(ostream& os, BinaryTree& tree)
{
	tree.print(os);
	return os;
}

int main(void) {
	int value;
	string line;
	BinaryTree tree;
	cout << "Enter tree values one per line:\n";
	for (int i = 0; i < 3; i++)
	{
		if (getline(cin, line))
		{
			istringstream iss(line);
			if (iss >> value)
				tree << value;
			else
				cout << "Invalid number!\n";
		}
	}
	cout << tree;
}
