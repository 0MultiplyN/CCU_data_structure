#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int array[ 2000 ] ;
int n ; // for array lenth
int idxa ;
int FindMin(int x, int y)
{
    if( x < y ) return x ;
    else return y ;
}
void MyMergeSort( void )
{
    int *list = array;
    int *sorted= (int *) malloc( n * sizeof(int));
    // use pointer for swapping
    int  segment ;
    int  start ;
    for (segment = 1; segment < n ; segment += segment)
    {
        for ( start = 0 ; start < n ; start += segment * 2)
        {
            int low = start ;
            int mid = FindMin(start +  segment , n) ;
            int high = FindMin(start +  segment * 2 , n);
            int k = low ;
            int start1 = low ;
            int end1 = mid ;
            int start2 = mid ;
            int end2 = high ;
            while ( start1 < end1 && start2 < end2 )
            {
                 if( list[ start1 ] < list[ start2 ] )
                 {
                     sorted[ k++ ] = list[ start1++ ] ;
                 }
                 else
                 {
                     sorted[ k++ ] = list[ start2++ ] ;
                 }
             }
            while (start1 < end1)
            {
                sorted[k++] = list[start1++];
            }
            while (start2 < end2)
            {
                sorted[k++] = list[start2++];
            }
        }
        for( int i = 0 ; i< n ; i++ )
        {
            if( i == n - 1 )
            {
                printf("%d",sorted[ i ]) ;
            }
            else
            printf("%d, ",sorted[ i ]) ;
        }
        printf("\n") ;

        int *temp = list;
        list = sorted ;
        sorted = temp ;
        // swap sorted list and origin list
    }
    // level
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
    MyMergeSort(  ) ;
    int min = 0 ;
    for( int i = 1 ; i < n ; i++ )
    {
        if( i == 1 )
        {
            min = array[  1  ] - array[  0  ] ;
        }
        else
        {
            if( array[ i  ] - array[ i - 1 ] < min )
            {
                min = array[ i ] - array[ i - 1 ] ;
            }
        }
    }
    // find minimum gap
    printf("Minimum gap: %d\n",min) ;
    return 0;
}
