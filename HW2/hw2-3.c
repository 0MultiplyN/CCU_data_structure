#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char stack[ 1000 ] ;
char source[ 1000 ] ;
char dest[ 1000 ] ;
char move[ 1000 ] ; // the  char array  to  form the target word
int idx_s , idx_m ; // index of source and  move
int top ; // top of string
int maxsize ; // for check stack is full
int ans[ 1000 ] ;

int full(  )
{
    if( top == maxsize - 1 ) return 1 ;
    else return 0 ;
}

int empty( )
{
    if( top == -1 ) return 1 ;
    else return 0 ;
}

void push( char item ) // push item in stack
{
    if( full( ) == 0 )  stack[ ++ top ] = item ;
    return ;
}

void pop(  ) // pop item in stack
{
    if( empty( ) == 0 )  top --  ;
    return  ;
}

void solve( int index , int lenth )
{
    if( idx_m == lenth - 1 )
    {
        for( int i = 0 ; i < index ; i++ )
        {
            printf("%c ",ans[ i ] ) ;
        }
        printf("\n") ;
    } // find word to print out it
    else
    {
        if( idx_s < lenth )
        {
            ans[ index ] = 'i' ;

            push( source[  idx_s ++ ]  ) ;


            solve( index + 1 , lenth ) ;


            source[ -- idx_s ] = stack[ top  ] ; // pop i

            pop( ) ;

        }

        if(  ( top >= 0 )  && (  idx_m < lenth - 1 ) && dest[  idx_m + 1  ] == stack[ top ] )
        {

            ans[ index ] = 'o';

            move[ ++ idx_m ] = stack[ top  ] ; // pop answer in move

            pop( ) ;

            solve(  index + 1 , lenth ) ;
            push ( move[ idx_m -- ] ) ;

        }
    }
}
int main( )
{
    int qry = 0  ;  // query
    scanf("%d",&qry) ;
    while( qry-- )
    {

        scanf("%s",source) ; // source word
        scanf("%s",dest) ; // target word
        top = -1 ,  idx_s = 0 , idx_m = -1 ;
        printf("[\n") ;
        int lens = strlen( source ) , lend = strlen( dest ) ;
        maxsize = lens ;
        if( lens == lend )
        {
            solve( 0 , lens ) ;
        } // else : can not form target word
        printf("]\n") ;

    }




    return 0  ;
}
