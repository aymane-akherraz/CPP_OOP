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
	size_t total_nodes;
public:
	BinaryTree();
	~BinaryTree();
	void print(ostream& os);
	size_t get_totalNodes() const;
	void free_nodes(treeElement* p);
	void insert(const int& value);
	void operator<<(const int& value);
	void insert(const int& value, treeElement* p);
	void print_in_order(ostream& os ,treeElement *p);
};

BinaryTree::BinaryTree() : root(nullptr), total_nodes(0) {}

void BinaryTree::free_nodes(treeElement* p)
{
	if (p->left)
		free_nodes(p->left);
	if (p->right)
        free_nodes(p->right);
	delete p;
}

BinaryTree::~BinaryTree()
{
	if (root)
		free_nodes(root);
}

size_t BinaryTree::get_totalNodes() const
{
	return total_nodes;
}


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
	total_nodes++;
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
	os << "Tree nodes in ascending order:\n";
	tree.print(os);
	return os;
}

int main(void) {
	int value;
	string line;
	int total_nodes;
	cout << "How many nodes do you want in the tree:\n";
	if (getline(cin, line))
    {
		istringstream iss(line);
		if (iss >> total_nodes && total_nodes > 0)
		{
			iss >> ws;
			if (!iss.eof())
			{
				cout << "Invalid number!\n";
				return 1;
			}
			BinaryTree tree;
			cout << "Enter nodes values one per line:\n";
			for (int i = 0; i < total_nodes; i++)
			{
				if (getline(cin, line))
				{
					istringstream iss(line);
					if (iss >> value)
					{
						iss >> ws;
						if (!iss.eof())
							cout << "Invalid number!\n";
						else
							tree << value;
					}
					else
						cout << "Invalid number!\n";
				}
				else
					return 0;
			}
			if (tree.get_totalNodes())
				cout << tree;
		}
		if (!iss.eof())
			cout << "Invalid number!\n";
	}
}
