#include "person.h"

int main(void)
{
	Person *person = new Person("XiaoMing", 12);
	person->display();
	delete person;

	return 0;
}
