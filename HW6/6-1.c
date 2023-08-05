#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int array[ 2000 ] ;
int n ;
int idxa ;
void swap( int a , int b )
{
    int t = array[ a ] ;
    array[ a ] = array[ b ] ;
    array[ b ] = t ;
}
int partition( int le , int rt , int key )
{
    int i = le , j = rt ;
    while( i < j )
    {
        while( array[ j ] > key && i <= j ) j-- ;
        while( array[ i ] <= key && i < j ) i++ ;
        if( i < j ) swap( i , j ) ;
    }
    swap( le , i ) ;
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
    return i ;
}
void quicksort( int le , int rt , int key )
{
    if( le >= rt ) return ;
    int pos = partition( le , rt , key ) ;
    quicksort( le , pos - 1 , array[ le ] ) ;
    quicksort( pos +1 , rt , array[ pos + 1 ] ) ;
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
    char input[ 100000 ] ;
    fgets( input , 100000 , stdin ) ;
    processinput( input ) ;
     n = idxa ;
     quicksort( 0 , n -1 , array[ 0 ] ) ;




    return 0;
}
