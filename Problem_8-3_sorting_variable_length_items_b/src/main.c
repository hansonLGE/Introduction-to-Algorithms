#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1024
#define MAX_CH 26

typedef struct _item{
	char *str;
	int len;
}item;

typedef struct _node{
	char data;
	struct _node*  child[MAX_CH];
	int is_end;
	item* m_item;
}node;

void build_trie_tree(node* root, item* items, int N) {
	for (int i = 0; i < N; i++) {
		char* p = items[i].str;
		node* ptr = root;
		int idx = 0;

		while (*p != '\0') {
			idx = *p - 'a';
			if (ptr->child[idx] == NULL) {
				ptr->child[idx] = (node *)malloc(sizeof(node));
				memset(ptr->child[idx], 0, sizeof(node));
				ptr->child[idx]->data = *p;
			}

			ptr = ptr->child[idx];
			p++;
		}

		ptr->is_end = 1;
		ptr->m_item = &items[i];
	}
}

void preorder_visit(node* ptr) {
	if (ptr != NULL) {
		if (ptr->is_end == 1) {
			printf("%s ", ptr->m_item->str);
		}

		for (int i = 0; i < MAX_CH; i++) {
			preorder_visit(ptr->child[i]);
		}
	}
}

int main(int argc, char** argv) {
	char str[LEN] = { '\0' };
	int N = 0;

	printf("please input the number of strings:");
	scanf("%d", &N);

	item* items = (item *)malloc(N * sizeof(item));
	for (int i = 0; i < N; i++) {
		memset(str, '\0', LEN * sizeof(char));
		printf("input a string:");
		scanf("%s", str);
		items[i].len = strlen(str);
		items[i].str = (char *)malloc(items[i].len * sizeof(char));
		strncpy(items[i].str, str, items[i].len);
		items[i].str[items[i].len] = '\0';
	}

	node* root = (node *)malloc(sizeof(node));
	memset(root, 0, sizeof(node));

	build_trie_tree(root, items, N);
	preorder_visit(root);

	printf("\n");
	return 0;
}