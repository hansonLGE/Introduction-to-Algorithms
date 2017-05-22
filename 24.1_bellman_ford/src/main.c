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
	char data;
	eNode* link;
}vNode;

typedef struct _vInfo{
	int d[N];
	int pre[N];
}vInfo;

void create_graph(vNode* adjlist, int n, int e) {
	char ch, ch2;
	eNode *p, *q;
	int w = 0;
	int k, k2;

	for (int i = 0; i < n; i++) {
		printf("input a data of %d vertex:", i + 1);
		scanf(" %c", &adjlist[i].data);
		adjlist[i].idx = i + 1;
		adjlist[i].link = NULL;
	}

	for (int j = 0; j < e; j++) {
		printf("the %d edge:\n", j+1);
		printf("start vertex:");
		scanf(" %c", &ch);
		printf("=>\n");
		printf("end vertex:");
		scanf(" %c", &ch2);
		printf("weight:");
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

void initialize_single_source(vNode* adjlist, vInfo* p_info, int n, char s) {
	int i = 0;

	for (i = 0; i < n; i++) {
		p_info->d[i] = MAX;
		p_info->pre[i] = 0;
	}

	i = 0;
	while (i < n && adjlist[i].data != s) {
		i++;
	}

	p_info->d[i] = 0;
}

void relax(vInfo* p_info, int u_idx, int v_idx, int w) {
	if (p_info->d[v_idx - 1] > p_info->d[u_idx - 1] + w) {
		p_info->d[v_idx - 1] = p_info->d[u_idx - 1] + w;
		p_info->pre[v_idx - 1] = u_idx;
	}
}

int bellman_ford(vNode* adjlist, int n, vInfo* p_info, char s) {
	int j = 0;
	vNode u;
	eNode *v = NULL;

	initialize_single_source(adjlist, p_info, n, s);

	for (int i = 1; i <= n - 1; i++) {
		j = 0;
		while (j < n) {
			u = adjlist[j];
			v = u.link;
			while (v != NULL) {
				relax(p_info, u.idx, v->v_idx, v->weight);

				v = v->next;
			}

			j++;
		}
	}

	j = 0;
	while (j < n) {
		u = adjlist[j];
		v = u.link;
		while (v != NULL) {
			if (p_info->d[v->v_idx - 1] > p_info->d[u.idx - 1] + v->weight) {
				return 0;
			}

			v = v->next;
		}

		j++;
	}

	return 1;
}

void print_path(vNode* adjlist, vInfo* p_info, int u_idx, int v_idx) {
	if (u_idx == v_idx) {
		printf("(%c %d) ", adjlist[u_idx-1].data, p_info->d[u_idx-1]);
	}
	else if (p_info->pre[v_idx - 1] == 0) {
		printf("no patch from %c to %c", adjlist[u_idx - 1].data, adjlist[v_idx-1].data);
	}
	else {
		print_path(adjlist, p_info, u_idx, p_info->pre[v_idx - 1]);
		printf("(%c %d) ", adjlist[v_idx-1].data, p_info->d[v_idx-1]);
	}
}

int main(int argc, char** argv) {
	int n = 0;
	int e = 0;
	vNode adjlist[N];
	vInfo m_vInfo;
	char ch = 0;

	memset(adjlist, 0, sizeof(adjlist));
	memset(&m_vInfo, 0, sizeof(vInfo));

	printf("input n and e:");
	scanf("%d %d", &n, &e);

	create_graph(adjlist, n, e);
	travgraph(adjlist, n);

	printf("input the start point:");
	scanf(" %c", &ch);
	if (bellman_ford(adjlist, n, &m_vInfo, ch) == 1) {
		for (int i = 1; i <= n; i++) {
			print_path(adjlist, &m_vInfo, 1, i);
			printf("\n");
		}
	}
	else {
		printf("negative weight loop exist!\n");
	}

	return 0;
}