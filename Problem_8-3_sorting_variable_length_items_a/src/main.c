#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000000
#define MAX_CH 10

typedef long long int int64_t;

typedef struct _item{
	char *str;
	int64_t len;
}item;

typedef struct _node {
	char data;
	struct _node* child[MAX_CH];
	int is_end;
	item* str;
	int64_t count;
}node;

typedef struct _queue{
	node* nodes[100];
	int64_t front;
	int64_t rear;
}queue;

int is_empty(queue *qu) {
	if (qu->front == qu->rear) {
		return 1;
	}

	return 0;
}

int is_full(queue* qu) {
	if (qu->rear == N) {
		return 1;
	}

	return 0;
}

void enqueue(queue* qu, node* x) {
	if (!is_full(qu)) {
		qu->rear++;
		qu->nodes[qu->rear] = x;
	}
}

node* dequeue(queue* qu) {
	node* ret = NULL;

	if (!is_empty(qu)) {
		qu->front++;
		ret = qu->nodes[qu->front];
	}

	return ret;
}

void build_trie_tree(node* root, item* vec, int64_t n) {
	for (int64_t i = 0; i<n; i++) {
		node* ptr = root;
		char* p = vec[i].str;
		int idx = 0;

		while (ptr != NULL && p != NULL && *p != '\0') {
			idx = *p - '0';

			if (ptr->child[idx] == NULL) {
				ptr->child[idx] = (node *)malloc(sizeof(node));
				memset(ptr->child[idx], 0, sizeof(node));
				ptr->child[idx]->data = *p;
			}
			
			ptr = ptr->child[idx];
			p++;
		}

		ptr->count++;
		ptr->is_end = 1;
		ptr->str = &vec[i];
	}
}

void visit(node *root) {
	queue qu;
	memset(&qu, 0, sizeof(queue));

	enqueue(&qu, root);

	node* mNode = NULL;
	while (!is_empty(&qu)) {
		mNode = dequeue(&qu);
		if (mNode != NULL) {
			if (mNode->is_end == 1) {
				for (int64_t i = 0; i<mNode->count; i++)
					printf("%s\n", mNode->str->str);
			}
			for (int i = 0; i<MAX_CH; i++) {
				if (mNode->child[i] != NULL)
					enqueue(&qu, mNode->child[i]);
			}
		}
	}
}

int main(){
	int64_t n = 0;
	printf("please input the size of integers:");
	scanf("%lld", &n);

	char str[N] = { '\0' };
	item* vec = (item *)malloc(n * sizeof(item));
	for (int64_t i = 0; i<n; i++) {
		memset(str, '\0', N * sizeof(char));
		printf("input a integet:");
		scanf("%s", str);
		vec[i].len = strlen(str);
		vec[i].str = (char *)malloc((vec[i].len + 1) * sizeof(char));
		strncpy(vec[i].str, str, vec[i].len);
		vec[i].str[vec[i].len] = '\0';
	}
	
	node* root = (node *)malloc(sizeof(node));
	memset(root, 0, sizeof(node));

	build_trie_tree(root, vec, n);
	visit(root);

	return 0;
}