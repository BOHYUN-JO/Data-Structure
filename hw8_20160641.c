#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
}entry_node;

typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		entry_node entry;
	} u;
}matrix_node;

matrix_pointer hdnode[MAX_SIZE];


matrix_pointer new_node();
matrix_pointer mread(FILE* fp, int*, int*);
void mwrite(matrix_pointer node, int, int);
void merase(matrix_pointer* node);
matrix_pointer msub(matrix_pointer, matrix_pointer, int, int);
matrix_pointer mtranspose(matrix_pointer, int, int);

void main()
{
	int rows, cols;
	
	matrix_pointer a, b, d;
	FILE* fp1 = fopen("A.txt", "r");
	FILE* fp2 = fopen("B.txt", "r");

	a = mread(fp1, &rows, &cols);
	b = mread(fp2, &cols, &cols);
	mwrite(a, rows, cols);
	mwrite(b, rows, cols);
	d = msub(a, b, rows, cols);
	mwrite(d, rows, cols);
	merase(&d);
	d = mtranspose(a, rows, cols);
	mwrite(d, cols, rows); /// transpose 한 결과를 나타내기 위해 rows와 cols가 바뀜
	merase(&d);
	merase(&a);
	merase(&b);
	mwrite(a, rows, cols);
	mwrite(b, rows, cols);
	mwrite(d, rows, cols);
	fclose(fp1);                                                        
	fclose(fp2);

	return 0;
}

matrix_pointer new_node()
{
	matrix_pointer newnode;
	newnode = (matrix_pointer)malloc(sizeof(matrix_node));

	return newnode;
}

matrix_pointer mread(FILE* fp, int* num_rows, int* num_cols)
{
	int num_terms, num_heads, i, j, ret, flag = 1;
	int row, col, value, current_row, data, cnt = 0;
	matrix_pointer temp, last, node;

	ret = fscanf(fp, "%d %d", num_rows, num_cols);
	num_heads = (*num_cols > *num_rows) ? *num_cols : *num_rows;
	node = new_node(); node->tag = entry;
	node->u.entry.row = *num_rows;
	node->u.entry.col = *num_cols;

	if (!num_heads) node->right = node;
	else {
		for (i = 0; i < num_heads; i++)
		{
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
		current_row = 0; last = hdnode[0];

		for (i = 0; i < *num_rows; i++)
		{
			for (j = 0; j < *num_cols; j++)
			{
				ret = fscanf(fp, "%d", &data);
				if (ret == EOF)
				{
					flag = 0;
					break;
				}
				if (data != 0)
				{
					row = i;
					col = j;
					value = data;
					cnt++;
					if (row > current_row)
					{
						last->right = hdnode[current_row];
						current_row = row; last = hdnode[row];
					}
					temp = new_node(); temp->tag = entry;
					temp->u.entry.row = row; temp->u.entry.col = col;
					temp->u.entry.value = value; last->right = temp; last = temp;
					hdnode[col]->u.next->down = temp;
					hdnode[col]->u.next = temp;
				}
				else continue;
			}
			if (flag == 0)
				break;
		}
		last->right = hdnode[current_row];
		for (i = 0; i < *num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}

	return node;
}

void mwrite(matrix_pointer node, int num_rows, int num_cols)
{
	int i, j;

	if (node == NULL)
	{
		printf("Matrix is empty! \n");
		return;
	}

	matrix_pointer temp, head = node->right;


	for (i = 0; i < num_rows; i++)
	{
		temp = head->right;
		for (j = 0; j < num_cols; j++)
		{
			if (j == temp->u.entry.col)
			{
				printf("%3d ", temp->u.entry.value);
				temp = temp->right;
			}
			else
				printf("%3d ", 0);
		}
		printf("\n");
		head = head->u.next;
	}
	printf("\n\n");

	
}

void merase(matrix_pointer* node)
{
	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;

	for (i = 0; i < (*node)->u.entry.row; i++)
	{
		y = head->right;
		while (y != head)
		{
			x = y;
			y = y->right;
			free(x);
		}
		x = head; head = head->u.next; free(x);
	}
	y = head;
	while (y != *node)
	{
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;
}

matrix_pointer msub(matrix_pointer a, matrix_pointer b, int num_rows, int num_cols)
{
	int i, j;
	FILE* fp = fopen("result.txt", "w");
	FILE* ret;
	matrix_pointer sub1, sub2, head1, head2, result;
	head1 = a->right;
	head2 = b->right;
	fprintf(fp, "%d %d\n", num_rows, num_cols);

	for (i = 0; i < num_rows; i++)
	{
		sub1 = head1->right;
		sub2 = head2->right;
		for (j = 0; j < num_cols; j++)
		{
			if (j == sub1->u.entry.col || j == sub2->u.entry.col)
			{
				if (j == sub1->u.entry.col && j != sub2->u.entry.col)
				{
					fprintf(fp, "%d ", sub1->u.entry.value);
					sub1 = sub1->right;
				}
				else if (j == sub1->u.entry.col && j == sub2->u.entry.col)
				{
					fprintf(fp, "%d ", sub1->u.entry.value - sub2->u.entry.value);
					sub1 = sub1->right;
					sub2 = sub2->right;
				}
				else
				{
					fprintf(fp, "%d ", 0 - sub2->u.entry.value);
					sub2 = sub2->right;
				}
			}
			else fprintf(fp, "0 ");
			
		}
		fprintf(fp,"\n");
		head1 = head1->u.next;
		head2 = head2->u.next;
	}
	fclose(fp);
	ret = fopen("result.txt", "r");
	result = mread(ret, &num_rows, &num_cols);

	fclose(ret);
	remove("result.txt");
	
	return result;
}
matrix_pointer mtranspose(matrix_pointer a, int num_rows, int num_cols)
{
	int i, j;
	matrix_pointer result, last;
	FILE* fp = fopen("result.txt", "w");
	FILE* ret;
	fprintf(fp, "%d %d\n", a->u.entry.col, a->u.entry.row);

	last = a->right;
	
	for (i = 0; i < num_cols; i++)
	{
		last = last->down;
		for (j = 0; j < num_rows; j++)
		{
			if (last == last->down)
				fprintf(fp, "%d ", 0);
			else {
				if (j == last->u.entry.row)
				{
					fprintf(fp, "%d ", last->u.entry.value);
					last = last->down;
				}
				else
					fprintf(fp, "%d ", 0);
			}
		}
		fprintf(fp, "\n");
		last = last->u.next;
	}

	fclose(fp);
	ret = fopen("result.txt", "r");
	result = mread(ret, &num_cols, &num_rows);

	fclose(ret);
	remove("result.txt");

	return result;
}
