#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "student.h"

typedef struct
{
	char *name;
	int age;
} person_t;

HPERSON person_create(const char *name, int age)
{
	printf("****create person****\n");
	person_t *p = (person_t *)malloc(sizeof(person_t));
	p->name = (char *)malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;

	return p;
}

void person_display(HPERSON p)
{
	printf("****display person information****\n");
	printf("Name:%s\n Age:%d\n", ((person_t *)p)->name, ((person_t *)p)->age);
}

void person_delete(HPERSON p)
{
	printf("****delete person****\n");
	free(((person_t *)p)->name);
	free(p);
}

typedef struct 
{
	person_t person;
	int score;
} student_t;

HSTUDENT student_create(const char *name, int age, int score)
{
	printf("****create student****\n");
	student_t *student = (student_t *)malloc(sizeof(student_t));
	student->person.name = (char *)malloc(strlen(name) + 1);
	strcpy(student->person.name, name);
	student->person.age = age;
	student->score = score;

	return student;
}

void student_display(const HSTUDENT s)
{
	printf("****display student information****\n");
	printf("Name: %s\nAge: %d\nScore: %d\n", ((person_t *)s)->name, \
		((person_t *)s)->age, ((student_t *)s)->score);
}

void  student_delete(HSTUDENT s)
{
	printf("delete student\n");
	free(((person_t *)s)->name);
	free(s);
}
