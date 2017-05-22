/*
Question:Write recursive versions of TREE-MINIMUM and TREE-MAXIMUM.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node* left;
	struct _node* right;
}node;

int tree_minmun(node* p) {
	if (p->left == NULL) {
		return p->data;
	}
	else {
		return tree_minmun(p->left);
	}
}

int tree_maxmum(node* p) {
	if (p->right == NULL) {
		return p->data;
	}
	else {
		return tree_maxmum(p->right);
	}
}

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
		printf("input a int data:");
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

int main(int argc, char** argv) {
	node* root = NULL;
	printf("create a BST(example 62,88,58,47,35,73,51,99,37,93):\n");
	create(&root);

	printf("tree_minmun:%d\n", tree_minmun(root));
	printf("tree_maxmum:%d\n", tree_maxmum(root));
	return 0;
}