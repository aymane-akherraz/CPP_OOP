#include <iostream>

using namespace std;

class ShopItemOrder
{
public:
	ShopItemOrder(string name, float price, int num_of_items = 1);
	string get_name() { return name; }
	float get_price() { return price; }
	int get_num_of_items() { return num_of_items; }
	void set_name(string name);
	void set_price(float price);
	void set_num_of_items(int num_of_items);
	float get_total_price();
	void print_order();
private:
	string name;
	float price;
	int num_of_items;
};

ShopItemOrder::ShopItemOrder(string name, float price, int num_of_items)
{
	this->name = name;
	this->price = price;
	this->num_of_items = num_of_items;
}

void ShopItemOrder::set_name(string new_name)
{
	this->name = new_name;
}

void ShopItemOrder::set_price(float new_price)
{
	if (new_price > 0)
	    this->price = new_price;
	else
		cout << "The price should be positive" << endl;
}

void ShopItemOrder::set_num_of_items(int new_num_of_items)
{
	if (new_num_of_items > 0)
	    this->num_of_items = new_num_of_items;
	else
        cout << "The number of items should be positive" << endl;
}

float ShopItemOrder::get_total_price()
{
	return this->price * this->num_of_items;
}

void ShopItemOrder::print_order()
{
	cout << this->num_of_items << " x \""
		 << this->name << "\" = "
		 << this->get_total_price() << endl;
}

int main()
{
	ShopItemOrder s("phone", 2300, 10);
	s.print_order();
}
