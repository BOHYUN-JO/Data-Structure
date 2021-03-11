#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1


typedef struct {
	short int vert;
	short int horiz;
}offsets;

offsets move[8] = { -1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1 };

typedef struct {
	int row;
	int col;
	int dir;
}element;

element stack[MAX_STACK_SIZE];

int top = -1;
int size = 0;

element pop()
{
	size--;
	return stack[top--];
}

void push(element pos)
{
	size++;
	stack[++top].row = pos.row;
	stack[top].col = pos.col;
	stack[top].dir = pos.dir;
}

void path(int** mark, int** maze, int EXIT_ROW, int EXIT_COL)
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow < 0 || nextCol < 0)
			{
				++dir;
				continue;
			}
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!(maze[nextRow][nextCol]) && !(mark[nextRow][nextCol]))
			{
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found)
	{
		printf("The path is: \n");
		printf("row col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("-1");
}

int main()
{
	int i,j,m, p, EXIT_ROW, EXIT_COL;
	int idx = 0;
	int ret = 0;
	int arr[10000];
	FILE* fp = fopen("maze.txt", "r");
	while (1)
	{
		ret =fscanf(fp, "%d", &arr[idx++]);
		if (ret == EOF)
			break;
	}
	idx = 2;
	m = arr[0], p = arr[1];
	EXIT_ROW = m;
	EXIT_COL = p;
	int** maze = (int**)malloc(sizeof(int*)*(m+2));
	for (i = 0; i < m+2; i++)
		maze[i] = (int*)malloc(sizeof(int)*(p+2));

	int** mark = (int**)malloc(sizeof(int*)*(m+2));
	for (i = 0; i < m+2; i++)
		mark[i] = (int*)malloc(sizeof(int)*(p + 2));

	for (i = 0; i < m + 2; i++)
	{
		for (j = 0; j < p + 2; j++)
		{
			maze[i][j] = 1;
			mark[i][j] = 0;
		}
	}
	for (i = 1; i < m+1; i++)
	{
		for (j = 1; j < p + 1; j++)
			maze[i][j] = arr[idx++];
	}
	
	path(mark, maze, EXIT_ROW, EXIT_COL);

	fclose(fp);
	return 0;
}
