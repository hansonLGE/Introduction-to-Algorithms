#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bnode {
	int data;
	struct _bnode *left;
	struct _bnode *right;
} bnode;

void inorder_tree_walk(bnode* ptr) {
	if (ptr != NULL) {
		inorder_tree_walk(ptr->left);
		printf("%d ", ptr->data);
		inorder_tree_walk(ptr->right);
	}
}

bnode* tree_search(bnode* ptr, int k) {
	if (ptr == NULL || k == ptr->data) {
		return ptr;
	}
	else {
		if (k < ptr->data) {
			return tree_search(ptr->left, k);
		}
		else {
			return tree_search(ptr->right, k);
		}
	}
}

bnode* tree_mininum(bnode* root) {
	bnode* ptr = root;

	while (ptr != NULL && ptr->left != NULL) {
		ptr = ptr->left;
	}

	return ptr;
}

bnode* tree_maxinum(bnode* root) {
	bnode* ptr = root;

	while (ptr != NULL && ptr->right != NULL) {
		ptr = ptr->right;
	}

	return ptr;
}

bnode* tree_successor(bnode* ptr) {
	if (ptr->right != NULL) {
		return tree_mininum(ptr->right);
	}
	else {
		return NULL; //TBD
	}
}

void tree_insert(bnode** ptr, bnode* s) {
	if (*ptr == NULL) {
		*ptr = s;
	}
	else {
		if (s->data == (*ptr)->data) {
			return;
		}
		else if (s->data < (*ptr)->data) {
			tree_insert(&((*ptr)->left), s);
		}
		else {
			tree_insert(&((*ptr)->right), s);
		}
	}
}

void tree_delete(bnode* root, int x) {
	bnode* ptr = root;
	bnode* par = NULL;
	bnode* r = NULL;

	while (ptr != NULL && ptr->data != x) {
		if (x < ptr->data) {
			par = ptr;
			ptr = ptr->left;
		}
		else if (x > ptr->data) {
			par = ptr;
			ptr = ptr->right;
		}
	}

	if (ptr == NULL) {
		printf("failed to find the node.\n");
	}
	else if (ptr->left == NULL) {
		if (par == NULL) {
			par = ptr->right;
		}
		else if (par->left = ptr) {
			par->left = ptr->right;
		}
		else {
			par->right = ptr->right;
		}

		free(ptr);
		ptr = NULL;
	}
	else {
		r = ptr->left;
		while (r->right != NULL) {
			r = r->right;
		}

		r->right = ptr->right;

		if (par == NULL) {
			par = ptr->left;
		}
		else if (par->left == ptr) {
			par->left = ptr->left;
		}
		else {
			par->right = ptr->left;
		}

		free(ptr);
		ptr = NULL;
	}
}

void create_binary_tree(bnode** tree) {
	int flag = 1;
	bnode* s = NULL;
	int x = 0;

	while (flag) {
		printf("input a node data:");
		scanf("%d", &x);
		if (x == -1) {
			flag = 0;
		}
		else {
			s = (bnode*)malloc(sizeof(bnode));
			s->data = x;
			s->left = s->right = NULL;

			tree_insert(tree, s);
		}
	}
}

int main(int argc, char** argv) {
	bnode* root = NULL;
	bnode* ptr = NULL;
	int x = 0;

	printf("create a BST(example 62,88,58,47,35,73,51,99,37,93,-1):\n");
	create_binary_tree(&root);
	inorder_tree_walk(root);
	printf("\n");

	printf("input a delete data:");
	scanf("%d", &x);
	tree_delete(root, x);
	inorder_tree_walk(root);
	printf("\n");

	return 0;
}