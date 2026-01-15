#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_

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

class BinaryTree
{
protected:
	treeElement* root;
	size_t total_nodes;
public:
	BinaryTree();
	virtual ~BinaryTree();
	virtual void print(ostream& os) = 0;
	size_t get_totalNodes() const;
	void free_nodes(treeElement* p);
	void insert(const int& value);
	void operator<<(const int& value);
	void insert(const int& value, treeElement* p);
	treeElement* operator[](int idx);
	treeElement* get_element(int idx);
	virtual treeElement* get_node(int& idx, treeElement *p) = 0;
};

class Preorder : public BinaryTree
{
public:
	Preorder();
	~Preorder();
	void print(ostream& os) override;
	treeElement* get_node(int& idx, treeElement *p) override;
	void print_pre_order(ostream& os ,treeElement *p);
};

class Postorder : public BinaryTree
{
public:
	Postorder();
	~Postorder();
	void print(ostream& os) override;
	void print_post_order(ostream& os ,treeElement *p);
	treeElement* get_node(int& idx, treeElement *p) override;
};

class Inorder : public BinaryTree
{
public:
	Inorder();
	~Inorder();
	void print(ostream& os) override;
	void print_in_order(ostream& os ,treeElement *p);
	treeElement* get_node(int& idx, treeElement *p) override;
};

ostream& operator<<(ostream& os, BinaryTree& tree);
ostream& operator<<(ostream& os, BinaryTree* tree);

#endif
