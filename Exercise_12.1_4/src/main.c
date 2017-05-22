/*
Question:
Give recursive algorithms that perform preorder and postorder tree walks in O(n)
time on a tree of n nodes.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
	int data;
	struct _node* left;
	struct _node* right;
} node;

void create_bit_tree(node** p){
	int x = 0;

	printf("input a int data(-1 means NULL for chind):");
	scanf("%d", &x);

	if (x == -1) {
		*p = NULL;
	}
	else {
		*p = (node*)malloc(sizeof(node));
		(*p)->data = x;

		create_bit_tree(&((*p)->left));
		create_bit_tree(&((*p)->right));
	}
}

void pre_order(node* p) {
	if (p != NULL) {
		printf("%d ", p->data);
		pre_order(p->left);
		pre_order(p->right);
	}
}

void post_order(node* p) {
	if (p != NULL) {
		pre_order(p->left);
		pre_order(p->right);

		printf("%d ", p->data);
	}
}

int main(int argc, char** argv) {
	node* root = NULL;

	printf("create a tree(example: 3 6 4 -1 -1 -1 10 9 -1 7 -1 -1 12 -1 -1):\n");
	create_bit_tree(&root);

	printf("preorder result:\n");
	pre_order(root);
	printf("\npostorder result:\n");
	post_order(root);
	printf("\n");

	return 0;
}