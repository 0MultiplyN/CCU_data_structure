#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll ;
ll num_river ;
ll num_confluence ;
ll num_relation ;
struct RiverInfo
{
    char name[ 20 ] ;
    ll idx ;
    ll nearcon ;
    ll neardis ;
    ll totdis ;
}RiverInfos[ 500000 ];
ll nodes[ 10000 ][ 10000 ] ;
ll adj[ 10000 ][ 10000 ] ;
ll store_conflu[ 10000 ] ;
ll store_river[ 100000 ] ;
ll store_confluidx[ 10000 ] ;
ll cmp ( const void *a , const void *b )
{
    return *(ll *)b - *(ll *)a;
}
ll BinarySearch( ll* arr ,  ll n , ll k )
{
    ll left = -1, right = n;
    while( left < right - 1 )
    {
        ll mid = ( left + right ) / 2;
        if( arr[mid] > k )
        left = mid;
        else
        right = mid;
    }
    return right;
}// use binary search to process rank array
void FindRiverLenth( void )//find all river source distance to the origin
{
    for( ll i = 0 ; i < num_river ; i++)
    {
        ll v = RiverInfos[ i ].nearcon ;
        store_river[ i ] += RiverInfos[ i ].neardis ;
        for( ll j = num_confluence  ; j >= 0 ; j-- )
        {
            if( j == v || v < j ) continue ;
            if( adj[ v ][ j ] <= 0 ) continue ;
            else
            {
                store_river[ i ] += adj[ v ][ j ] ;
                v = j ;
            }
        }
         RiverInfos[ i ].totdis = store_river[ i ] ;
    }
}

int main( )
{
    scanf("%lld %lld",&num_river,&num_confluence) ;
    for( ll i = 0 ; i < num_river ; i++ )
    {
        scanf("%s %lld %lld",RiverInfos[ i ].name , &RiverInfos[ i ].nearcon , &RiverInfos[ i ].neardis ) ;
        RiverInfos[ i ].idx = num_confluence+1+i ;
        adj[  RiverInfos[ i ].idx ][ RiverInfos[ i ].nearcon ] = RiverInfos[ i ].neardis ;
        adj[  RiverInfos[ i ].nearcon ][ RiverInfos[ i ].idx ] = RiverInfos[ i ].neardis ;
    }
    scanf("%lld",&num_relation) ;
    for( ll i = 0 ; i < num_relation ; i++ )
    {
        ll fc , sc , dis ;
        // fc = first source point
        // sc = second source point
        // dis = the distance between first and second point
        scanf("%lld %lld %lld",&fc,&sc,&dis) ;
        adj[ fc ][ sc ] = dis ;
        adj[ sc ][ fc ] = dis ;
    }
    FindRiverLenth( );
    qsort( store_river , num_river , sizeof( ll ) , cmp )  ;
    ll rank[ 100000 ] ;
    rank[ 0 ] = 1 ;
    ll cnt = 1 ;
    for( ll i = 1 ; i < num_river ; i++ )
    {
        if( store_river[ i ] == store_river[ i - 1 ] )
        {
            rank[ i ] = cnt ;
        }
        else
        {
            cnt++ ;
            rank[ i ] = cnt ;
        }
    }// the real rank of river lenth
    for( ll i = 0 ; i < num_river ; i++ )
    {
        printf("%s ",RiverInfos[ i ].name) ;
        ll ans = BinarySearch( store_river , num_river , RiverInfos[ i ].totdis ) ;
        printf("%lld\n",rank[ ans ] ) ;
    }







    return 0 ;
}
