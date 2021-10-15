#include "BST_skipass.h"

#define MAXCH 6

int hoursToMinutes(char *hours);

int main(int argc, char **argv) {

	// Menu flag
	int stop = 0;

	// data to insert via stdin
	char hour[MAXCH];
	char skiliftID[MAXSKILID];
	int cardID;

	// data to acquiring via file
	if (argc != 2) return 1;
	List *skiliftIt = readSkiliftsFromFile(argv[1]);

	// data for BST 
	BST *root = initBST();

	printf("Inserire la richiesta di autorizzazione (skiliftId cardId ora:minuti) o \"fine\" per uscire\n");
	while (!stop) {
		printf("Richiesta: ");
		scanf("%s", skiliftID);
		if (strcmp(skiliftID, "fine") == 0) stop = 1;
		else {
			scanf("%d %s", &cardID, hour);
			if (authorize(root, skiliftIt, cardID, skiliftID, hoursToMinutes(hour))) printf("Autorizzazione concessa!\n");
			else printf("Autorizzazione negata!\n");
		}
	}

	// free functions
	freeList(skiliftIt);
	freeBST(root);

	system("PAUSE");
	return 0;
}

int hoursToMinutes(char *hours) {
	char h[2], mins[2];
	if (hours[1] == ':') {
		h[0] = '0'; h[1] = hours[0];
		mins[0] = hours[2]; mins[1] = hours[3];
	} else {
		h[0] = hours[0]; h[1] = hours[1];
		mins[0] = hours[3]; mins[1] = hours[4];
	}
	int hi = atoi(h);
	int mini = atoi(mins);
	mini += (hi * 60);
	return mini;
}