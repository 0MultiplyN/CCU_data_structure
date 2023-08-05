#include <stdio.h>
#include <stdlib.h>
#define MIN2( x , y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )
int dfn[ 10000 ] ;
int low[ 10000 ] ;
int num;
int adj[ 10000 ][ 10000 ] ; // adjacency matrix ;
int num_vertex ; // number of vertex
int ini_vertex ; // initial vertex
int cnt = 0  ; // count for dfn
int visited[ 10000 ] ;
int isAP[ 10000 ] ; // is articulation point
void CalculateDfnLow( int u , int v )
{
    /* compute dfn and low while performing a dfs search
        beginning at vertex u, v is the parent of u (if any) */
    visited[ u ] = 1 ;
    dfn[ u ] = cnt , low[ u ] = cnt ;
    cnt++ ;
    int children = 0 ;
    for( int j =  0 ; j < num_vertex ; j ++ )
    {
        if( adj[ u ][ j ] == 0 ) continue ;
        if( visited[ j ] == 0 )
        {
            children++ ;
            CalculateDfnLow( j , u ) ;
            low[ u ] = MIN2( low[ u ] , low[ j ] ) ;
            if( v != -1 && low[ j ] >= dfn[ u ])
            {
                isAP[ u ] = 1 ;
            }
        }
        else if( j != v )
        {
            low[ u ] = MIN2( low[ u ] , dfn[ j ]);
        }
    }
    if( v == - 1 && children > 1 )
    {
        isAP[ u ] = 1 ;
    }
}

int main( )
{
    scanf("%d %d", &ini_vertex , &num_vertex ) ;
    for( int i = 0 ; i < num_vertex ; i++ )
    {
        for( int j = 0 ; j < num_vertex ; j++ )
        {
            scanf("%d",&adj[ i ][ j ]) ;
        }
    }

    CalculateDfnLow( ini_vertex-1 , -1 ) ;

    for( int i = 0 ; i < num_vertex ; i++ )
    {
       printf("%d ",dfn[ i ]) ;
    }

    printf("\n") ;

    for( int i = 0 ; i < num_vertex ; i++ )
    {
        printf("%d ",low[ i ]) ;
    }

    printf("\n") ;

    for( int i = 0 ; i < num_vertex ; i++ )
    {
        if( isAP[ i ] == 1 )
            printf("%d ",i+1) ;
    }


    return 0 ;
}
