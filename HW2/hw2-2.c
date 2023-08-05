#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100000
#define MAX_STACK_SIZE MAX //maximum stack size
#define MAX_EXPR_SIZE MAX //max size of expression

typedef enum {lparen,rparen,plus,minus,times,divide,mod,eos,operand} precedence;

precedence postfix_stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE]; //input string

void postfix(void);
int IsInfixValid( char* expr ) ;
int main()
{
   int qry = 0 ;
    scanf("%d",&qry) ;
    while( qry-- )
    {
        scanf("%s",expr);
        int flag = IsInfixValid( expr ) ;
        if( flag == 1 )
        {
            printf("1 ") ;
            postfix() ;
            printf("\n") ;
        }
        else
        {
            printf("0\n") ;
        }
    }
}

int IsInfixValid( char* expr )
{
    int valid = 0 ;
    int len = strlen( expr ) ;
    int lepar = 0 , rtpar = 0 ; // leftparen rightparen ;
    int integer = 0  , opt = 0 ,  keep_opt_flag = 0 , keep_int_flag = 0 ;
    int flag_par = 0 ;
    for( int i = 0 ; i < len ; i++ )
    {
        if( keep_opt_flag == 2 || keep_int_flag == 2 ) break ;
        // for consecutive operator or integer
        if( expr[ i ] == '(' )
        {
            lepar++ ;
            flag_par++ ;
        }
        else if( expr[ i ] == ')' )
        {
            rtpar++ ;
            flag_par-- ;
            if( flag_par < 0 ) break ;
        }
        else if( expr[ i ] >= '0' && expr[ i ] <= '9' )
        {
            integer ++ ;
            keep_int_flag ++ ;
            keep_opt_flag = 0 ;
        }
        else
        {
            opt++ ;
            keep_opt_flag ++ ;
            keep_int_flag = 0 ;
        }
    }
    if( lepar == rtpar ) valid = 1 ;
    // check num_leftpaten == num_rightparen
    if( keep_opt_flag == 2 || keep_int_flag == 2 || flag_par < 0 ) valid = 0 ;
    // consecutive integer or operator
    if( opt >= integer  ) valid = 0 ;  //too many operator : 1++2
    if( integer == 1 ) valid = 0 ; // only one integer is not allowed
    return valid ;
}
void postfix_push(int *top,precedence item)
{
	// add an item to the global stack
	if(*top >= MAX_STACK_SIZE-1){
		return;
	}
	postfix_stack[++*top] = item;
}
precedence postfix_pop(int *top)
{
	return postfix_stack[(*top)--];
}
precedence get_token(char *symbol, int *n)
{

	*symbol = expr[(*n)++];
	switch(*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '\0': return eos;
	default: return operand;
	}
	// get token to build precedence
}




void print_token(precedence token,int *i)
{
        if( token == plus )
        {
            printf("+") ;
            expr[(*i)++]='+' ;
        }
        else if( token == minus )
        {
            printf("-") ;
            expr[(*i)++]='-' ;
        }
        else if( token == times )
        {
            printf("*") ;
            expr[(*i)++]='*' ;
        }
        else if( token == divide )
        {
            printf("/") ;
            expr[(*i)++]='/' ;
        }
        else return ;
}
void postfix(void)
{

	int isp[] = {0,19,12,12,13,13,13,0}; // in stack presedence

	int icp[] = {25,19,12,12,13,13,13,0}; // is coming presedence

	char symbol;
	precedence token;
	int n = 0 , i = 0;
	int top = 0;

	postfix_stack[0] = eos;
	for(token = get_token(&symbol , &n) ; token != eos ; token = get_token(&symbol , &n))
	{
		if(token == operand)
		{
			printf("%c",symbol);
			expr[i++]=symbol;
		}
		else if(token == rparen)
        {

			while (postfix_stack[top] != lparen)
				print_token(postfix_pop(&top) , &i);
			postfix_pop(&top);
		}
		else
		{

			while(isp[postfix_stack[top]] >= icp[token])
				print_token(postfix_pop(&top) , &i);
			postfix_push(&top , token);
		}
	}
	while (  (token=postfix_pop(&top)  ) != eos )
	print_token(token , &i);
	expr[i]='\0';
}

