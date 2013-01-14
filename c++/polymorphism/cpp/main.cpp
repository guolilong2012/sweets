#include "student.h"

int main(void)
{
	Student *student = new Student("XiaoMing", 12, 99);
	student->display();
	Person *p = (Person *)student;
	p->display();
	delete student;

	Person *person = new Person("XiaoHua", 11);
	person->display();
	Student *s = (Student *)person;
	s->display();
	delete person;

	return 0;
}
