#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

typedef struct _Key
{
	int32_t val;
} Key;

typedef struct _Row
{
	Key key;
	char str[256];
} Row;

void printTable(const Row *arr, const int size);
int binSearch(const Row *arr, const int size, const Key *key);
void sort(Row *arr, const int size);
void scramble(Row *arr, const int size);
void reverse(Row *arr, const int size);

void getRow(FILE *stream, char *str, const int size);
void swapRows(Row *r1, Row *r2);
int comparator(const Key *k1, const Key *k2);
int isEqualKeys(const Key *k1, const Key *k2);
int randomAB(const int a, const int b);
int isSorted(const Row *a, const int size);

int main(void)
{
	const int N = 50;
	int i, cnt, action;
	char ch;
	Row arr[N];
	Key key;
	FILE *file = fopen("input.txt", "r");

	if (file == NULL)
	{
		printf("Ошибка при открытии файла\n");

		return 0;
	}

	i = 0;

	while (i < N && fscanf(file, "%d", &arr[i].key.val) == 1)
	{
		fscanf(file, "%c", &ch);
		getRow(file, arr[i].str, sizeof(arr[i].str));

		i++;
	}

	fclose(file);

	cnt = i;

	do
	{
		printf("Меню\n");
		printf("1) Печать\n");
		printf("2) Двоичный поиск\n");
		printf("3) Сортировка\n");
		printf("4) Перемешивание\n");
		printf("5) Реверс\n");
		printf("6) Выход\n");
		printf("Выберите действие\n");
		scanf("%d", &action);

		switch (action)
		{
			case 1:
			{
				printTable(arr, cnt);
			}
			break;

			case 2:
			{
				if (!isSorted(arr, cnt))
					printf("Ошибка. Таблица не отсортирована\n");
				else
				{
					printf("Введите ключ: ");
					scanf("%d", &key.val);

					i = binSearch(arr, cnt, &key);

					if (i > -1)
						printf("Найдена строка: %s\n", arr[i].str);
					else
						printf("Строка с таким ключом не найдена\n");
				}
			}
			break;

			case 3:
			{
				sort(arr, cnt);
			}
			break;

			case 4:
			{
				scramble(arr, cnt);
			}
			break;

			case 5:
			{
				reverse(arr, cnt);
			}
			break;

			case 6: break;

			default:
			{
				printf("Ошибка. Такого пункта меню не существует\n");
			}
			break;
		}
	}
	while (action != 6);

	return 0;
}

void printTable(const Row *a, const int size)
{
	int i;

	printf("+---------+------------------------------------------------------------------------------------------------+\n");
	printf("|   Ключ  |                    Значение                    	                                           |\n");
	printf("+---------+------------------------------------------------------------------------------------------------+\n");

	for (i = 0; i < size; i++)
		printf("|%9d|%-96s|\n", a[i].key.val, a[i].str);

	printf("+---------+------------------------------------------------------------------------------------------------+\n");
}

int binSearch(const Row *arr, const int size, const Key *key)
{
	int start = 0, end = size - 1, mid;

	if (size <= 0)
		return -1;

	while (start < end)
	{
		mid = start + (end - start) / 2;

		if (isEqualKeys(&arr[mid].key, key))
			return mid;
		else if (comparator(&arr[mid].key, key))
			start = mid + 1;
		else
			end = mid;
	}

	if (isEqualKeys(&arr[end].key, key))
		return end;

	return -1;
}

void sort(Row *arr, const int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
			if (!comparator(&arr[i].key, &arr[j].key))
				swapRows(&arr[i], &arr[j]);
	}
}

void scramble(Row *arr, const int size)
{
	int i, j, k;

	srand((unsigned int)time(0));

	for (k = 0; k < size; k++)
	{
		i = randomAB(0, size - 1);
		j = randomAB(0, size - 1);

		swapRows(&arr[i], &arr[j]);
	}
}

void reverse(Row *arr, const int size)
{
	int i, j;

	for (i = 0, j = size - 1; i < j; i++, j--)
		swapRows(&arr[i], &arr[j]);
}

void getRow(FILE *stream, char *str, const int size)
{
	int cnt = 0, ch;

	while ((ch = getc(stream)) != '\n' && cnt < size - 1)
		str[cnt++] = ch;

	str[cnt] = '\0';
}

void swapRows(Row *r1, Row *r2)
{
	Row tmp;

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

int comparator(const Key *k1, const Key *k2)
{
	return k1->val <= k2->val;
}

int isEqualKeys(const Key *k1, const Key *k2)
{
	return k1->val == k2->val;
}

int randomAB(const int a, const int b)
{
	return a + rand() % (b - a + 1);
}

int isSorted(const Row *a, const int size)
{
	int i;

	for (i = 0; i < size - 1; i++)
		if (!comparator(&a[i].key, &a[i + 1].key))
			return 0;

	return 1;
}
