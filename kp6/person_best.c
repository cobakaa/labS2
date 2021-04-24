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

int main(int argc, char* argv[]) {

	if (argc > 5 && argc != 1) {
		usage();
		return 1;
	}

    setlocale(LC_ALL,"");

    char filename[256];
    bool f_key = false, p_key = false;
    int p_value = 0;

    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-f") == 0) {
            f_key = true;
        }

        if ()
    }

	Person pers;
	FILE *in = fopen(argv[1], "r");

	if (!in) {
		perror("Can't open file");
		return 2;
	}

	int people_count = 0;
	int minSum[8];
	int maxSum[8];
	int maxDelta = -1;
	int group_num;
	int minSum_sub_count[8];
	int maxSum_sub_count[8];

	for (int i = 0; i < 8; ++i) {
		maxSum[i] = -1;
		minSum[i] = 80;
		minSum_sub_count[i] = 1;
		maxSum_sub_count[i] = 1;
	}

	if (f == 1) {
		print_head();
	}

	while (fread(&pers, sizeof(pers), 1, in) == 1) {

				
		for (int i = pers.subjects_num; i < 15; ++i) {
			pers.marks[i] = -1;
		}
		if (f == 1) { 
			if (people_count != 0) print_table(); // Иначе лишняя строка.
			print_data(pers);
		}

		++people_count;

		group_num = (int)(pers.group[6] - '0');

		int sum = 0;

		for (int i = 0; i < pers.subjects_num; ++i) {
			sum += pers.marks[i];
		}

		if (maxSum[group_num - 1] * pers.subjects_num < sum * maxSum_sub_count[group_num - 1]) {  // maxSum[group_naum - 1] / maxSum_sub_count[group - 1] < sum / pers.subjects_num
			maxSum[group_num - 1] = max(maxSum[group_num - 1], sum);							// Максимальный средний балл < текущего среднего балла
			maxSum_sub_count[group_num -1] = pers.subjects_num;
		}

		if (minSum[group_num - 1] * pers.subjects_num > sum * minSum_sub_count[group_num - 1]) { // Аналогично
			minSum[group_num - 1] = min(minSum[group_num - 1], sum);
			minSum_sub_count[group_num - 1] = pers.subjects_num;
		}

	}

	if (f == 1) print_foot();

	fseek(in, 0, SEEK_SET);
	if (people_count == 0) {
		perror("No people.\n");
		return 3;
	}
									// i - номер группы - 1
	for (int i = 0; i < 8; ++i) {													// maxSum[i]/maxSum_sub_count[i] - minSum[i]/minSum_sub_count[i] > maxDelta
		int k = maxDelta * maxSum_sub_count[i] * minSum_sub_count[i]; 
		if (maxSum[i] * minSum_sub_count[i] - minSum[i] * maxSum_sub_count[i] > k) { //избегаем double
			group_num = i;
			maxDelta = maxSum[i] - minSum[i]; // в условии разница максимальна
		}
	}

	printf("\nAnswer: М80-10%dБ\n", group_num + 1);
	fclose(in);
	return 0;
}
