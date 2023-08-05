#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int array[ 2000 ] ;
int n ;
int idxa ;
void selection_sort( void  )
{
    for (int i=0; i<n-1; i++)
    {
        int min_idx = i;
        for (int j=i+1; j<n; j++)
        {
            if (array[  j  ] < array[  min_idx  ] )
            {
                min_idx = j;
            }
        }
        // swap
        int temp = array[ min_idx ];
        array[ min_idx ] = array[ i ];
        array[ i ] = temp;
        for( int i = 0 ; i< n ; i++ )
        {
            if( i == n - 1 )
            {
                printf("%d",array[ i ]) ;
            }
            else
            printf("%d, ",array[ i ]) ;
        }
        printf("\n") ;
    }
}
// select the minimun element from unsorted list
void processinput( char* input )
{
    int lenth = strlen( input ) ;
    int flag = 0 ;
    char num[ 30 ] ;
    int idxnum = 0 ;
    for( int i = 0 ; i < lenth ; i++ )
    {
        char tmp = input[ i ] ;
        if( isdigit( tmp ) )
        {
            num[ idxnum ] = tmp ;
            idxnum++ ;
            flag = 1 ;
        }
        else
        {
            if( flag == 1 )
            {
                flag = 0 ;
                num[ idxnum ] = '\0' ;
                idxnum = 0 ;
                int val = atoi( num ) ;
                array[ idxa ] = val ;
                idxa++ ;
            }
        }
    }
    int val = atoi( num ) ;
    array[ idxa ] = val ;
    idxa++ ;
}
int main()
{
    char input[ 10000 ] ;
    fgets( input , 10000 , stdin ) ;
    processinput( input ) ;
    n = idxa ;
    selection_sort( ) ;
    return 0;
}
