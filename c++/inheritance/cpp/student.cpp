#include <iostream>
#include <cstring>

#include "student.h"

using namespace std;

Person::Person(const char *name, int age)
	:name(NULL), age(age)
{
	cout << "****create person****" << endl;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Person::display() const
{
	cout << "****display person information****" << endl
		<< "Name: " << name << endl << "Age: " << age << endl;
}

Person::~Person()
{
	cout << "****delete person****" << endl;
	delete[] name;
}

Student::Student(const char *name, int age, int score)
	:Person(name, age), score(score)
{
	cout << "****create student****" << endl;
}

void Student::display() const
{
	cout << "****display student information****" << endl \
		<< "Name: " << name << endl << "Age: " << age << endl \
		<< "Score: " << score << endl;
}

Student::~Student()
{
	cout << "****delete student****" << endl;
}
