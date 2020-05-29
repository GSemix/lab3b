#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char letter;
	struct Node * next;
} Node;

struct borders{
	Node * first;
	Node * last;
};

void init(struct borders ** border, char letter) {
	Node * root = (Node *) calloc(1, sizeof(Node));
	if (root == NULL) printf("#####");
	root->letter = letter;
	root->next = NULL;
	(*border)->first = root;
	(*border)->last = root;
}

void shift(struct borders ** border, char letter) {
	if ((*border)->first == NULL) {
		init(border, letter);
	} else {
		Node * tmp = (*border)->last;
		Node * root = (Node *) calloc(1, sizeof(Node));
		if (root == NULL) printf("#####");
		root->letter = letter;
		root->next = NULL;
		tmp->next = root;
		(*border)->last = root;
	}

}

void show(Node * border) {
	while (border != NULL) {
		printf("%c", border->letter);
		border = border->next;
	}
	printf("\n");
}

void deleteList(struct borders ** border) {
	Node * tmp = NULL;
	Node * prev = (*border)->first;
	while (prev != NULL) {
		tmp = prev;
		prev = prev->next;
		free(tmp);
	}
	//free(prev);
	(*border)->first = NULL;
	(*border)->last = NULL;
}

int main() {
	struct borders * border = (struct borders *) calloc(1, sizeof(struct borders));
	
	if (border == NULL) return 0;
	
	char buf;
	int sc = 1;
		
	do {
		sc = scanf("%1[^\n]", &buf);
		
		if (sc == -1) break;
		else if (sc == 1) {
			shift(&border, buf);
		} else {
			show(border->first);
			deleteList(&border);
			scanf("%*c");
		}
		
	} while (sc != -1);
	
	show(border->first);
	
	return 0;
}
