#include "person.h"

#include <stdio.h>
#include <locale.h>
#include <string.h>


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
        // while(token) {
            swscanf(token, L"%ls", p->second_name);
            token = wcstok(NULL, L"\t", &state);
            swscanf(token, L"%ls", p->initials);
            token = wcstok(NULL, L"\t", &state);
            swscanf(token, L"%lc", &p->gender);
            token = wcstok(NULL, L"\t", &state);
            swscanf(token, L"%ls", p->group);
            token = wcstok(NULL, L"\t", &state);
            
        // }
    }   

    wprintf(L"%ls\t%ls\t%lc\t%ls\n", p->second_name, p->initials, p->gender, p->group);
    
}

int main(int argc, char *argv[]) {

    // if (argc != 3) {
    //     usage();
    //     return 1;
    // }

    setlocale(LC_ALL,"");
    FILE *in = fopen("data2", "r");
    FILE *out = fopen("ddata2", "w");
    Person p;

    if (!in || !out) {
        perror("Can't open file");
        return 2;
    }

    while (!feof(in))
    {
        read_from_file(&p, in);
    }
    
    fclose(out);
    fclose(in);

    return 0;
}