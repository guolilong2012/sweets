#include "student.h"

int main(void)
{
	Student *student = new Student("XiaoMing", 12, 99);
	student->display();

	Person *p = student;
	p->display();

	delete student;

	return 0;
}
