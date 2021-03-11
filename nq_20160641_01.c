#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void queens(int);
int promising(int);

int n;
int *col;

int main()
{
	printf("Input N: ");
	scanf("%d", &n);
	col = (int*)malloc(sizeof(int)*(n+1));
	queens(0);
	printf("No solution");
	
	return 0;
}

void printQueens()
{
	int i;
	for (i = 1; i <= n; i++)
		printf("%d ", col[i]);
	exit(1);
}

void queens(int i)
{
	int j;

	if (promising(i))
	{
		if (i == n)
		{
			printQueens();
			return;
		}
		else
		{
			for (j = 1; j <= n; j++)
			{
				col[i + 1] = j;
				queens(i + 1);
			}
		}
	}

}

int promising(int i)
{
	int k = 1;
	int flag = 1;
	while (k < i && promising)
	{
		if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k))
			flag = 0;
		k++;
	}
	return flag;
}
