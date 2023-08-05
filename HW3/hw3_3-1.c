#include <stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct nd node;
struct nd
{
    char data[ 30 ] ;
    node *link ;
};
int lastpos=0;
void MyInsertFunction( int pos , node* first , char* name )
{
    if( pos >  lastpos  || pos < 0 )
    {
        printf("no result\n") ;
        return ;
    }
    else
    {
        node* pos_ptr = first ;
        int cnt = pos ;
        while( cnt-- )
        {
            pos_ptr = pos_ptr->link ;
        }
        node* pos_after_ptr = pos_ptr -> link ; // pointer after pos
        if( pos_after_ptr == NULL )
        {
            node* tmp = (node*) malloc(sizeof(node)) ;
            tmp -> link = NULL ;
            pos_ptr->link = tmp ;
            strcpy( tmp ->  data , name ) ;
            lastpos++ ;
        } // pos is the last node int the linked list
        else
        {
            node* tmp = (node*) malloc(sizeof(node)) ;
            tmp->link = pos_after_ptr ;
            pos_ptr-> link = tmp ;
            strcpy( tmp ->  data , name ) ;
            lastpos++ ;
        }// pos is not the last node in the linked list
    }
}

void MyQueryFunction( int pos , node* first )
{
    node* ans = first ;
    char ans_name[ 30 ] ;
    if( pos > lastpos || pos == 0 )
    {
        printf("no result\n") ;
    }
    else
    {
        while( pos -- )
        {
            ans = ans -> link ;
        }
        strcpy( ans_name , ans->data  ) ;
        printf("%s\n",ans_name) ;
    }
}


void MyDeleteFunction( int pos , node* first )
{

    if( pos > lastpos || pos <= 0 )
    {
        printf("no result\n") ;
        return ;
    }
    else
    {
        int cnt = 0 ;
        node* tmp = first ;
        node* pos_before = first ;
        node* pos_cur =first ;

        while( cnt <= pos )
        {
            if( cnt == pos - 1 )
            {
                pos_before = tmp ;
            }
            if( cnt == pos )
            {
                pos_cur = tmp ;
            }
            tmp = tmp -> link ;
            cnt++ ;
        } // find pointer before delete node to link
        node* pos_after = pos_cur -> link ;
        pos_before -> link = pos_after  ;
        pos_cur->link = NULL ;
        lastpos -- ;
        free( pos_cur)  ;
    }
}

void MySwapFunction( int posa , int posb , node* first )
{
    if( posa <= 0 || posb <= 0 || posa > lastpos || posb > lastpos  )
    {
        printf("no result\n") ;
        return ;
    }// can not swap case
    node*  nodea = first ;
    node*  nodeb = first ;
    node*  preva = NULL ; // the node before nodea
    node*  prevb = NULL  ;// the node before nodeb
    node* tmp = first ;
    int cnt = 0 ;
    const int maxPos = (posa > posb) ? posa : posb;
    while(  ( tmp != NULL )  && ( cnt <= maxPos ) )
    {
        if ( cnt == posa - 1)
            preva= tmp;
        if ( cnt == posa )
            nodea = tmp;
        if ( cnt == posb - 1)
            prevb = tmp;
        if ( cnt  == posb)
            nodeb = tmp;
        tmp = tmp->link;
        cnt++;
    }// find pointer to get link for swapping
    if (nodea != NULL && nodeb != NULL)
    {
        if (preva != NULL)
        {
            preva->link= nodeb;
        }
        if (prevb != NULL)
        {
             prevb->link = nodea;
        }
        node* temp  = nodea->link; // in case of disappearing
        nodea->link  = nodeb->link;
        nodeb->link = temp;
    }//swap two node
}
int main( )
{
    int qry = 0 ;
    node* first = (node*) malloc(sizeof(node)) ;
    first->link = NULL ;
    scanf("%d",&qry) ;
    while( qry-- )
    {
        char ope[ 10 ] ; // operation
        scanf("%s",ope) ;
        char name[ 10 ] ;
        int pos ;
        if( ope[ 0 ] == 'i' )
        {
            scanf("%d %s",&pos,name) ;
            MyInsertFunction(  pos , first , name ) ;
        }
        else if( ope[ 0 ] == 'd')
        {
            scanf("%d",&pos) ;
            MyDeleteFunction( pos , first ) ;
        }
        else if( ope[ 0 ] == 's')
        {
            int posa = 0 , posb = 0 ;
            scanf("%d %d",&posa,&posb) ;
            MySwapFunction( posa , posb , first ) ;
        }
        else
        {
            scanf("%d",&pos) ;
            MyQueryFunction( pos , first ) ;
        }

    }



    return 0  ;
}
