#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 100

typedef struct _node{
	int idx;
} node;

typedef struct _graph{
	node vexs[N];
	int edges[N][N];
}graph;

typedef struct _stack{
	int s[N];
	int top;
}stack;

void create_graph(graph* g, int n, int e) {
	int idx_from = 0;
	int idx_to = 0;

	for (int i = 0; i < n; i++) {
		g->vexs[i].idx = i + 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g->edges[i][j] = 0;
		}
	}

	for (int j = 0; j < e; j++) {
		printf("the %d edge =>\n", j+1);
		printf("start:");
		scanf("%d", &idx_from);
		printf("end:");
		scanf("%d", &idx_to);

		if (idx_from <= n && idx_to <= n) {
			g->edges[idx_from-1][idx_to-1] = 1;
			g->edges[idx_to - 1][idx_from - 1] = 1;
		}
	}
}

int is_eular_graph(graph* g, int n) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		count = 0;
		for (int j = 0; j < n; j++) {
			if (g->edges[i][j] == 1) {
				count++;
			}
		}

		if (count % 2 != 0) {
			return 0;
		}
	}

	return 1;
}

int is_full(stack* s) {
	if (s->top == N) {
		return 1;
	}

	return 0;
}

int is_empty(stack* s){
	if (s->top == 0) {
		return 1;
	}

	return 0;
}

void push(stack* s, int idx) {
	if (!is_full(s)){
		s->top++;
		s->s[s->top] = idx;
	}
}

int top(stack* s){
	if (!is_empty(s)){
		return s->s[s->top];
	}

	return 0;
}

void pop(stack* s) {
	if (!is_empty(s)) {
		s->top--;
	}
}

void dfs(graph* g, stack* s, int u, int n) {
	int v = 0;
	push(s, u);

	for (v = 1; v <= n; v++) {
		if (g->edges[u - 1][v - 1] == 1) {
			g->edges[u - 1][v - 1] = 0;
			g->edges[v - 1][u - 1] = 0;
			dfs(g, s, v, n);
			break;
		}
	}
}

void fleury(graph* g, int ss, int n) {
	int u = 0;
	int v = 0;
	int bridge = 0;
	stack s;
	memset(&s, 0, sizeof(stack));

	push(&s, ss);

	while (!is_empty(&s)){
		bridge = 1;
		u = top(&s);
		pop(&s);
		for (v = 1; v <= n; v++){
			if (g->edges[u - 1][v-1] == 1) {
				bridge = 0;
				break;
			}
		}

		if (bridge == 0) {
			dfs(g, &s, u, n);
		}
		else {
			printf("%d ", u);
		}
	}
}

int main(int argc, char** argv) {
	graph m_graph;
	memset(&m_graph, 0, sizeof(graph));

	int n = 0;
	int e = 0;

	printf("input the count of nodes(n) and edges(e):");
	scanf("%d %d", &n, &e);

	create_graph(&m_graph, n, e);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", m_graph.edges[i][j]);
		}

		printf("\n");
	}
	printf("\n");

	if (is_eular_graph(&m_graph, n)){
		fleury(&m_graph, 1, n);
		printf("\n");
	}
	else {
		printf("It is not a eular circuit.\n");
	}

	return 0;
}