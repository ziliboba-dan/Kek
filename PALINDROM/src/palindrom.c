#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "palindrom.h"

int palindrom_func(char *str, int size)
{
	int k = 0;
	char *str1 = malloc(sizeof(char) * size);
	if (str1 == NULL) {
		return -1;
	}
	for (int i = 0; i < strlen(str); i++) {
		if ((str[i] != '.' && str[i] != '!' && str[i] != '?')) {
			if ((str[i] != ' ')) {
				str1[k] = str[i];
				k++;
			}
		}
		else {	
			//printf("%s ", str1);
			//printf("%d\n", strlen(str1));
			int znach = 1;
			for (int j = 0; j < strlen(str1); j++) {
				//printf("%d  ", str1[j]);
				//printf("%d\n", str1[strlen(str1) - 1 - j]);
				if (((str1[j]) != (str1[strlen(str1) - 1 - j])) && ((str1[j]) != (str1[strlen(str1) - 1 - j] - 32)) && ((str1[j] - 32) != (str1[strlen(str1) - 1 - j]))) {
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
	free(str1);
	return 0;
}

int delete_punct(char *buffer, int size)
{
	int ix = 0;
	int is = 0;
	char *str = malloc(sizeof(char) * size);
	if (str == NULL) {
		return -1;
	}

	while (ix < size) {
		if((buffer[ix] != '.' && buffer[ix] != '!' && buffer[ix] != '?')){
			//printf("%c", buffer[ix]);
			if(!(ispunct(buffer[ix]) || (isdigit(buffer[ix]) || (buffer[ix] == '\n')))){
				str[is] = buffer[ix];
				is++;
			}			
		}
		else {
			str[is] = buffer[ix];
			is++;
		}
		ix++;
	}
	strcpy(buffer, str);
	return 0;
}

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
	//удаляем все знаки препинания и цифры
	if (delete_punct(buffer, size) == -1) {
		return -1;
	}
	printf("%s\n", buffer);
	printf("Palindroms: \n");
	//поиск палиндромов
	if (palindrom_func(buffer, strlen(buffer)) == -1) {
		return -1;
	}
	free(buffer);
	fclose(a);
	fclose(b);
	return 0;
}


