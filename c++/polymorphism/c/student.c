#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "student.h"

typedef struct
{
	char *name;
	int age;
	struct operations *ops;
} person_t;

struct operations
{
	void (*display)(const HPERSON);
};

void person_display(const HPERSON p)
{
	printf("****display person information****\n");
	printf("Name:%s\n Age:%d\n", ((person_t *)p)->name, ((person_t *)p)->age);
}
static struct operations person_ops = { person_display };


HPERSON person_create(const char *name, int age)
{
	printf("****create person****\n");
	person_t *p = (person_t *)malloc(sizeof(person_t));
	p->name = (char *)malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;
	p->ops = &person_ops;

	return p;
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

void student_display(const HSTUDENT s)
{
	printf("****display student information****\n");
	printf("Name: %s\nAge: %d\nScore: %d\n", ((person_t *)s)->name, \
		((person_t *)s)->age, ((student_t *)s)->score);
}
static struct operations student_ops = { student_display };

HSTUDENT student_create(const char *name, int age, int score)
{
	printf("****create student****\n");
	student_t *student = (student_t *)malloc(sizeof(student_t));
	student->person.name = (char *)malloc(strlen(name) + 1);
	strcpy(student->person.name, name);
	student->person.age = age;
	student->score = score;
	((person_t *)student)->ops = &student_ops;

	return student;
}

void  student_delete(HSTUDENT s)
{
	printf("delete student\n");
	free(((person_t *)s)->name);
	free(s);
}

void display(HPERSON p)
{
	((person_t *)p)->ops->display(p);
}
