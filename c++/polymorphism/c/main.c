#include "student.h"

int main(void)
{
	HSTUDENT student = student_create("XiaoMing", 12, 99);
	display(student);
	HPERSON p = (HPERSON)student;
	display(p);
	student_delete(student);

	HPERSON person = person_create("XiaoHua", 11);
	display(person);
	HSTUDENT s = (HSTUDENT)person;
	display(s);
	person_delete(person);

	return 0;
}
