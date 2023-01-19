#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MEM_STEP 25

//Функция ввода с клавиатуры предложения:

char* getSentence() {
	char* sentence;
	char sym;
	int size_sentence = 50;
	sentence = malloc(size_sentence * sizeof(char));
	int i = 0;
	do {
		if (i == size_sentence - 2) {
			size_sentence += MEM_STEP;
			sentence = realloc(sentence, size_sentence * sizeof(char));
		}
		sym = getchar();
		sentence[i] = sym;
		i++;
		if (sym == '\n')
			return NULL;
	} while (sym != '.' && sym != '\n');

	sentence[i - 1] = '\0';

	return sentence;
}

//Функция добавления каждого предложения в массив:

char** getText(int* size) {
	int size_text = 35;
	char* sentence;
	char** text;
	text = malloc(size_text * sizeof(char*));
	int i = 0;

	while ((sentence = getSentence())) {
		text[i] = sentence;
		if (i == size_text - 2) {
			size_text += MEM_STEP;
			text = realloc(text, size_text * sizeof(char*));
		}
		i++;
	}

	*size = i;

	return text;
}

//Функция вывод текста на экран:

void printText(char** text, int size) {
	int i = 0;
	for (i = 0; i < size; i++)
		if (text[i] != NULL)
			printf("%s", text[i]);
}

//Функция удаления дубликатов в массиве предложений:

//Удаление одинаковых символов:

int StrCompare(const void* str1, const void* str2)
{
	return strcmp(*(const char**)str1, *(const char**)str2);
}

//Сортировка в лексиграфическом порядке:

char** sortText(char** text, int size)
{
	char** words;
	char* ptr;
	int wordsCount;

	for (int i = 0; i < size; i++)
	{
		words = (char**)malloc(sizeof(char*));
		ptr = strtok(text[i], " ,.");
		wordsCount = 0;
		while (ptr)
		{
			words = (char**)realloc(words, sizeof(char*) * (wordsCount + 1));
			words[wordsCount] = malloc(sizeof(char) * strlen(ptr));
			strcpy(words[wordsCount], ptr);
			wordsCount++;
			ptr = strtok(NULL, " ,.");
		}
		qsort(words, wordsCount, sizeof(const char*), StrCompare);
		char* t = text[i];
		strcpy(t, words[0]);
		for (int j = 1; j < wordsCount; j++)
		{
			strcat(t, " ");
			strcat(t, words[j]);
		}
		printf("%s", text[i]);
	}
	return text;
}


//Удаление предложений с палиндромами:

int isPalindrome(char* text)
{
	int size = strlen(text);
	for (int i = 0; i < size; i++)
		if (text[i] != text[size - i - 1])
			return 0;
	return 1;
}

char** palindromeSentenceRemove(char** text, int* size)
{
	char* ptr;
	for (int i = 0; i < *size; i++)
	{
		char* line = malloc(sizeof(char) * strlen(text[i]));
		strcpy(line, text[i]);
		ptr = strtok(line, " ,.");
		while (ptr)
		{
			if (isPalindrome(ptr))
			{
				for (int j = i; j < (*size) - 1; j++)
				{
					strcpy(text[j], text[j + 1]);
				}
				// Освободить общую память на -1 строку
				i--;
				(*size)--;
				ptr = NULL;
				break;
			}
			ptr = strtok(NULL, " ,.");
		}
	}
	return text;
}

//Вывод всех предложений со словом "Hidden Agent":

//Функция вывода информации:

void show_inf() {
	printf("Выберите какое-то из нижеприведенных действий:\n");
	printf("0-выход из программы!\n");
	printf("1-удалить все одинаковые символы в начале и конце предложения!\n");
	printf("2-отсортировать все предложения в лексигрофическом порядке!\n");
	printf("3-удалить все предложения, в которых хотя бы одно слово является палиндромом!\n");
	printf("4-вывести все предложения в которых есть 'Hidden Agent'!\n");
}

//Основная функция:

int main() {
	setlocale(0, "ru");
	int size;
	char** text;
	text = getText(&size);
	printText(text, size);
	printf("Все повторяющиеся предложения удалены!\n");
	show_inf();
	int choice;
	printf("Ждем вашего выбора:");
	scanf("%d", &choice);
	switch (choice) {
	case 0:
		printf("Был выполнен выход из программы!\n");
		break;
	case 2:
		printText(sortText(text, size), size);
		break;
	case 3:
		text = palindromeSentenceRemove(text, &size);
		printText(text, size);
		break;
	}
}
