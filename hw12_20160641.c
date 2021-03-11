#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y)  ? (x) : (y) )
#define FALSE 0
#define TRUE 1

short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
short int visited[MAX_VERTICES];
int num,n;

typedef struct graphNode* nodePointer;
typedef struct graphNode{
	int vertex;
	nodePointer link;
}graphNode;

typedef struct stackNode* stackPointer;
typedef struct stackNode{
	int vertex1;
	int vertex2;
	stackPointer prev;
}stackNode;

nodePointer graph[MAX_VERTICES];
stackPointer top;

void init();
void bicon(int, int);
void makeGraph(int, int);
void push(int, int);
void pop(int*, int*);

void main()
{
	int i,j,ver, adj,flag;
	char str[30];
	nodePointer ptr;
	FILE* fp;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	j = 0;
	flag = 0;
	for (i = 0; i < n; i++)
	{
		fgets(str, 30, fp);
		while (1)
		{
			if (str[j] == '\n')
				break;
			else if (str[j] <= '9' && str[j] >= '0')
			{
				if (flag == 0)
				{
					ver = str[j] - '0';
					flag = 1;
					j++;
					continue;
				}
				adj = str[j] - '0';
				makeGraph(ver, adj);
			}
			else {
				j++;
				continue;
			}
			j++;
		}
		flag = 0;
		j = 0;
	}
	
	init();
	bicon(3, -1);

	return 0;
}

void init()
{
	int i;
	for (i = 0; i < n; i++)
	{
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

void bicon(int u, int v)
{
	nodePointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link)
	{
		w = ptr->vertex;
		if (v != w && dfn[w] < dfn[u])
		{
			push(u, w);
			if (dfn[w] < 0)
				bicon(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u])
			{
				printf("New biconnected component: ");
				do {
					pop(&x, &y);
					printf(" <%d,%d>", x, y);
				} while (!((x == u) && (y == w)));
				printf("\n");
			}
		}
		else if (w != v)	low[u] = MIN2(low[u], dfn[w]);
	}
}


void makeGraph(int ver, int adj)
{
	nodePointer temp, ptr;
	temp = (nodePointer)malloc(sizeof(graphNode));
	temp->vertex = adj;
	temp->link = NULL;
	ptr = graph[ver];
	if (ptr == NULL)
		graph[ver] = temp;
	else
	{
		while (1)
		{
			if (ptr->link == NULL)
				break;
			else ptr = ptr->link;
		}
		ptr->link = temp;
	}
}

void push(int ver1, int ver2)
{
	stackPointer temp, ptr;
	ptr = top;
	temp = (stackPointer)malloc(sizeof(stackNode));
	temp->vertex1 = ver1;
	temp->vertex2 = ver2;
	if (ptr == NULL)
		top = temp;
	else
	{
		temp->prev = top;
		top = temp;
	}
	
}

void pop(int* ver1, int* ver2)
{
	stackPointer temp;
	temp = top;
	if (temp == NULL)
		return;
	else
	{
		*ver1 = temp->vertex1;
		*ver2 = temp->vertex2;
		top = temp->prev;
		free(temp);
	}
}