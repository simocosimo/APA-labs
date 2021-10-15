#ifndef _BST_SKIPASS_H_
#define _BST_SKIPASS_H_

#include "LIST_skilift.h"

typedef struct bstnode BSTNode;
typedef struct bst BST;

struct bstnode {
	int cardID;
	List *skiliftAccess;
	BSTNode *l, *r;
};

struct bst {
	BSTNode *head;
};

BST *initBST();
BSTNode *newBSTNode(int cardID, char *skiliftID, int time);
void insertBSTNodeW(BST *root, int cardID, char *skiliftID, int time);
BSTNode *insertBSTNode(BSTNode *root, int cardID, char *skiliftID, int time);
BSTNode *findSkipass(BSTNode *root, int cardID);
int authorize(BST *root, List *skiliftIt, int cardID, char *skiliftID, int time);
// free function
void freeBSTNode(BSTNode *bstnode);
void freeBST(BST *root);

#endif