#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 100

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

char expr[MAX_EXPR_SIZE];

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef struct _node
{
	precedence data;
	struct _node* next;
}Node;

typedef struct _stack
{
	Node* top;
}stack;


void init(stack* pstack)
{
	pstack->top = NULL;
}

void push(stack* pstack, precedence p)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = p;
	newnode->next = pstack->top;
	pstack->top = newnode;
}

precedence pop(stack* pstack)
{
	precedence temp;
	Node* tempnode;

	if (pstack->top == NULL)
		return;
	temp = pstack->top->data;
	tempnode = pstack->top;
	pstack->top = pstack->top->next;
	free(tempnode);

	return temp;
}
void printToken(precedence a)
{
	switch (a)
	{
	case plus: printf("+"); return;
	case minus: printf("-"); return;
	case divide: printf("/"); return;
	case times: printf("*"); return;
	case mod: printf("\%"); return;
	default: return;
	}
}
precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return eos;
	case '\0': return eos;
	default: return operand;
		break;
	}
}

void postfix(stack* pstack)
{
	precedence token;
	char symbol;
	int n = 0;
	push(pstack, eos);
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
			printf("%c", symbol);
		else if (token == rparen)
		{
			while (pstack->top->data != lparen)
				printToken(pop(pstack));
			pop(pstack);
		}
		else {
			if (pstack->top == NULL)
			{
				push(pstack, token);
				continue;
			}
			while (isp[pstack->top->data] >= icp[token])
				printToken(pop(pstack));
			push(pstack, token);
		}
	}
		while ((token = pop(pstack)) != eos)
			printToken(token);
		printf("\n");
	
}



void rExpr(FILE* fp)
{
	char temp;
	int ret,i = 0;
	while (1)
	{
		ret=fscanf(fp,"%c", &temp);
		if (temp == ' ')
			continue;
		else if (ret == EOF)
			return;
		else expr[i++] = temp;
	}
}


int main()
{
	FILE* fp = fopen("expr.txt", "r");
	stack stack1;
	init(&stack1);
	rExpr(fp);
	postfix(&stack1);
	
	return 0;

}