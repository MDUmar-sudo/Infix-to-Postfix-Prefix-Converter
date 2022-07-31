#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define repeat(n) for(int i=0;i<n;i++)
#define max 100

typedef struct Stack ss;

struct Stack{
    int size;
    int top;
    char *arr;
};

//return stack status: Empty or Not

int isEmpty(ss *s){

    if(s->top==-1) return 1;

    return 0;
}

//return stack status: Full or Not

int isFull(ss *s){

    if(s->top==s->size-1) return 1;

    return 0;
}

//push() function append an element at the top most position in the stack

void push(char x, ss *s)
{
    if(isFull(s))
    {
        printf("\nSTACK FULL\n");
    }
    else
    {
        s->arr[++s->top]=x;
    }

}

//pop() function deletes the top most element in the stack

void pop(ss *s)
{
    if(isEmpty(s))
    {
        printf("\nSTACK EMPTY\n");
    }
    else
    {
        s->arr[s->top--];
    }
}

void InfixToPostfix();
void InfixToPrefix();


int main()
{
    ss *s = (ss *)malloc(sizeof(ss));
    s->size=100;
    s->top=-1;
    s->arr = (char *)malloc(s->size*sizeof(char));
	char infix[max];

    repeat(50)
    printf("=");
	printf("\nENTER INFIX EXPRESSION : ");
    scanf("%s",infix);
	printf("\n");
	repeat(50)
    printf("=");

    int choice;
    printf("\n");
	repeat(50)
    printf("-");
    printf("\nCHOOSE A CONVERSION\n\n(1)POSTFIX\n\n(2)PREFIX\n");
    printf("\n\nCHOOSE A OPTION : ");
    scanf("%d",&choice);
    printf("\n");
	repeat(50)
    printf("-");

    switch(choice){
        case 1: {
                    InfixToPostfix(infix,s);
                    break;

                }

        case 2: {
                    strrev(infix);
                    InfixToPrefix(infix,s);
                    break;

                }
        default: printf("WRONG OPTION!!!");
                 exit(0);

    }



    getchar();
	return 0;

}

//checks if the given character is an operator or operand

int is_operator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	return 0;
}

/*
define function that is used to assign precedence to operator.
In this function we assume that higher integer value means higher precedence.
*/

int precedence(char symbol)
{
	if(symbol == '^')/* exponent operator, highest precedence*/
	{
		return 3;
	}
	else if(symbol == '*' || symbol == '/')
	{
		return 2;
	}
	else if(symbol == '+' || symbol == '-')          /* lowest precedence */
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void InfixToPrefix(char  infix[], ss *s)
{

    char prefix[max];
	int i=0, j=0;
	char item;
	for (int i = 0; i < strlen(infix); i++) {

        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
	while(infix[i]!='\0')
	{
	    item=infix[i];
	    if( isdigit(item)||isalpha(item))
		{
			prefix[j++] = item;
		}
		else if(item == '(')
		{
			push(item,s);
		}
		else if(item == ')')
		{
			while(s->arr[s->top]!= '(')
			{
				prefix[j++] =s->arr[s->top];
				pop(s);
			}
			pop(s);
		}

		else if(is_operator(item))
		{
		    if(item=='^'){
                    while(precedence(s->arr[s->top])>= precedence(item))
                {
                        prefix[j++] = s->arr[s->top];
                        pop(s);

                }
		    }
                else{
                        while(precedence(s->arr[s->top])> precedence(item))
                    {
                            prefix[j++] = s->arr[s->top];
                            pop(s);
                    }
                }


			push(item,s);
		}
		i++;


	}
	while(!isEmpty(s)){
        prefix[j++]=s->arr[s->top];
        pop(s);
	}
    prefix[j] = '\0';
    printf("\n");
    repeat(50)
    printf("*");
    printf("\nPREFIX EXPRESSION : ");
    puts(strrev(prefix));
    printf("\n");
    repeat(50)
    printf("*");

}




void InfixToPostfix(char infix[], ss *s)
{
    char postfix[max];
	int i=0, j=0;
	char item;
	while(infix[i]!='\0')
	{
	    item=infix[i];
	    if( isdigit(item)||isalpha(item))
		{
			postfix[j++] = item;
		}
		else if(item == '(')
		{
			push(item,s);
		}
		else if(item == ')')
		{
			while(s->arr[s->top]!= '(')
			{
				postfix[j++] =s->arr[s->top];
				pop(s);
			}
			pop(s);
		}

		else
		{

			while(!isEmpty(s) && precedence(s->arr[s->top])>= precedence(item))
			{
			    if (item == '^' && s->arr[s->top] != '^')
                    break;
                else{
                    postfix[j++] = s->arr[s->top];
                    pop(s);
                }

			}

			push(item,s);
		}
		i++;


	}
	while(!isEmpty(s)){
        postfix[j++]=s->arr[s->top];
        pop(s);
	}

    postfix[j] = '\0';
    printf("\n");
    repeat(50)
    printf("*");
    printf("\nPOSTFIX EXPRESSION: ");
    puts(postfix);
    printf("\n");
    repeat(50)
    printf("*");
}









