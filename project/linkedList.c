#include "linkedList.h"
#include "global.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define BIG_NUM 1000
#define NULL_PLACE 1

#pragma warning(disable:0020)
#pragma warning(disable:4996)

/*
	this function search a node by name
	input: the list head and the name of the frame to search
	output: the node before the wanted node, null if not found
*/

FrameNode* search(FrameNode* head, char* frameName)
{
	FrameNode* nowNode = head;
	FrameNode* lastNode = NULL;
	bool found = false;

	if (!strcmp(head->frame->name, frameName))
	{
		found = true;  //This case should not happen
	}
	lastNode = nowNode;
	nowNode = nowNode->next;

	while (nowNode && !found)
	{
		if (!strcmp(nowNode->frame->name, frameName))
		{
			found = true;
		}
		else
		{
			lastNode = nowNode;
			nowNode = nowNode->next;
		}
	}

	if (!found)
	{
		lastNode = NULL;
	}

	return lastNode;
}

/*
	this function make a new node in the list
	input: the head of the list
	output: NONE
*/

void addFrame(FrameNode** head)
{
	FrameNode* curr = NULL;
	FrameNode* newFrame = NULL;
	Frame* theNewFrame = NULL;
	char* name = NULL;
	char* path = NULL;
	int duration = 0;
	FILE* frame = NULL;
	bool sameName = true;

	printf("*** Creating new frame ***\n");

	printf("Please insert frame path:\n");
	path = myFgets();//get the frame path

	printf("Please insert frame duration<in miliseconds>:\n");
	scanf("%d", &duration);//get the duration
	getchar(); //clean the buffer

	printf("Please choose a name for that frame:\n");
	name = myFgets();//get the frame name

	if (!(frame = fopen(path, "r")))//check if the frame path exist
	{
		warning("file doesn't exsit");
	}
	else
	{
		fclose(frame);//dont need it any more
		
		
		if (!(*head))//in case it is the first one int the node
		{
			//set the frame
			theNewFrame = (Frame*)malloc(sizeof(Frame));
			theNewFrame->duration = duration;
			theNewFrame->name = name;
			theNewFrame->path = path;

			//set the node
			newFrame = (FrameNode*)malloc(sizeof(FrameNode));
			newFrame->frame = theNewFrame;
			newFrame->next = NULL;//it is the last one

			(*head) = newFrame;//connect the new node to the list
		}
		else
		{
			curr = (*head);//set to the start

			while (sameName)//check if the name is the same is the name of the first frame
			{
				if (!strcmp((*head)->frame->name, name))
				{
					printf("The name is already taken, please enter another name\n");
					free(name);
					name = myFgets();//get new name
					curr = (*head);//start the searching again
				}
				else
				{
					sameName = false;
				}
			}

			while (curr->next)
			{
				curr = curr->next;
				while (!strcmp(curr->frame->name, name))
				{
					printf("The name is already taken, please enter another name\n");
					free(name);
					name = myFgets();//get new name
					curr = (*head);//start the searching again
				}
			}

			//set the frame
			theNewFrame = (Frame*)malloc(sizeof(Frame));
			theNewFrame->duration = duration;
			theNewFrame->name = name;
			theNewFrame->path = path;

			//set the node
			newFrame = (FrameNode*)malloc(sizeof(FrameNode));
			newFrame->frame = theNewFrame;
			newFrame->next = NULL;//it is the last one

			curr->next = newFrame;//connect the new node to the list
			
		}
	}
}

/*
	this function remove the node that the user want
	input: the list head
	output: NONE
*/

void removeFrame(FrameNode** head)
{
	char* frameName = NULL;
	FrameNode* beforeToRemove = NULL;
	FrameNode* temp = NULL;

	if ((*head))//in case the list is empty
	{
		printf("Enter the name of the frame you wish to erase\n");
		frameName = myFgets();

		if (!strcmp((*head)->frame->name, frameName))
		{
			temp = (*head);
			(*head) = (*head)->next;
			freeList(temp, false);
		}
		else
		{
			beforeToRemove = search(*head, frameName);

			if (beforeToRemove)
			{
				temp = beforeToRemove->next;
				beforeToRemove->next = temp->next;
				freeList(temp, false);
			}
			else
			{
				warning("The frame was not found");
			}
		}

		free(frameName);
	}
	else
	{
		warning("the list is empty");
	}
}

/*
	this function move the index of frame
	input: pointer to the head of the list
	output: NONE
*/

void moveFrame(FrameNode** head)
{
	int index = 0;
	FrameNode* curr = (*head);
	FrameNode* toMove = NULL;
	FrameNode* beforeToMove = NULL;
	FrameNode* nextFrame = NULL;
	char* name = NULL;
	int i = 2;
	bool moved = false;
	bool existFrameName = false;

	if ((*head))//for case the list is empty
	{
		printf("Enter the name of the frame\n");
		name = myFgets();

		while (!existFrameName)//check that 
		{
			existFrameName = true;

			if (!strcmp((*head)->frame->name, name))
			{
				toMove = (*head);
				(*head) = (*head)->next;
				i--;//i short the list in 1 node then i need one run less
			}
			else if ((beforeToMove = search((*head), name)))
			{
				toMove = beforeToMove->next;

				beforeToMove->next = toMove->next;
			}
			else
			{
				printf("this frame does not exist\n");

				printf("Enter the name of the frame\n");//tale now name
				name = myFgets();

				existFrameName = false;
			}
		}

		while (!moved)
		{
			printf("Enter the new index in the movie you wish to place the frame\n");
			scanf("%d", &index);
			getchar(); //clean the buffer

			if (index == 1)
			{
				nextFrame = (*head);
				toMove->next = nextFrame;
				(*head) = toMove;
				moved = true;
			}
			else
			{
				for (i; i < index && curr->next; i++)
				{
					curr = curr->next;
				}
				if (i == index)
				{
					nextFrame = curr->next;
					curr->next = toMove;
					toMove->next = nextFrame;
					moved = true;
				}
				else
				{
					printf("The movie contains only %d frames!", i);
				}
			}
		}

		/*while (curr->next)
		{
			if (!strcmp(curr->next->frame->name, name))
			{
				toMove = curr->next;
				curr->next = curr->next->next;

				if (i < index)
				{
					for (i; i < index && curr; i++)
					{
						curr = curr->next;
					}
					if (curr)
					{
						nextFrame = curr->next;
						curr->next = toMove;
						toMove->next = nextFrame;
					}
					else
					{
						printf("The movie contains only %d frames!", i);
					}
				}
			}
			i++;
			curr = curr->next;
		}*/

		free(name);
	}
	else
	{
		warning("list is empty");
	}
}

/*
	this function change one duration
	input: the list head
	output: NONE
*/

void changeOneDuration(FrameNode* head)
{
	FrameNode* toChange = NULL;
	char* name = NULL;

	if (head)//fpr a case the list is empty
	{
		printf("Enter the name of the frame\n");
		name = myFgets();

		if (!strcmp(head->frame->name, name))
		{
			toChange = head;
		}
		else
		{
			toChange = search(head, name);
			if (toChange)//happens only if found
			{
				toChange = toChange->next;
			}
		}

		if (!toChange)
		{
			warning("The frame does not exist\n");
		}
		else
		{
			printf("Enter the new duration\n");
			scanf("%d", &(toChange->frame->duration));
			getchar(); //clean the buffer
			
		}

		free(name);
	}
	else
	{
		warning("list is empty");
	}
}

/*
	this function change all the duration
	input: the head of the list
	output: NONE
*/

void changeAllTheDurations(FrameNode* head)
{
	FrameNode* curr = head;
	int theDuration = 0;

	printf("Enter the duration for all frames:\n");
	scanf("%d", &theDuration);
	getchar(); //clean the buffer

	while (curr)
	{
		curr->frame->duration = theDuration;
		curr = curr->next;
	}
}

/*
	this function print the list
	input: the head of the list
	output: NONE
*/

void printList(FrameNode* head)
{
	FrameNode* curr = head;

	printf("Name		Duration		Path\n");

	while (curr)
	{
		printf("\x1b[32m%s		\x1b[34m%d ms			\x1b[35m%s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}

	printf("\x1b[0m");//set the color
}

/*
	this function free the list/one node
	input: the head of the list and if clear the all list or one node
	output: NONE
*/

void freeList(FrameNode* head, const bool freeAll)
{
	if (head)
	{
		if (freeAll)
		{
			freeList(head->next, freeAll);
		}
		free(head->frame->name);
		free(head->frame->path);
		free(head->frame);
		free(head);
	}
}