#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
void delete(treePtr*, int);
void rangeSearch(treePtr, int, int);
int count(treePtr);

void main()
{
	clock_t start_time = clock();
	int i, j,n,m, A[MAX_TERMS], D[MAX_TERMS], k1, k2;
	treePtr tree = NULL;
	FILE* fp = fopen("input2.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < 100000; i++)
		insert(&tree, i);
	printf("%lf\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	return 0;

}

void inorder(treePtr ptr)
{
	if (ptr)
	{
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(treePtr ptr)
{
	if (ptr)
	{
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void insert(treePtr* node, int num)
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

void delete(treePtr* tree, int target)
{
	int Lcnt, Rcnt;
	treePtr del_parent, del_child, del, suc, suc_parent;
	del_parent = NULL;
	del = *tree;
	
	while (del != NULL && del->data != target)
	{
		del_parent = del;
		del = (target < del_parent->data) ? del_parent->lchild : del_parent->rchild;
	}

	if (del == NULL)
	{
		printf("Nothing to delete\n");
		return;
	}
	
	if (del->lchild == NULL && del->rchild == NULL)
	{
		if (del_parent)
		{
			if (del_parent->lchild == del)
				del_parent->lchild = NULL;
			else
				del_parent->rchild = NULL;
		}
		else *tree = NULL;
	}
	else if ((del->lchild == NULL) || (del->rchild == NULL))
	{
		del_child = del->lchild != NULL ? del->lchild : del->rchild;
		if (del_parent)
		{
			if (del_parent->lchild == del)
				del_parent->lchild = del_child;
			else
				del_parent->rchild = del_child;
		}
		else *tree = del_child;
	}
	else
	{
		suc_parent = del;
		Lcnt = count(del->lchild);
		Rcnt = count(del->rchild);
		if (Lcnt < Rcnt)
		{
			suc = del->rchild;
			while (suc->lchild != NULL)
			{
				suc_parent = suc;
				suc = suc->lchild;
			}
			if (suc_parent->lchild == suc)
				suc_parent->lchild = suc->rchild;
			else 
				suc_parent->rchild = suc->rchild;

			del->data = suc->data;
			del = suc;
		}
		else if (Lcnt > Rcnt)
		{
			suc = del->lchild;
			while (suc->rchild != NULL)
			{
				suc_parent = suc;
				suc = suc->rchild;
			}
			if (suc_parent->rchild == suc)
				suc_parent->rchild = suc->lchild;
			else
				suc_parent->lchild = suc->lchild;
			
			del->data = suc->data;
			del = suc;
		}
		else
		{
			int random;
			srand(time(NULL));
			random = rand() % 10;
			if (random < 5)
			{
				suc = del->rchild;
				while (suc->lchild != NULL)
				{
					suc_parent = suc;
					suc = suc->lchild;
				}
				if (suc_parent->lchild == suc)
					suc_parent->lchild = suc->rchild;
				else
					suc_parent->rchild = suc->rchild;

				del->data = suc->data;
				del = suc;
			}
			else
			{
				suc = del->lchild;
				while (suc->rchild != NULL)
				{
					suc_parent = suc;
					suc = suc->rchild;
				}
				if (suc_parent->rchild == suc)
					suc_parent->rchild = suc->lchild;
				else
					suc_parent->lchild = suc->lchild;

				del->data = suc->data;
				del = suc;
			}
		}
	}
	free(del);
}

int count(treePtr tree)
{
	if (!tree)
		return 0;
	else
		return count(tree->lchild) + count(tree->rchild) + 1;
}

void rangeSearch(treePtr tree, int k1, int k2)
{
	if (tree)
	{
		rangeSearch(tree->lchild, k1, k2);
		if (tree->data >= k1 && tree->data <= k2)
			printf("%d ", tree->data);
		rangeSearch(tree->rchild, k1, k2);
	}
}
