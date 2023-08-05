#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 10000000

typedef struct{
    int row;
    int col;
    int dir;
}element ;
typedef struct{
    int vert ; // vertical position
    int horiz; // horizontal position
} dir ;

element stack[ MAX_STACK_SIZE ] ;  /* global stack declaration */
int top ; // top of stack

int maxsize ; // real size    double dimension
int dimension ; // real dimension
dir dirs[ 4 ] =  { { 1 , 0 } , {  0 , 1  } , { -1 , 0 } , { 0 , -1 } } ; // down right up left direction

int mark[ 9999 ][ 10000 ] , maze[ 9999 ][ 10000 ] ;
char str[ 9999 ][ 10000 ] ;
int ans[ 9999 ][ 10000 ] ;

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

element push( element item ) // push item in stack
{
    if( full( ) == 0 )  return stack[ ++ top ] = item ;
}

element pop( ) // pop item in stack
{
    if( empty( ) == 0 ) return stack[ top -- ] ;
}



void ProcessInput(  )// read character store integer
{
    for( int i = 0 ; i < dimension ; i++ )
    {
        scanf("%s",str[ i ] ) ;
    }
    for( int i = 0 ; i < dimension ; i++ )
    {
        for( int j = 0 ; j < dimension ; j++ )
        {
            if( str[ i ][ j ] == '0' )
            {
                maze[ i  ][ j  ] = 0 ;
            }
            else maze[  i  ][ j   ] = 1 ;
        }
    } // read character store integer
    return ;
}

int isSafe( int nxtrow , int nxtcol )
{
    if(  ( maze[ nxtrow ][ nxtcol ] != 1 ) ||  ( mark[ nxtrow ][ nxtcol ] != 0 )  || nxtrow >= dimension  ||  nxtcol >= dimension    || nxtrow < 0 || nxtcol < 0 )
    {
        return FALSE ;
    }
    else return  TRUE  ;
} // determine

void path( void )
{
    int row , col , nxtrow , nxtcol , dir ,  found = FALSE ;
    top = 0 , stack[ 0 ].row = 0 , stack[ 0 ].col = 0 , stack[ 0 ].dir = 0 ;
    mark[ 0 ][ 0 ] = 1 ;
    element position ; // postion of now

    while( top > -1 && !found )
    {
        position = pop( ) ;
        row = position.row , col = position.col , dir = position.dir ;
        while( dir < 4 &&  !found )
        {
            nxtrow = row + dirs[ dir ].vert ;
            nxtcol = col + dirs[ dir ].horiz ;
            if( nxtrow == dimension -1   &&  nxtcol == dimension -1   ) found = TRUE ;
            else if( isSafe( nxtrow , nxtcol ) )
            {
                mark[ nxtrow ][ nxtcol ] = 1 ;
                position.row = row , position.col = col , position.dir = ++dir ;
                push( position ) ; // push the path in stack
                row = nxtrow , col = nxtcol ;
                dir = 0 ; // keep the first direction : DOWN
            }   // current position has not been checked, place it
                // on the stack and continue
            else dir++ ;
        }  // check all of the remaining directions from the current position
    }

    for( int i = 0 ; i <= top ; i++ )
    {
        int stkrow = stack[ i ].row , stkcol = stack[ i ].col ;
        ans[ stkrow ][ stkcol ] = 1 ;
    } // put answer ( in stack ) to array for printing out

    ans[ row ][ col ] = 1 ;
    ans[ dimension - 1 ][ dimension - 1 ] = 1 ;

    for( int i = 0 ; i < dimension ; i++ )
    {
        for( int j = 0 ; j < dimension ; j++ )
        {
           printf("%d",ans[ i ][ j ]) ;
        }
        printf("\n") ;
    }

}


void Initialize( )
{
    for( int i = 0 ; i < dimension ; i++ )
    {
        for( int j = 0 ; j < dimension ; j++ )
        {
            mark[ i ][ j ] = 0 ;
            maze[ i ][ j ] = 0 ;
            ans[ i ][ j ] = 0 ;
        }
    }
}

int main ()
{
    int qry = 0 ; //qurey
    scanf("%d",&qry ) ;
    while( qry -- )
    {
        Initialize( ) ;
        scanf("%d",&dimension) ;
        maxsize = 2 * dimension ;
        Initialize( ) ;
        ProcessInput(  ) ;
        path( ) ;
    }

}



