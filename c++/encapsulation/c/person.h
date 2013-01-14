#ifndef PERSON_H
#define PERSON_H

typedef void * HPERSON;

HPERSON person_create(const char *name, int age);
void person_display(HPERSON p);
void person_delete(HPERSON p);

#endif
