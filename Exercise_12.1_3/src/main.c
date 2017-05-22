/*
Question:
Give a nonrecursive algorithm that performs an inorder tree walk.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct _node{
	int data;
	struct _node* left;
	struct _node* right;
} node;

typedef struct _stack{
	node* p_node[N];
	int top;
} stack;

void insert(node** ptr, node* s) {
	if (*ptr == NULL) {
		*ptr = s;
	}
	else {
		if (s->data == (*ptr)->data) {
			return;
		}
		else if (s->data < (*ptr)->data) {
			insert(&((*ptr)->left), s);
		}
		else {
			insert(&((*ptr)->right), s);
		}
	}
}

void create(node** ptr) {
	int flag = 1;
	int x = 0;
	node* s = NULL;

	while (flag) {
		printf("input a node data:");
		scanf("%d", &x);
		if (x == -1) {
			flag = 0;
		}
		else {
			s = (node*)malloc(sizeof(node));
			s->data = x;
			s->left = s->right = NULL;

			insert(ptr, s);
		}
	}
}

void in_order_walk(node* root) {
	node* p = root;
	stack s;
	memset(&s, 0, sizeof(s));
	int flag = 0;

	while (p != NULL || flag) {
		while (p != NULL) {
			s.top++;
			s.p_node[s.top] = p;
			p = p->left;
		}

		if (s.top > 0) {
			flag = 1;
			p = s.p_node[s.top];
			s.top--;
			printf("%d ", p->data);

			p = p->right;
		}
		else {
			flag = 0;
		}
	}

	printf("\n");
}

int main(int argc, char** argv) {
	node* root = NULL;

	printf("create a BST(example 62,88,58,47,35,73,51,99,37,93):\n");
	create(&root);

	in_order_walk(root);

	return 0;
}