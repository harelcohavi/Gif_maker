#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "global.h"

#define BIG_NUM 10000
#define ERROR_TIME 3
#define MS_TO_SEC 1000
#define BEEP_TIME 0.8 //time in sec
#define BEEP_FREQUENCY 750

/*
	this function is better version of fgets
	input: NONE
	output: pointer to the first char in the str
*/

char* myFgets()
{
	char tempStr[BIG_NUM] = { 0 };
	char* str = NULL;
	fgets(tempStr, BIG_NUM, stdin);
	str = (char*)malloc(sizeof(char) * strlen(tempStr));
	tempStr[strcspn(tempStr, "\n")] = 0;
	strcpy(str, tempStr);
	return str;
}

/*
	print with color
	input: the text to print
	output: NONE
*/

void printColorful(char* toPrint)
{
	int color = 0;
	int i = 0;

	srand(time(NULL));

	for (i = 0; i < strlen(toPrint); i++)
	{
		color = rand() % 8;

		if (!color)
		{
			printf("\x1B[0m");
		}
		else
		{
			printf("\x1B[3%dm", color);
		}

		printf("%c", toPrint[i]);
	}

	printf("\x1B[0m");//set the color
}

/*
	this function clean a string
	input: the string to clean
	output: NONE
*/

void cleanString(char* string)
{
	int i = strlen(string);

	for (i;i;--i)
	{
		string[i] = NULL;
	}
	string[i] = NULL;//the last one
}

/*
	this function get int without enter
	input: NONE
	output: the user number
*/

int getInt(void)
{
	int num;

	num = getch() - '0';

	return num;
}

/*
	this function print a warning
	input: the warning
	output: NONE
*/

void warning(char* theWarning)
{
	int i = 0;

	for (i = 0; i < ERROR_TIME; i++)
	{
		system("cls");
		printf("\033[0;31m%s", theWarning);
		printf("\n\n%d", i + 1);
		Beep(BEEP_FREQUENCY, BEEP_TIME * MS_TO_SEC);
		Sleep((1 - BEEP_TIME) * MS_TO_SEC);
	}
	printf("\x1B[0m");//set the color
}