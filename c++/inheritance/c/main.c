#include "student.h"

int main(void)
{
	HSTUDENT student = student_create("XiaoMing", 12, 99);
	student_display(student);
	person_display(student);
	student_delete(student);

	return 0;
}
