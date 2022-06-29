#include "saving.h"
#include "linkedList.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

#define BIG_NUM 1000
#define NULL_PLACE 1
#define TEN 10

/*
	this fumction load a gif (only if the user choose to)
	input: the FrameNode head (point to NULL)
	output: NONE
*/

void loadGif(FrameNode** head)
{
	int newGif = 0;
	FILE* gifFile = NULL;
	char* gifPath = NULL;
	FrameNode* curr = NULL;
	Frame* theFrame = NULL;
	FrameNode* newFrameNode = NULL;
	FrameNode* last = NULL;
	char path[BIG_NUM] = { 0 };
	char name[BIG_NUM] = { 0 };
	int duration = 0;
	char ch = 0;
	bool reachTheEnd = false;
	int i = 0;

	printf( "[0] Create a new project\n"
			"[1] Load existing project\n");
	newGif = getInt();

	if (!newGif)
	{
		printf("Working on a new project.\n");
	}
	else
	{
		printf("Enter the path of the project (including project name):\n");
		gifPath = myFgets();

		if ((gifFile = fopen(gifPath, "r")) != NULL)
		{
			fseek(gifFile, 0, SEEK_END);
			if (ftell(gifFile))//check if the file is empty
			{
				fseek(gifFile, 0, SEEK_SET);//back to the start of the file

				while (!reachTheEnd)
				{
					while ((ch = fgetc(gifFile)) != '\n' && !reachTheEnd)
					{
						if (ch == EOF)
						{
							reachTheEnd = true;
						}
						path[strlen(path)] = ch;
					}
					if (!reachTheEnd)
					{
						while ((ch = fgetc(gifFile)) != '\n')
						{
							duration *= TEN;
							duration += (ch - '0');
						}
						while ((ch = fgetc(gifFile)) != '\n')
						{
							name[strlen(name)] = ch;
						}

						theFrame = (Frame*)malloc(sizeof(Frame));
						newFrameNode = (FrameNode*)malloc(sizeof(FrameNode));

						//set the frame
						theFrame->path = (char*)calloc(sizeof(char), strlen(path) + NULL_PLACE);
						strcpy(theFrame->path, path);

						theFrame->name = (char*)calloc(sizeof(char), strlen(name) + NULL_PLACE);
						strcpy(theFrame->name, name);

						theFrame->duration = duration;

						//set the node and enter it to the list
						newFrameNode->frame = theFrame;
						newFrameNode->next = NULL;

						//set all the values
						cleanString(path);
						cleanString(name);
						duration = 0;

						if (!(*head))
						{
							(*head) = newFrameNode;
							last = (*head);
						}
						else
						{
							last->next = newFrameNode;
							last = last->next;
						}
					}
				}
				printf("\x1b[32Project loaded successfully");
			}
			else
			{
				warning("file is empty, open new project");
			}
			fclose(gifFile);
		}
		else
		{
			warning("file doesn't exist, open new project");
		}
		
		free(gifPath);
	}
}

/*
	this function save the project
	input: the head
	output: NONE
*/

void saveProject(FrameNode* head)
{
	FILE* projectFile = NULL;
	char* filePath = NULL;
	FrameNode* curr = head;

	printf("Where to save the project? enter a full path and file name\n");
	filePath = myFgets();//take the file path

	if ((projectFile = fopen(filePath, "w")) != NULL)
	{
		while (curr)
		{
			fprintf(projectFile, "%s\n%d\n%s\n", curr->frame->path, curr->frame->duration, curr->frame->name);
			curr = curr->next;
		}
		fclose(projectFile);
	}

	free(filePath);
}
