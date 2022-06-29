#ifndef LINKEDLISTH
#define LINKEDLISTH

#include <stdbool.h>

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

enum option
{
	Exit,
	Add,
	Remove,
	ChangeIndex,
	ChangeDuration,
	ChangeAllDurations,
	Print,
	Play,
	Save
};

enum option menu(void);
FrameNode* search(FrameNode* head, char* frameName);
void addFrame(FrameNode** head);
void removeFrame(FrameNode** head);
void moveFrame(FrameNode** head);
void changeOneDuration(FrameNode* head);
void changeAllTheDurations(FrameNode* head);
void printList(FrameNode* head);
void freeList(FrameNode* head, const bool freeAll);

#endif
