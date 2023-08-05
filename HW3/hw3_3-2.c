#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nd node;
struct nd
{
    char data[ 30 ] ;
    node *link ;
};

struct people
{
    char name[ 20 ] ;
}peoples[ 1000 ]; // record name

int num_people = 0 ;

void ProcessInput( char* list_name )
{
    int len = strlen( list_name ) ;
    int name_idx = 0 ;
    for( int i = 0 ; i < len-1 ; i++ )
    {
        if( list_name[ i ] == ',' )
        {
            num_people++ ;
            name_idx = 0 ;
        }
        else if( list_name[ i ] == ' ' )
        {
            continue ;
        }
        else
        {
            peoples[ num_people ].name[ name_idx ] = list_name[ i ] ;
            name_idx++ ;
        }// PUT name in struct for copy to pointer
    }
}
void Clockwise( int k , node* first )
{
    int cnt = num_people ;
    int people_idx = 1 ; // peoples_index in struct
    node* cur_ptr = first ; // current pointer is first
    while( cnt-- )
    {
        node* tmp = ( node* )malloc( sizeof( node ) ) ;
        cur_ptr->link = tmp ;
        cur_ptr = tmp  ;
        tmp->link = NULL ;
        strcpy( tmp -> data , peoples[ people_idx ].name ) ;
        people_idx++ ;
    }
    cur_ptr->link = first ;  // circular linked list need link last node to head

}
void CounterClockwise( int k , node* first )
{
    int cnt = num_people ;
    int people_idx = num_people ; // peoples_index in struct
    node* cur_ptr = first ; //current pointer is first
    while( cnt-- )
    {
        node* tmp = ( node* )malloc( sizeof( node ) ) ;
        cur_ptr->link = tmp ;
        cur_ptr = tmp  ;
        tmp->link = NULL ;
        strcpy( tmp -> data , peoples[ people_idx ].name ) ;
        people_idx-- ;
    }
    cur_ptr->link = first ; // circular linked list need link last node to head
}
node* FindSurviver( int k , node* start , node* first )
{

    int count = 0 ;
    node* flag = start ;
    node* cur = start ;
    node* prev = start ;
    while (  prev->link != start )
    {
        prev = prev->link;
        count++;
    }// find the node before delete node to link
    while( k-- )
    {
        prev = cur ;
        cur = cur->link ;
    }// find the node before delete node to link
    printf("%s is killed.\n",cur->data) ;
    prev->link= cur->link ;
    if( cur == first )
    {
        first = cur->link  ;
    }// DELETE first node case
    flag = cur->link ;
    free( cur ) ;
    // check pointer in case of link to NULL
    if( prev != NULL )
    {
        cur = prev->link ;
    }
    else
    {
        cur = NULL ;
    }
    return flag ; // flag for the start for next deletion
}
int main( )
{
    char list_name[ 10000 ] ;
    fgets( list_name , 10000 , stdin ) ;
    int k = 0 , d = 0 ;
    ProcessInput( list_name ) ;
    node* first = ( node* )malloc( sizeof( node ) ) ;
    scanf("%d %d",&k,&d) ;
    strcpy( first -> data , peoples[ 0 ].name ) ;
    node* start = first ;
    if( d == 1 )
    {
        Clockwise( k , first ) ;
        int num_survive = num_people + 1 ;
        while( num_survive >= 2 )
        {
            start = FindSurviver( k , start ,first ) ;
            num_survive-- ;
        }
        printf("%s is survived.\n",start->data) ;

    }
    else
    {
        CounterClockwise( k , first  ) ;

        int num_survive = num_people + 1 ;
        while( num_survive >= 2 )
        {
            start = FindSurviver( k , start ,first ) ;
            num_survive--;
        }
        printf("%s is survived.\n",start->data) ;
    }
    return 0 ;
}

