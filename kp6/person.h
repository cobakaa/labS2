#ifndef __person_h__
#define __person_h__

#include <wchar.h>

#define MAX_S_NAME 20
#define INIT_COUNT 6
#define GROUP_NAME_SIZE 9
#define MARKS_COUNT 15

typedef struct
{
	wchar_t second_name[MAX_S_NAME];
	wchar_t initials[INIT_COUNT];
	wchar_t gender;
	wchar_t group[GROUP_NAME_SIZE];
	int marks[MARKS_COUNT];
	int subjects_num;
} Person;

#endif