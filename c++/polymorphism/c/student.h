#ifndef STUDENT_H
#define STUDENT_H

typedef void * HPERSON;

HPERSON person_create(const char *name, int age);
//void person_display(HPERSON p);
void person_delete(HPERSON p);


typedef void * HSTUDENT;

HSTUDENT student_create(const char *name, int age, int score);
//void student_display(const HSTUDENT s);
void student_delete(HSTUDENT s);

void display(HPERSON);

#endif
