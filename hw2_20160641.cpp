#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SequentialSearch(int arr[], int len, int target)
{
	int i;
	int flag = -1;
	for(i=0; i<len; i++)
	{
		if(arr[i] == target)
		{
			flag =1;
			printf("Searched(index) : %d\n", i);
			break;
		}
	}
	return flag;
}

int main()
{
	int i,n,flag, len, target, step =10;
	int*a = (int*)malloc(sizeof(int)*1000000);
	clock_t start;
	double duration;
	printf("Input data length: ");
	scanf("%d", &len);
	printf("Search number : ");
	scanf("%d", &target);
	int* arr = (int*)malloc(sizeof(int)*len);
	for(i=0; i<len; i++)
	{
		arr[i] = i;
	}
	printf("\n\nInput data length: %d\n",len);
	printf("Search number : %d\n", target);
	start = clock();
	flag = SequentialSearch(arr, len, target);
	duration = (double)(clock() - start)/(CLOCKS_PER_SEC);
	if(flag == -1) printf("Searched : -1\n");
	printf("Time : %.6f\n", duration);
	target = -1;
	printf("%Data Size  Repetitions   Duration\n");
	for(n=0; n <=1000000; n+=step)
	{
		long repet =0;
		start = clock();
		do
		{
			repet++;
			for(i=0; i<n; i++)
				a[i] = i;
			SequentialSearch(a, n, target);
		}while(clock() - start <1000);
		duration = ((double)(clock() - start))/(CLOCKS_PER_SEC);
		duration /= repet;
		printf("  %7d     %9d   %f\n", n, repet, duration);
		if(n==10) step =40;
		else if(n==50) step =50;
		else if(n==100) step =400;
		else if(n==500) step=500;
		else if(n==1000) step = 4000;
		else if(n==5000) step = 5000;
		else if(n==10000) step = 90000;
		else if(n==100000) step = 900000;
		
	}
	free(a);
	free(arr);
	return 0;
	
}
