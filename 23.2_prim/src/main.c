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
	int parent_idx;
	char data;
	eNode* link;
}vNode;

typedef struct _item{
	int v_idx;
	int key;
}item;

void create_graph(vNode* adjlist, int n, int e) {
	char ch, ch2;
	int w;
	int k, k2;
	eNode* p, *q;

	for (int i = 0; i < n; i++) {
		adjlist[i].idx = i + 1;
		adjlist[i].link = NULL;
		printf("input a data of %d vertes:", i + 1);
		scanf(" %c", &adjlist[i].data);
	}

	for (int j = 0; j < e; j++) {
		printf("the %d edge:\n", j + 1);
		printf("start vertex:");
		scanf(" %c", &ch);
		printf("=>\n");
		printf("end vertex:");
		scanf(" %c", &ch2);
		printf("the weight of the edge is:");
		scanf("%d", &w);

		k = 0;
		while (k < n && adjlist[k].data != ch) {
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

		p = adjlist[k2].link;
		q = (eNode*)malloc(sizeof(eNode));
		q->v_idx = adjlist[k].idx;
		q->weight = w;
		q->next = p;
		adjlist[k2].link = q;

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

void init_priority_queue(vNode* g, item* items, int n, char ch) {
	for (int i = 0; i < n; i++) {
		g[i].parent_idx = 0;
		items[i].v_idx = g[i].idx;
		if (g[i].data == ch) {
			items[i].key = 0;
		}
		else {
			items[i].key = MAX;
		}
	}
}

void min_heapify(item* vec, int n, int i) {
	//printf("[fun min_heapify] n=%d, i=%d\n", n, i);
	int left = 2 * i;
	int right = 2 * i + 1;
	int min = MAX;
	item tmp;

	if (left <= n && vec[left - 1].key < vec[i - 1].key){
		min = left;
	}
	else {
		min = i;
	}

	if (right <= n && vec[right - 1].key < vec[min -1].key){
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
	item u = vec[0];

	memcpy(&vec[0], &vec[*n - 1], sizeof(item));

	*n = *n - 1;
	min_heapify(vec, *n, 1);

	return u;
}

int get_parent(int i) {
	return i / 2;
}

void decrease_key(item* vec, int* n, int i) {
	int parent = 0;
	item tmp;

	while ((parent = get_parent(i)) && (vec[parent - 1].key > vec[i - 1].key)) {
		memcpy(&tmp, &vec[parent - 1], sizeof(item));
		memcpy(&vec[parent - 1], &vec[i - 1], sizeof(item));
		memcpy(&vec[i - 1], &tmp, sizeof(item));

		i = parent;
	}
}

void mst_prim(vNode* adjlist, item* vec, int n, char ch) {
	int *m = &n;
	int i = 0;
	item u;
	eNode* v = NULL;

	init_priority_queue(adjlist, vec, n, ch);
	build_min_heap(vec, n);

	while (*m > 0) {
		u = extract_min(vec, m);
		printf("[fun mst_prim] u_idx=%d, m=%d \n", u.v_idx, *m);

		v = adjlist[u.v_idx - 1].link;
		while (v != NULL) {
			i = 0;
			while (i < *m && vec[i].v_idx != v->v_idx) {
				i++;
			}

			if (i < *m && v->weight < vec[i].key) {
				adjlist[v->v_idx - 1].parent_idx = u.v_idx;
				vec[i].key = v->weight;

				decrease_key(vec, m, i + 1);
			}
			
			v = v->next;
		}
	}
}

void output_mst_patch(vNode* adjlist, int n) {
	for (int i = 0; i < n; i++){
		if (adjlist[i].parent_idx != 0) {
			printf("(%d %d) ", adjlist[i].idx, adjlist[i].parent_idx);
		}
	}
	printf("\n");
}

int main(int argc, char** argv) {
	int n = 0;
	int e = 0;
	vNode adjlist[N];
	item items[N];
	char ch;

	memset(adjlist, 0, sizeof(adjlist));
	memset(items, 0, sizeof(items));
	printf("input the n and e:");
	scanf("%d %d", &n, &e);

	create_graph(adjlist, n, e);
	travgraph(adjlist, n);

	printf("input data of the vertex that finding a mst from it:");
	scanf(" %c", &ch);

	mst_prim(adjlist, items, n, ch);
	output_mst_patch(adjlist, n);

	return 0;
}