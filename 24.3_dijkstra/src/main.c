#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define MAX 65536

typedef struct _eNode{
	int v_idx;
	int weight;
	struct _eNode* next;
}eNode;

typedef struct _vNode{
	int idx;
	int pre_idx;
	char data;
	int d;
	eNode* link;
}vNode;

typedef struct _item{
	int v_idx;
	int *key;
}item;

void create_graph(vNode* adjlist, int n, int e) {
	char ch, ch2;
	eNode *p, *q;
	int k, k2;
	int w = 0;

	for (int i = 0; i < n; i++) {
		printf("input a data of %d vertex:", i + 1);
		scanf(" %c", &adjlist[i].data);
		adjlist[i].idx = i + 1;
		adjlist[i].link = NULL;
	}

	for (int j = 0; j < e; j++) {
		printf("the %d edge:\n", j + 1);
		printf("start:");
		scanf(" %c", &ch);
		printf("=>\n");
		printf("end:");
		scanf(" %c", &ch2);
		printf("weight:");
		scanf("%d", &w);

		k = 0;
		while (k < n && adjlist[k].data != ch){
			k++;
		}

		k2 = 0;
		while (k2 < n && adjlist[k2].data != ch2) {
			k2++;
		}

		p = adjlist[k].link;
		q = (eNode*)malloc(sizeof(eNode));
		q->v_idx = adjlist[k2].idx;
		q->weight = w;
		q->next = p;
		adjlist[k].link = q;

		printf("\n");
	}
}

void travgraph(vNode* g, int n) {
	int i = 0;
	eNode* p = NULL;

	for (i = 0; i < n; i++) {
		printf("[%d, %c]", g[i].idx, g[i].data);
		p = g[i].link;
		while (p != NULL) {
			printf("(%d %d)", p->v_idx, p->weight);

			p = p->next;
		}

		printf("\n");
	}

	printf("\n");
}

void min_heapify(item* vec, int n, int i) {
	int left = 2 * i;
	int right = 2 * i + 1;
	int min = MAX;
	item tmp;

	if (left <= n && *(vec[left - 1].key) < *(vec[i - 1].key)) {
		min = left;
	}
	else {
		min = i;
	}

	if (right <= n && *(vec[right - 1].key) < *(vec[min - 1].key)) {
		min = right;
	}

	if (min != i) {
		memcpy(&tmp, &vec[i - 1], sizeof(item));
		memcpy(&vec[i - 1], &vec[min - 1], sizeof(item));
		memcpy(&vec[min - 1], &tmp, sizeof(item));

		min_heapify(vec, n, min);
	}
}

void build_min_heap(item* vec, int n) {
	for (int i = n / 2; i >= 1; i--) {
		min_heapify(vec, n, i);
	}
}

item extract_min(item* vec, int* n) {
	item key = vec[0];

	memcpy(&vec[0], &vec[*n - 1], sizeof(item));

	*n = *n - 1;

	min_heapify(vec, *n, 1);

	return key;
}

int get_parent(int i) {
	return i / 2;
}

void decrease_key(item* vec, int i) {
	int parent = 0;
	item tmp;

	while ((parent = get_parent(i)) && (*(vec[parent - 1].key) > *(vec[i - 1].key))){
		memcpy(&tmp, &vec[parent - 1], sizeof(item));
		memcpy(&vec[parent - 1], &vec[i - 1], sizeof(item));
		memcpy(&vec[i - 1], &tmp, sizeof(item));

		i = parent;
	}
}

void initialize_single_source(vNode* adjlist, item* vec, int n,char ch) {
	int i = 0;

	for (i = 0; i < n; i++) {
		adjlist[i].pre_idx = 0;

		if (adjlist[i].data == ch) {
			adjlist[i].d = 0;
		}
		else {
			adjlist[i].d = MAX;
		}

		vec[i].v_idx = adjlist[i].idx;
		vec[i].key = &adjlist[i].d;
	}
}

int relax(vNode* adjlist, int u, int v, int w) {
	if (adjlist[v - 1].d > adjlist[u - 1].d + w) {
		adjlist[v - 1].d = adjlist[u - 1].d + w;
		adjlist[v - 1].pre_idx = u;

		return 1;
	}

	return 0;
}

void dijkstra(vNode* adjlist, item* vec, int n, char s) {
	int *m = &n;
	int i = 0;
	item u;
	eNode* v = NULL;

	initialize_single_source(adjlist, vec, n, s);
	build_min_heap(vec, n);

	while (*m > 0) {
		u = extract_min(vec, m);
		printf("[fun dijkstra] (u_idx=%d data=%c), d=%d \n", u.v_idx, adjlist[u.v_idx - 1].data, *(u.key));

		v = adjlist[u.v_idx - 1].link;
		while (v != NULL) {
			i = 0;
			while (i < *m && vec[i].v_idx != v->v_idx) {
				i++;
			}

			if (relax(adjlist, u.v_idx, v->v_idx, v->weight) == 1) {
				decrease_key(vec, i + 1);

			}

			v = v->next;
		}
	}
}

void print_path(vNode* adjlist, int u_idx, int v_idx) {
	if (u_idx == v_idx) {
		printf("(%c %d) ", adjlist[u_idx - 1].data, adjlist[u_idx - 1].d);
	}
	else if (adjlist[v_idx - 1].d == 0) {
		printf("no patch from %c to %c", adjlist[u_idx - 1].data, adjlist[v_idx - 1].data);
	}
	else {
		print_path(adjlist, u_idx, adjlist[v_idx - 1].pre_idx);
		printf("(%c %d) ", adjlist[v_idx - 1].data, adjlist[v_idx - 1].d);
	}
}

int main(int argc, char** argv) {
	int n, e;
	vNode adjlist[N];
	item vInfos[N];
	char ch = 0;

	memset(adjlist, 0, sizeof(adjlist));
	memset(vInfos, 0, sizeof(vInfos));

	printf("input n and e:");
	scanf("%d %d", &n, &e);
	create_graph(adjlist, n, e);
	travgraph(adjlist, n);

	printf("input the start point:");
	scanf(" %c", &ch);
	dijkstra(adjlist, vInfos, n, ch);

	for (int i = 1; i <= n; i++) {
		print_path(adjlist, 1, i);
		printf("\n");
	}
	return 0;
}