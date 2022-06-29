/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/
#define CV_IGNORE_DEBUG_BUILD_GUARD

#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

#include <stdio.h>
#include "linkedList.h"
#include "view.h"
#include "saving.h"
#include "global.h"

/*
	this program is a gif maker
	input: NONE
	output: 0 on success
*/

int main(void)
{
	enum option userChoice = 0;
	FrameNode* head = NULL;
	
	printColorful("Welcome to Magshimim Movie Maker! what would you like to do?\n");

	loadGif(&head);

	do//it's do while because userChoice set to 0 (EXIT)
	{
		if (userChoice != Print)
		{
			system("cls");
		}
		userChoice = menu();

		switch (userChoice)
		{
		case Exit:
			freeList(head, true);
			printf("Bye!");
			break;
		case Add:
			addFrame(&head);
			break;
		case Remove:
			removeFrame(&head);
			break;
		case ChangeIndex:
			moveFrame(&head);
			break;
		case ChangeDuration:
			changeOneDuration(head);
			break;
		case ChangeAllDurations:
			changeAllTheDurations(head);
			break;
		case Print:
			printList(head);
			break;
		case Play:
			play(head);
			break;
		case Save:
			saveProject(head);
			break;
		}
	} while (userChoice != Exit);

	getchar();
	return 0;
}

/*
	this function print the menu and take the user choice
	input: NONE
	output: the user choice
*/

enum option menu(void)
{
	enum option userChoice = 0;
	bool firstRun = true;

	do
	{
		if (!firstRun)
		{
			system("cls");
		}
		printf("What would you like to do?\n"
			" [0] Exit\n"
			" [1] Add new Frame\n"
			" [2] Remove a Frame\n"
			" [3] Change frame index\n"
			" [4] Change frame duration\n"
			" [5] Change duration of all frames\n"
			" [6] List frames\n"
			" [7] play movie!\n"
			" [8] save project\n");

		firstRun = false;
		userChoice = getInt();
	} while (userChoice < Exit || userChoice > Save);
	system("cls");
	return userChoice;
}