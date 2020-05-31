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

void init(struct borders * border, char letter) {
	Node * root = calloc(1, sizeof *root);
	root->letter = letter;
	root->next = NULL;
	border->first = root;
	border->last = root;
}

void shift(struct borders * border, char letter) {
	if (border->first == NULL) {
		init(border, letter);
	} else {
		Node * tmp = border->last;
		Node * root = calloc(1, sizeof *root);
		root->letter = letter;
		root->next = NULL;
		tmp->next = root;
		border->last = root;
	}
}

void show(Node * border) {
	printf("\"");

	while (border != NULL) {
		printf("%c", border->letter);
		border = border->next;
	}
	
	printf("\"\n");
}

void delete_list(struct borders * border) {
	Node * tmp = NULL;
	Node * prev = border->first;
	while (prev != NULL) {
		tmp = prev;
		prev = prev->next;
		free(tmp);
	}
	border->first = NULL;
	border->last = NULL;	
}

void delete_space(struct borders * border) {
	Node * root = border->first;
	Node * del;
	while (root->next != NULL) {
		if (((root->letter == ' ') || (root->letter == '\t')) && ((root->next->letter == ' ') || (root->next->letter == '\t'))) {
			del = root->next;
			root->next = root->next->next;
			free(del);
		} else if (root->next->letter == '\t') {
			root->next->letter = ' ';
		} else if ((root->next->letter == ' ') && (root->next->next == NULL)) {
			del = root->next;
			root->next = NULL;
			free(del);
			border->last = root;
		} else {
			root = root->next;
		}
	}
	
	if ((border->first->letter == ' ') || (border->first->letter == '\t') ) {
		del = border->first;
		border->first = border->first->next;
		free(del);
	}
	
	root = border->first;
	
	while ((root != NULL) && (root->next != NULL)) {
		if ((root->next->letter == ' ') && (root->next->next == NULL)) {
			del = root->next;
			root->next = NULL;
			free(del);
			border->last = root;
		}
		
		if (root->next != NULL) {
			root = root->next;
		}
	}
}

Node * n_elem(Node * tmp, int count) {
	for (int i = 1; i < count; i++) {
		tmp = tmp->next;
	}
	
	return tmp;
}

int word_len(Node * root) {
	int count = 1;

	while ((root->next != NULL) && (root->next->letter != ' ')) {
		root = root->next;
		count++;
	}
	
	return count;
}

void line_processing(struct borders * border) {
	Node * root = border->first;
	Node * head = border->first;
	Node * tmp;
	char letter;
	int count = word_len(border->first);
	
	while (root->next != NULL) {
		
		for (int i = 0, j = count; i < j; ++i, --j) {
			letter = root->letter;
			tmp = n_elem(head, j);
			root->letter = tmp->letter;
			tmp->letter = letter;
			root = root->next;
		}
		
		head = n_elem(head, count);
		
		if (head->next != NULL) {
			head = head->next->next;
			count = word_len(head);
		}
		
		root = head;	
	}
}

int main() {
	struct borders * border = calloc(1, sizeof *border);
	
	if (border == NULL) return 0;
	
	char buf;
	int sc = 1;
		
	do {
		sc = scanf("%1[^\n]", &buf);
		
		if (sc == -1) {
			break;
		} else if (sc == 1) {
			shift(border, buf);
		} else {
			if (border->first != NULL) {
				delete_space(border);
				if (border->first != NULL) {
					line_processing(border);
					show(border->first);
					delete_list(border);
				} else {
					show(border->first);
				}
			} else {
				show(border->first);
			}
			
			scanf("%*c");
		}
		
	} while (sc != -1);
	
	free(border);
	
	return 0;
}
