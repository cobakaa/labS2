#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>
#include "person.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

void usage() {
	printf("Usage: <-f> -p studentsCount inputFile\n");
}

void print_head() {
		wchar_t c1[] = L"Фамилия";
		wchar_t c2[] = L"Инициалы";
		wchar_t c3[] = L"Пол";
		wchar_t c4[] = L"Группа";
		wchar_t c5[] = L"Оценки";
		printf(" ┏");
		for (int i = 0; i < 15; i++) printf("━");
		printf("┯");
		for (int i = 0; i < 8; i++) printf("━");
		printf("┯");
		for (int i = 0; i < 3; i++) printf("━");
		printf("┯");
		for (int i = 0; i < 8; i++) printf("━");
		printf("┯");
		for (int i = 0; i < 29; i++) printf("━");
		printf("┓\n");
		printf(" ┃");
		printf("%-*ls", (int)(15 + wcslen(c1)), c1);
		printf("│");
		printf("%-*ls", (int)(8 + wcslen(c2)), c2);
		printf("│");
		printf("%-*ls", (int)(3 + wcslen(c3)), c3);
		printf("│");
		printf("%-*ls", (int)(8 + wcslen(c4)), c4);
		printf("│");
		printf("%*ls %-*s", (int)(15 + wcslen(c5)), c5, 13, " ");
		printf("┃\n");
		printf(" ┠");
		for (int i = 0; i < 15; i++) printf("─");
		printf("┼");
		for (int i = 0; i < 8; i++) printf("─");
		printf("┼");
		for (int i = 0; i < 3; i++) printf("─");
		printf("┼");
		for (int i = 0; i < 8; i++) printf("─");
		printf("┼");
		for (int i = 0; i < 14; i++) {
			printf("─");
			printf("┬");
		}
		printf("─");
		printf("┨\n");
}

void print_data(Person p) {

		printf(" ┃");
		printf("%-*ls", (int)(15 + wcslen(p.second_name)), p.second_name);
	    printf("│");
	    printf("%-*ls", 10, p.initials);
	    printf("│");
	    printf("%-*lc", 4, p.gender);
	    printf("│");
	    printf("%-*ls", 10, p.group);
	    printf("│");
	    for (int i = 0; i < 15; ++i) {
            if (p.marks[i] != -1) {
                printf("%d", p.marks[i]);
            } else {
                printf(" ");
            }
	    	
	    	if (i == 14) printf("┃\n");
	    	else printf("│");
	    }
}

void print_table() {

			printf(" ┠");
			for (int i = 0; i < 15; i++) printf("─");
			printf("┼");
			for (int i = 0; i < 8; i++) printf("─");
			printf("┼");
			for (int i = 0; i < 3; i++) printf("─");
			printf("┼");
			for (int i = 0; i < 8; i++) printf("─");
			printf("┼");
			for (int i = 0; i < 14; i++) {
				printf("─");
				printf("┼");
			}
			printf("─");
			printf("┨\n");
}

void print_foot() {
	printf(" ┗");
	for (int i = 0; i < 15; i++) printf("━");
	printf("┷");
	for (int i = 0; i < 8; i++) printf("━");
	printf("┷");
	for (int i = 0; i < 3; i++) printf("━");
	printf("┷");
	for (int i = 0; i < 7; i++) printf("━");
	for (int i = 0; i < 15; i++) {
			printf("━");
			printf("┷");
		}
	printf("━");
	printf("┛\n");
}

typedef struct {
	Person p;
	double avg;
} Avg_pair;

int main(int argc, char* argv[]) {

	if (argc > 5 && argc != 1) {
		usage();
		return 1;
	}

    setlocale(LC_ALL,"");

    char filename[256];
    bool f_key = false, p_key = false;
    int p_value = 0;

    for (int i = 1; i < argc - 1; ++i) {
		// printf("%s\n", argv[i]);
        if (strcmp(argv[i], "-f") == 0) {
            f_key = true;
        } else if (strcmp(argv[i], "-p") == 0) {
			++i;
			p_key = true;
			p_value = atoi(argv[i]);
		} else {
			usage();
			return 1;
		}

    }

	Person pers;
	FILE *in = fopen(argv[argc - 1], "r");

	if (!in) {
		perror("Can't open file");
		return 2;
	}

	int people_count = 0;
	
	Avg_pair best[p_value];

	for (int i = 0; i < p_value; ++i) {
		best[i].avg = -1;
	}


	if (f_key) {
		print_head();
	}

	while (fread(&pers, sizeof(pers), 1, in) == 1) {

		Avg_pair cur;

		for (int i = pers.subjects_num; i < 15; ++i) {
			pers.marks[i] = -1;
		}

		cur.p = pers;

		if (f_key) { 
			if (people_count != 0) print_table(); // Иначе лишняя строка.
			print_data(pers);
		}

		++people_count;

		double sum = 0;

		for (int i = 0; i < pers.subjects_num; ++i) {
			if (pers.marks[i] != -1) {
				sum += pers.marks[i];
			}
		}

		// printf("%d", sum);

		cur.avg = sum / pers.subjects_num;

		if (cur.avg > best[p_value - 1].avg) {
			best[p_value - 1] = cur;
		}

		for (int i = p_value - 1; i > 0; --i) {
			if (best[i].avg > best[i - 1].avg) {
				Avg_pair tmp = best[i];
				best[i] = best[i - 1];
				best[i - 1] = tmp;
			}
		}

	}

	if (f_key) print_foot();

	fseek(in, 0, SEEK_SET);
	if (people_count == 0) {
		perror("No people.\n");
		return 3;
	}

	fclose(in);

	p_value = (people_count < p_value) ? people_count : p_value;

	printf("\nBest %d students\n", p_value);

	print_head();

	for (int i = 0; i < p_value; ++i) {
		if (i != 0) print_table();
		print_data(best[i].p);
	}

	print_foot();

	// printf("%lf %d\n", best[0].avg, best[0].p.subjects_num);

	return 0;
}
