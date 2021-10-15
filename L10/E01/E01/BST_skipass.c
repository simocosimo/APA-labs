#include "BST_skipass.h"

BST *initBST()
{
	BST *bst = malloc(sizeof(*bst));
	bst->head = NULL;
	return bst;
}

BSTNode *newBSTNode(int cardID, char *skiliftID, int time) {
	BSTNode *node = malloc(sizeof(*node));
	node->cardID = cardID;
	node->l = (node->r = NULL);
	node->skiliftAccess = createList();
	addNodeToList(node->skiliftAccess, skiliftID, time);
	return node;
}

void insertBSTNodeW(BST *root, int cardID, char *skiliftID, int time) {
	root->head = insertBSTNode(root->head, cardID, skiliftID, time);
}

BSTNode *insertBSTNode(BSTNode *root, int cardID, char *skiliftID, int time) {
	if (root == NULL) {
		return newBSTNode(cardID, skiliftID, time);
	}
	if (cardID < root->cardID) root->l = insertBSTNode(root->l, cardID, skiliftID, time);
	else if (cardID > root->cardID) root->r = insertBSTNode(root->r, cardID, skiliftID, time);

	return root;
}

BSTNode *findSkipass(BSTNode *root, int cardID) {
	BSTNode *skipass = NULL;
	if (root == NULL) return NULL;
	if (cardID == root->cardID) skipass = root;
	else if (cardID < root->cardID) skipass = findSkipass(root->l, cardID);
	else if (cardID > root->cardID) skipass = findSkipass(root->r, cardID);
	return skipass;
}

int authorize(BST *root, List *skiliftIt, int cardID, char *skiliftID, int time) {
	int ti = getTiMins(skiliftIt, skiliftID);
	if (ti < 0) {
		printf("Skilift non trovato. ");
		return 0;
	}
	BSTNode *skitofind = findSkipass(root->head, cardID);
	if (skitofind == NULL) {
		insertBSTNodeW(root, cardID, skiliftID, time);
		return 1;
	} else {
		int last_access = getTiMins(skitofind->skiliftAccess, skiliftID);
		if (last_access < 0) {
			addNodeToList(skitofind->skiliftAccess, skiliftID, time);
			return 1;
		} else {
			// I've found the last skipass access, now checking if the time interval is respected
			if (time - last_access < ti) return 0;
			else {
				// Modify the last access and return 1
				modifyNode(skitofind->skiliftAccess, skiliftID, time);
				return 1;
			}
		}
	}
}

void freeBSTNode(BSTNode *bstnode) {
	if (bstnode->l != NULL) freeBSTNode(bstnode->l);
	if (bstnode->r != NULL) freeBSTNode(bstnode->r);
	freeList(bstnode->skiliftAccess);
	free(bstnode); return;
}

void freeBST(BST *root) {
	if(root->head != NULL) freeBSTNode(root->head);
	free(root);
}