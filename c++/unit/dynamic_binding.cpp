#include <iostream>
using namespace std;

class Animal
{
public:
	virtual const char *saywhat(void) = 0;
};

class Cow: public Animal
{
public:
	virtual const char *saywhat(void) {return "Cow";}
};

class Dog: public Animal
{
public:
	virtual const char *saywhat(void) {return "Dog";}
};

void whosay(const char *who, Animal *a)
{
	cout << who << " say " << a->saywhat() << endl;
}

int main(void)
{
	Cow cow;
	Dog dog;

	whosay("Cow", &cow);
	whosay("Dog", &dog);
	cout << "sizeof(Animal) = " << sizeof(Animal) << endl;
	cout << "sizeof(Cow) = " << sizeof(Cow) << endl;

	return 0;
}

