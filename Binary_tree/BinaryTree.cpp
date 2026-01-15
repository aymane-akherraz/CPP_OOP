#include "BinaryTree.hpp"

treeElement::treeElement(int value)
		: value(value), left(nullptr), right(nullptr) {}

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

treeElement* BinaryTree::get_element(int idx)
{
	if (idx < 0 || idx >= (int)total_nodes)
	{
	    cout << "Invalid index!\n";
		return nullptr; 
	}
	return get_node(idx, root);
}

treeElement* BinaryTree::operator[](int idx)
{
	if (root)
		return get_element(idx);
	return nullptr;
}

Preorder::Preorder() : BinaryTree() {}

Preorder::~Preorder() {}

treeElement* Preorder::get_node(int& idx, treeElement *p)
{
	if (!p)
        return nullptr;
	if (idx-- == 0)
        return p;
    treeElement* found = get_node(idx, p->left);
    if (found)
        return found;
    return get_node(idx, p->right);
}

void Preorder::print_pre_order(ostream& os ,treeElement *p)
{
	os << p->value << endl;
	if (p->left)
		print_pre_order(os, p->left);
	if (p->right)
		print_pre_order(os, p->right);
}

void Preorder::print(ostream& os)
{
	os << "Preorder:\n";
	if (root)
		print_pre_order(os, root);
}

Postorder::Postorder() : BinaryTree() {}

Postorder::~Postorder() {}

void Postorder::print_post_order(ostream& os ,treeElement *p)
{
	if (p->left)
		print_post_order(os, p->left);
	if (p->right)
		print_post_order(os, p->right);
	os << p->value << endl;
}

void Postorder::print(ostream& os)
{
	os << "Postorder:\n";
	if (root)
		print_post_order(os, root);
}

treeElement* Postorder::get_node(int& idx, treeElement *p)
{
	if (!p)
        return nullptr;
    treeElement* left = get_node(idx, p->left);
    if (left)
        return left;
    treeElement* right = get_node(idx, p->right);
	if (right)
			return right;
	if (idx-- == 0)
        return p;
	return nullptr;
}

Inorder::Inorder() : BinaryTree() {}

Inorder::~Inorder() {}


treeElement* Inorder::get_node(int& idx, treeElement *p)
{
	if (!p)
        return nullptr;
    treeElement* found = get_node(idx, p->left);
    if (found) {
        return found;
	}
	if (idx-- == 0) {
        return p;
	}
    return get_node(idx, p->right);
}

void Inorder::print_in_order(ostream& os ,treeElement *p)
{
	if (p->left)
		print_in_order(os, p->left);
	os << p->value << endl;
	if (p->right)
		print_in_order(os, p->right);
}

void Inorder::print(ostream& os)
{
	os << "Inorder:\n";
	if (root)
		print_in_order(os, root);
}

ostream& operator<<(ostream& os, BinaryTree& tree)
{
	tree.print(os);
	return os;
}

ostream& operator<<(ostream& os, BinaryTree* tree)
{
	tree->print(os);
	return os;
}
