#include "person.h"

int main(void)
{
	HPERSON person = person_create("XiaoMing", 12);
	person_display(person);
	person_delete(person);

	return 0;
}
