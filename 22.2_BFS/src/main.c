#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct _eNode {
	int index;
	struct _eNode* next;
}eNode;

typedef struct _vNode {
	int index;
	eNode* s;
}vNode;

typedef struct _queue{
	int q[N];
	int front;
	int rear;
}queue;

enum _color {
	WHITE,
	GRAY,
	BLACK
};

void create_graph(vNode* g, int n, int e) {
	int i = 0;
	int j = 0;
	int idx_from = 0;
	int idx_to = 0;
	eNode* p = NULL;
	eNode* q = NULL;

	for (i = 0; i < n; i++) {
		g[i].index = i + 1;
		g[i].s = NULL;
	}

	for (j = 0; j < e; j++) {
		printf("[the %d edge]\n", j+1);
		scanf("%d", &idx_from);
		printf("=>");
		scanf("%d", &idx_to);
		printf("\n");

		i = 0;
		while (i < n && g[i].index != idx_from) {
			i++;
		}

		if (i >= n) {
			printf("Failed to find the vetex.\n");
		}

		p = g[i].s;

		q = (eNode*)malloc(sizeof(eNode));
		q->index = idx_to;
		q->next = p;
		g[i].s = q;
	}
}

void travgraph(vNode* g, int n) {
	int i = 0;
	eNode* p = NULL;

	for (i = 0; i < n; i++) {
		printf("[%d, %d]", i+1, g[i].index);
		p = g[i].s;
		while (p != NULL) {
			printf("%d ", p->index);

			p = p->next;
		}

		printf("\n");
	}

	printf("\n");
}

void enqueue(queue* qu, int index) {
	qu->rear++;
	qu->q[qu->rear] = index;
}

int dequeue(queue* qu) {
	if (is_empty(qu)) {
		printf("the queue is empty.");
		return 0;
	}
	else {
		qu->front++;
		return qu->q[qu->front];
	}
}

int is_empty(queue* qu) {
	if (qu->front == qu->rear) {
		return 1;
	}

	return 0;
}

void bfs(vNode* g, int s, int n) {
	int color[N] = {0};
	int d[N] = {0};
	int parent[N] = {0};
	int u = 0;
	int v = 0;
	eNode* p = NULL;

	for (int i = 0; i < n; i++) {
		color[i] = WHITE;
		d[i] = 0;
		parent[i] = 0;
	}

	color[s - 1] = GRAY;
	d[s - 1] = 0;
	parent[s - 1] = 0;

	queue qu;
	memset(&qu, 0, sizeof(queue));

	enqueue(&qu, s);
	while (!is_empty(&qu)) {
		u = dequeue(&qu);

		p = g[u - 1].s;
		while (p != NULL) {
			v = p->index;
			if (color[v - 1] == WHITE) {
				d[v - 1] = d[u - 1] + 1;
				parent[v - 1] = u;
				color[v - 1] = GRAY;

				enqueue(&qu, v);
			}
			p = p->next;
		}
		color[u - 1] = BLACK;
	}

	for (int i = 0; i < n; i++) {
		printf("the distance between %d and %d is %d.\n", i+1, s, d[i]);
	}
 }

int main(int argc, char** argv) {
	int n = 0;
	int e = 0;
	int s = 0;
	vNode adjlist[N];

	memset(adjlist, 0, sizeof(adjlist));

	printf("input the count of nodes and edges:");
	scanf("%d %d", &n, &e);

	create_graph(adjlist, n, e);

	travgraph(adjlist, n);

	printf("input the index of source:");
	scanf("%d", &s);
	bfs(adjlist, s, n);

	return 0;
}