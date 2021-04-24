#include "person.h"

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int mark_to_int(wchar_t * str) {
    if (wcscmp(str, L"отл.") == 0) {
        return 5;
    }

    if (wcscmp(str, L"хор.") == 0) {
        return 4;
    }

    if (wcscmp(str, L"удовл.") == 0) {
        return 3;
    }

    if (wcscmp(str, L"неуд.") == 0) {
        return 2;
    }

    if (wcscmp(str, L"зачтено") == 0) {
        return 1;
    }

    return 0;

}

void usage() {
    printf("Usage: inputFile outputFile\n");
}

void read_from_file(Person *p, FILE * f) {
    wchar_t str[256];
    int cnt;

    if (fgetws(str, sizeof(str), f) != NULL) {
        // cnt++;
        wchar_t *state;
        wchar_t *token = wcstok(str, L"\t", &state);

        swscanf(token, L"%ls", p->second_name);
        token = wcstok(NULL, L"\t", &state);
        swscanf(token, L"%ls", p->initials);
        token = wcstok(NULL, L"\t", &state);
        swscanf(token, L"%lc", &p->gender);
        token = wcstok(NULL, L"\t", &state);
        swscanf(token, L"%ls", p->group);
        token = wcstok(NULL, L"\t", &state);
        p->subjects_num = 0;
        while (token)
        {
            wchar_t mark[MARKS_MAX_STR];
            swscanf(token, L"%ls", mark);
            token = wcstok(NULL, L"\t", &state);

            if (isdigit(mark[0])) {
                swscanf(mark, L"%d", &p->marks[p->subjects_num]);
            } else {
                p->marks[p->subjects_num] = mark_to_int(mark);
            }

            p->subjects_num++;

        }
             
    }       
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        usage();
        return 1;
    }

    setlocale(LC_ALL,"");
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    Person p;

    if (!in || !out) {
        perror("Can't open file");
        return 2;
    }

    while (!feof(in))
    {
        read_from_file(&p, in);
        if (fwrite(&p, sizeof(p), 1, out) != 1) {
            perror("Writing error.\n");
        }
    }
    
    fclose(out);
    fclose(in);

    return 0;
}