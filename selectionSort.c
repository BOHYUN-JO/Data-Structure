#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)= (y), (y)=(t))

void sort(int* list, int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		SWAP(list[i], list[min], temp);
	}
}

int main()
{
	int num,i;
	int* arr;
	int a[1001];
	int n, step =10;
	clock_t start;
	double duration;

	printf("Input data size: ");
	scanf("%d", &num);
	
	arr = (int*)malloc(sizeof(int) * num);
	for (i = 0; i < num; i++)
	{
		printf("Input: ");
		scanf("%d", &arr[i]);
	}
	sort(arr, num);
	printf("Sorted: ");
	for (i = 0; i < num ;i++)
		printf("%d ", arr[i]);
	printf("\n"); 
	
	printf("%Data Size  Repetitions   Duration\n");
	for(n=0; n <=1000; n+=step)
	{
		long repet =0;
		start = clock();
		do
		{
			repet++;
			for(i=0; i<n; i++)
				a[i] = n - i;
			sort(a,n);
		}while(clock() - start <1000);
		duration = ((double)(clock() - start))/(CLOCKS_PER_SEC);
		duration /= repet;
		printf("  %6d     %9d   %f\n", n, repet, duration);
		if(n==100) step =100;
	}
	
	free(arr);
	return 0;
}
