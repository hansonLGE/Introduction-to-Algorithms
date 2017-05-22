#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct _eNode{
	int idx;
	struct _eNode* next;
}eNode;

typedef struct _vNode{
	int idx;
	eNode* link;
}vNode;

enum Color{
	WHITE,
	GRAY,
	BLACK
};

int time;
int color[N];
int parent[N];
int d[N];
int f[N];

void create_graph(vNode* g, int n, int e) {
	int i = 0;
	int j = 0;
	int idx_from = 0;
	int idx_to = 0;
	eNode* p = NULL;
	eNode* q = NULL;

	for (i = 0; i < n; i++) {
		g[i].idx = i + 1;
		g[i].link = NULL;
	}

	for (j = 0; j < e; j++) {
		printf("[the %d edge]\n", j + 1);
		scanf("%d", &idx_from);
		printf("=>\n");
		scanf("%d", &idx_to);

		if (idx_from > n) {
			printf("bounds of the index!\n");
		}
		else {
			p = g[idx_from - 1].link;

			q = (eNode*)malloc(sizeof(eNode));
			q->idx = idx_to;
			q->next = p;
			g[idx_from - 1].link = q;
		}
	}
}

void dfs_visit(vNode* g, int u) {
	int v = 0;
	eNode* p = g[u-1].link;

	color[u - 1] = GRAY;
	time++;
	d[u - 1] = time;

	while (p != NULL) {
		v = p->idx;
		if (color[v - 1] == WHITE) {
			parent[v - 1] = u;
			dfs_visit(g, v);
		}
		p = p->next;
	}

	color[u - 1] = BLACK;
	time++;
	f[u - 1] = time;
}

void dfs(vNode* g, int n) {
	time = 0;

	for (int i = 0; i < n; i++) {
		color[i] = WHITE;
		parent[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == WHITE) {
			dfs_visit(g, g[i].idx);
		}
	}
}

int main(int argc, char** argv) {
	int n = 0;
	int e = 0;
	vNode adjlist[N];

	printf("please input the quantity of verteex and edges:");
	scanf("%d %d", &n, &e);

	create_graph(adjlist, n, e);
	dfs(adjlist, n);

	return 0;
}