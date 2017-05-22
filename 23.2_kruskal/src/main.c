#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct _eNode{
	int v_index;
	int weight;
	struct _eNode* next;
}eNode;

typedef struct _vNode{
	int index;
	int tree_index;
	char data;
	eNode* link;
}vNode;

typedef struct _edges{
	int index;
	int weight;
	int v1_index;
	int v2_index;
}edges;

void create_graph(vNode* adjlist, int n, int e, edges* edgesa) {
	int i = 0;
	int j = 0;
	int k = 0;
	int w = 0;
	char ch = 0;
	char ch2 = 0;
	edges m_edge;
	eNode* p = 0;
	eNode* q = 0;

	printf("[create all vertexes]\n");
	for (i = 0; i < n; i++){
		printf("input the data of a vertex:");
		scanf(" %c", &ch);
		adjlist[i].index = i + 1;
		adjlist[i].tree_index = i + 1;
		adjlist[i].data = ch;
		adjlist[i].link = NULL;
	}

	printf("[create all edges]\n");
	for (k = 0; k < e; k++){
		printf("the %d edge:\n", k+1);
		printf("start vertex:");
		scanf(" %c", &ch);
		printf("=>\n");
		printf("end vertex:");
		scanf(" %c", &ch2);
		printf("the weight of the edge is:");
		scanf("%d", &w);

		i = 0;
		while (i < n && adjlist[i].data != ch){
			i++;
		}

		j = 0;
		while (j < n && adjlist[j].data != ch2){
			j++;
		}

		p = adjlist[i].link;
		q = (eNode*)malloc(sizeof(eNode));

		q->v_index = j + 1;
		q->weight = w;
		q->next = p;
		adjlist[i].link = q;

		p = adjlist[j].link;
		q = (eNode*)malloc(sizeof(eNode));
		q->v_index = i + 1;
		q->weight = w;
		q->next = p;
		adjlist[j].link = q;

		m_edge.index = k + 1;
		m_edge.weight = w;
		m_edge.v1_index = i + 1;
		m_edge.v2_index = j + 1;
		edgesa[k] = m_edge;
	}
}

void quick_sort(edges* edgesa, int left, int right) {
	int i = left;
	int j = right;
	edges key;

	if (left < right) {
		key = edgesa[left];

		while (i < j) {
			while (i < j && edgesa[j].weight >= key.weight) {
				j--;
			}
			if (i < j) {
				edgesa[i] = edgesa[j];
				i++;
			}

			while (i < j && edgesa[i].weight <= key.weight) {
				i++;
			}
			if (i < j) {
				edgesa[j] = edgesa[i];
				j--;
			}
		}

		edgesa[i] = key;
		quick_sort(edgesa, left, i - 1);
		quick_sort(edgesa, i + 1, right);
	}
}

void mst_kruskal(vNode* adjlist, int n, int e, edges* edgesa, int* aSet) {
	edges m_edge;
	int j = 0;
	int k = 0;
	vNode u, v;

	quick_sort(edgesa, 0, e - 1);

	for (int i = 0; i < e; i++) {
		m_edge = edgesa[i];
		u = adjlist[m_edge.v1_index-1];
		v = adjlist[m_edge.v2_index-1];

		if (u.tree_index != v.tree_index) {
			aSet[i] = m_edge.index;
			adjlist[v.index - 1].tree_index = u.tree_index;
			printf("%c <--> %c\n", u.data, v.data);
		}
	}
}

int main(int argc, char** argv) {
	int n = 0;
	int e = 0;
	vNode adglist[N];
	edges edges[N];
	int aSet[N] = { 0 };

	memset(adglist, 0, sizeof(adglist));
	memset(edges, 0, sizeof(edges));

	printf("input the n and e:");
	scanf("%d %d", &n, &e);

	create_graph(adglist, n, e, edges);
	mst_kruskal(adglist, n, e, edges, aSet);


	return 0;
}