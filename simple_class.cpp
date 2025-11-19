#include <iostream>
#include <string>

using namespace std;

class Person
{
  public:
	string name;
	int	 age;
	string address;
	string major;
 	string hobbies;
};

void print(Person* person)
{
	cout << person->name << " is " << person->age << " years old and he lives in " << person->address << ", his major is " << person->major << " and he loves " << person->hobbies << '.' << endl;
}


int main()
{
	Person person;
	person.name = "Harry";
	person.age  = 23;
	person.address = "New york";
	person.major = "IT";
	person.hobbies = "reading and watching TV";

	cout << "Meet " << person.name << endl;
	print(&person);
	return 0;
}
