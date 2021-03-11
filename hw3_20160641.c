#include <stdio.h>

#define MAX_TERMS 100
int avail = 0;
int i = 0;

typedef struct {
	int expon;
	float coef;
} poly;

poly terms[MAX_TERMS];

void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS) {
		printf("Too many terms in the polynomial");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}
int Compare(int a, int b)
{
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else return -1;
}

void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	float coefficient;
	*startd = avail;
	while(starta <= finisha && startb <= finishb)
		switch (Compare(terms[starta].expon, terms[startb].expon))
		{
		case -1:
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0:
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1:
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishd = avail - 1;
}

void readPoly(FILE* fp)
{
	int ret;
	while(1)
	{
		ret = fscanf(fp,"%f %d", &(terms[i].coef), &(terms[i].expon));
		i++;
		if(ret==EOF)
			break;
	}
}

void printfPoly(int startd, int finishd)
{
	for(; startd<=finishd; startd++)
	{
		if(startd==finishd)
			printf("(%.0f,%d)", terms[startd].coef, terms[startd].expon);
		else
			printf(" (%.0f,%d), ", terms[startd].coef, terms[startd].expon); 
	}
}

int main()
{
	int starta,finisha,startb,finishb;
	int startd=0; int finishd=0;
	int* pstartd= &startd;
	int* pfinishd = &finishd;
	FILE* fpa = fopen("A.txt", "r");
	FILE* fpb = fopen("B.txt", "r");
	if(fpa== NULL || fpb==NULL)
	{
		printf("Error!");
		return 1;
	}
	starta = 0;
	readPoly(fpa);
	finisha = i-2;
	startb = i;
	readPoly(fpb);
	finishb = i-2;

	avail = i;
	
	padd(starta, finisha,startb,finishb,pstartd,pfinishd);
	printfPoly(startd,finishd);
	
	
	fclose(fpa);
	fclose(fpb);
	return 0;	
	
}
