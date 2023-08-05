#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int array[ 2000 ] ;
int n ;
int idxa ;
void insertion_sort( )
{
    int i, key, j;
    for ( i = 1 ; i < n; i++)
    {
        key = array[i];
        j = i - 1;
        /**Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position **/
        while ( j >= 0 && array[j] > key )
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
        for( int i = 0 ; i < n ; i++ )
        {
            if( i == n - 1 ) printf("%d",array[ i ] ) ;
            else printf("%d, ",array[ i ] ) ;
        }
        printf("\n") ;
    }
}
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
    for( int i = 0 ; i < n ; i++ )
    {
        if( i == n - 1 ) printf("%d",array[ i ] ) ;
        else printf("%d, ",array[ i ] ) ;
    }
    printf("\n") ;
    insertion_sort( ) ;
    return 0;
}
