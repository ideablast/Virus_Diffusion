#ifndef __Data_H__
#define __Data_H__

typedef struct _Graph {
	char ch;
	struct _Graph **link;
}Graph;

typedef struct _Stack {
	Graph* G_link;
	struct _Stack* S_link;
}Stack;
#endif
#define ACTUAL

#define SIZE_START 5
#define SIZE_END 5


#define TRUE 1
#define FALSE 0
#define FAIL -1


#define NUM_OF_LINK 4
#define NUM_OF_NODE 4



