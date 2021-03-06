#include <stdio.h>
#include <string.h>
#define MAX_STR_SIZE 100
#define MAX_PAT_SIZE 100

int failure[MAX_PAT_SIZE];
char string[MAX_STR_SIZE];
char pat[MAX_PAT_SIZE];

void fail(char* pat)
{
	int i,j, n = strlen(pat);
	failure[0] = -1;
	for(j=1; j<n; j++)
	{
		i= failure[j-1];
		while((pat[j]!= pat[i+1]) && (i>=0))
			i = failure[i];
		if(pat[j] == pat[i+1])
			failure[j] = i+1;
		else failure[j] = -1;
	}
}

int pmatch(char* string, char* pat)
{
	int i =0, j=0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while(i<lens && j<lenp)
	{
		if(string[i]==pat[j])
		{
			i++;
			j++;
		}
		else if(j==0) i++;
		else j = failure[j-1] +1;
	}
	return ((j==lenp) ? (i-lenp) : -1);
}

int main()
{
	int i,loc=0;
	scanf("%s", pat);
	fail(pat);
	for(i=0; i<strlen(pat); i++)
	{
		printf("%d ", failure[i]);
	}
	return 0;
}
