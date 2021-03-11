#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

void construct_tree(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insert(threadedPointer s, char data);

int main()
{ 
	threadedPointer root = (threadedPointer)malloc(sizeof(threadedTree));
	root->rightChild = root;
	root->leftChild = root;
	root->leftThread = root->rightThread = FALSE;
	/* construct a given tree */
	construct_tree(root);
	insert(root->leftChild->rightChild, 'E');
	insert(root->leftChild->leftChild->rightChild, 'F');
	insert(root->leftChild->leftChild, 'G');
	tinorder(root);
	return 0;
}

void construct_tree(threadedPointer tree)
{
	threadedPointer temp, temp_root;

	temp_root = tree;
	/* insert node 'A' to the left of the head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = TRUE;
	temp->leftChild = temp->rightChild = temp;
	temp->data = 'A';

	temp_root->leftChild = temp;
	temp_root->leftThread = FALSE;

	temp_root = tree->leftChild;
	/* insert node 'B' to the left of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightThread = temp->leftThread = TRUE;
	temp->leftChild = tree;
	temp->rightChild = temp;
	temp->data = 'B';

	temp_root->leftChild = temp;
	temp_root->leftThread = FALSE;

	/* insert node 'C' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = TRUE;
	temp->leftChild = temp_root;
	temp->rightChild = tree;
	temp->data = 'C';

	temp_root->rightChild = temp;
	temp_root->rightThread = FALSE;

	temp_root = temp_root->leftChild;
	/* insert node 'D' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = TRUE;
	temp->leftChild = temp_root;
	temp->rightChild = tree->leftChild;
	temp->data = 'D';

	temp_root->rightChild = temp;
	temp_root->rightThread = FALSE;
}

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;
}

void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (;;)
	{
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}

void insert(threadedPointer s, char data)
{
	threadedPointer temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = data;
	insertRight(s, temp);

}

void insertRight(threadedPointer s, threadedPointer r)
{
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = TRUE;
	s->rightChild = r;
	s->rightThread = FALSE;
	if (!r->rightThread)
	{
		temp = insucc(r);
		temp->leftChild = r;
	}

}