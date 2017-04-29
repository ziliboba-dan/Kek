#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "palindrom.h"

int process(const char *file_name)
{
	FILE *a;
	a = fopen(file_name, "r");
	if (a == NULL) {
		return -1;
	}
	FILE *b;
	b = fopen("final.txt","w");
	if (b == NULL) {
		return -1;
	}

	//узнаём длину файла в байтах
	fseek(a, 0, SEEK_END);
	long int size = ftell(a);
	printf("Size = %li\n", size);
	rewind(a);
	//выделяем память для хранения содержимого файла	
	char *buffer = malloc(sizeof(char) * (size));
	if (buffer == NULL) {
		return -1;
	}

	//считываем файл в массив
	size_t result = fread(buffer, 1, size, a);
	if (result != size ) {
		return -1;
	}
	char *str = malloc(sizeof(char) * size);
	if (str == NULL) {
		return -1;
	}
	printf("%d\n", strlen(buffer));
	int ix = 0;
	int is = 0;
	//удаление всех знаков препинания и запись в второй буфер 
	while (ix < size) {
		if(!(ispunct(buffer[ix]) || (isdigit(buffer[ix]) || (buffer[ix] == '\n')))){
			printf("%c", buffer[ix]);
			str[is] = buffer[ix];
			is++;
		}
		ix++;
	}
	printf("\n");
	printf("%s\n", str);
	//palindrom
	int k = 0;
	char *str1 = malloc(sizeof(char) * size);
	if (str1 == NULL) {
		return -1;
	}
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != ' ') {
			str1[k] = str[i];
			k++;
		}
		else {
			printf("%s ", str1);
			printf("%d\n", strlen(str1));
			int znach = 1;
			for (int j = 0; j < strlen(str1); j++) {
				printf("%c  ", str1[j]);
				printf("%c\n", str1[strlen(str1) - 1 - j]);
				if (tolower(str1[j]) != tolower(str1[strlen(str1) - 1 - j])) {
					znach = 0;
				}
			}
			if (znach) {
				printf("%s", str1);
				printf("\n");
			}
			memset(str1, 0 ,strlen(str1));
			k = 0;
		}
	}
	printf("%c\n", str1[0]);
	free(str);
	free(str1);
	free(buffer);
	fclose(a);
	fclose(b);
	return 0;
}


