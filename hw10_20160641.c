#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

void main()
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++)
		fscanf(fp, "%d", &A[i]);
	for (i = 0; i < n; i++)
		insert(&tree, A[i]);
	inorder(tree);
	printf("\n");
	preorder(tree);
	
}

void inorder(treePtr ptr)
{
	if (ptr)
	{
		inorder(ptr->lchild);
		printf("%d\n", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(treePtr ptr)
{
	if (ptr)
	{
		printf("%d\n", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void insert(treePtr*node, int num)
{
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) {
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if (*node)
		{
			if (num < temp->data) temp->lchild = ptr;
			else temp->rchild = ptr;
		}
		else *node = ptr;
	}
}

treePtr modifiedSearch(treePtr tree, int k)
{
	if (tree == NULL) return NULL;
	while (tree)
	{
		if (k == tree->data) return NULL;
		if (k < tree->data)
		{
			if (tree->lchild)
				tree = tree->lchild;
			else
				return tree;
		}
		else
		{
			if (tree->rchild)
				tree = tree->rchild;
			else
				return tree;
		}
	}
}


