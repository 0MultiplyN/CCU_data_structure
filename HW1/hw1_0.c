#include <stdio.h>
#include <string.h>
struct vaccineInfo
{
    char Id[ 11 ] ;
    char Name[ 26 ] ;
    char Vac_Brand[ 31 ] ; // vaccine brand ;
    int Age ;
    char City[ 21 ] ;
}vaccineInfos[ 20 ];
int main( )
{
    int num_of_data = 0 ;
    scanf("%d",&num_of_data) ;
    getchar( ) ;
    for( int i = 0 ; i < num_of_data ; i++ )
    {
        scanf("%s",vaccineInfos[ i ].Id) ;
        scanf("%s",vaccineInfos[ i ].Name) ;
        scanf("%s",vaccineInfos[ i ].Vac_Brand) ;
        scanf("%d",&vaccineInfos[ i ].Age ) ;
        scanf("%s",vaccineInfos[ i ].City ) ;
    }
    char qry[ 31 ] ; //query
    scanf("%s",qry) ;
    /*for( int i = 0 ; i < num_of_data ; i++ )
    {
        printf("%s %s %s %d %s\n",vaccineInfos[ i ].Id,vaccineInfos[ i ].Name,vaccineInfos[ i ].Vac_Brand,vaccineInfos[ i ].Age,vaccineInfos[ i ].City) ;
    }*/
    for( int i = 0 ; i < num_of_data ; i++ )
    {
        if( vaccineInfos[ i ].Vac_Brand[ 0 ] == qry[ 0 ] )
        {
            printf("%s %s %s %d %s\n",vaccineInfos[ i ].Id,vaccineInfos[ i ].Name,vaccineInfos[ i ].Vac_Brand,vaccineInfos[ i ].Age,vaccineInfos[ i ].City) ;
        }
    }






    return 0 ;
}
