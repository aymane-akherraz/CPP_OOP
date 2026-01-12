#include <iostream>

using namespace std;

class Tree
{
public:
	virtual void draw();
	virtual ~Tree();
};

void Tree::draw()
{

}

Tree::~Tree()
{

}

class SimpleTree : public Tree
{
public:
	void draw();
};

void SimpleTree::draw()
{
	cout << " /\\\n";
	cout << "//\\\\\n";
}

class StarTree : public Tree
{
public:
    void draw();
};

void StarTree::draw()
{
	cout << " / \\\n";
	cout << "/**\\\n";
}

class PlusTree : public Tree
{
public:
    void draw();
};

void PlusTree::draw()
{
    cout << " / \\\n";
    cout << "/++\\\n";
}

int main()
{
	SimpleTree slash;
	StarTree star;
	PlusTree plus;
	Tree *trees[3] = {&slash, &star, &plus};
	for (int i = 0; i < 3; i++)
	{
		cout << "Drawing " << i + 1 << ":\n";
		trees[i]->draw();
	}
}
