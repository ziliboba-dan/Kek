#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "palindrom.h"

int palindrom(char *str, int size)
{
	int k = 0;
	int count = 0;
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
			int znach = 1;
			for (int j = 0; j < strlen(str1); j++) {
				if (((str1[j]) != (str1[strlen(str1) - 1 - j])) 
					&& ((str1[j]) != (str1[strlen(str1) - 1 - j] - 32)) 
						&& ((str1[j] - 32) != (str1[strlen(str1) - 1 - j]))) {
					znach = 0;
				}
			}
			if (znach) {
				printf("%s", str1);
				printf("\n");
				count++;
			}
			memset(str1, 0 ,strlen(str1));
			k = 0;
		}
	}
	free(str1);
	return count;
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
			if(!(ispunct(buffer[ix]) || (buffer[ix] == '\n'))){
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

	//узнаём длину файла в байтах
	fseek(a, 0, SEEK_END);
	long int size = ftell(a);
	//printf("Size = %li\n", size);
	if (size == 0) {
		printf("Memory allocation error, the file does not contain text\n");
		return 0;
	}
	rewind(a);
	//выделяем память для хранения содержимого файла	
	char *buffer;
	buffer = malloc(sizeof(char) * (size));
	if (buffer == NULL) {
		printf("Memory allocation error, the file does not contain text\n");
		return 0;
	}
	//считываем файл в массив
	size_t result = fread(buffer, 1, size, a);
	if (result != size ) {
		return -1;
	}
	printf("Text:\n%s", buffer);
	//удаляем все знаки препинания и цифры
	if (delete_punct(buffer, size) == -1) {
		return -1;
	}
	printf("Palindroms: \n");
	//поиск палиндромов
	int ind = palindrom(buffer, strlen(buffer));
	if (ind == -1 ) {
		printf("Memory allocation error, the file does not contain text\n");
		return 0;
	}
	else if (ind == 0) {
		printf("The text does not contain palindrome suggestions\n");
		return 0;
	}
	free(buffer);
	fclose(a);
	return 0;
}


