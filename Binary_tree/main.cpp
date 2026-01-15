#include "BinaryTree.hpp"

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
			BinaryTree *tree[] = { new Inorder(), new Postorder(), new Preorder() };
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
						{
							*tree[0] << value;
							*tree[1] << value;
							*tree[2] << value;
						}
					}
					else
						cout << "Invalid number!\n";
				}
				else
					return 0;
			}
			if (tree[0]->get_totalNodes())
			{
				Inorder *p = dynamic_cast<Inorder*>(tree[0]);
				if (p)
				{
					treeElement *t = (*p)[3]; // use of [] operator overload
					cout << "previous value is " << t->value << endl << "New value will be 0" << endl;
					t->value = 0;
				}
				cout << tree[0];
				cout << tree[1];
				cout << tree[2];
			}
			delete tree[0];
			delete tree[1];
			delete tree[2];
		}
		if (!iss.eof())
			cout << "Invalid number!\n";
	}
}
