
#include<stdio.h>

// Number of vertices in the graph

/* Define Infinite as a large enough
  value. This value will be used
  for vertices not connected to each other */
#define INF 9999999
int n ;
int graph[ 25 ][ 25 ] ;
int totaldistance[ 25] ;
int m ;
int shortestpath ;
int min_case = 0 ;
int cs = 1 ;
struct member
{
    char name[ 20 ] ;
}members[ 25 ];
// A function to print the solution matrix
void CalculateLenth(int dist[][n]);
void FindAllPairsPath()
{
    /* dist[][] will be the output matrix
      that will finally have the shortest
      distances between every pair of vertices */
    int dist[n][n], i, j, k;

    /* Initialize the solution matrix*/
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to*/
    for (k = 0; k < n; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < n; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < n; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    // Print the shortest distance matrix
    CalculateLenth(dist);
}

/* A utility function to print solution */
void CalculateLenth(int dist[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            totaldistance[ i ] += dist[ i ][ j ] ;
        }
    }
}
int main()
{
    scanf("%d %d",&n,&m) ;
    while( n != 0 && m != 0 )
    {
        for( int i = 0 ; i < n ; i++ )
        {
            scanf("%s",members[ i ].name) ;
        }
        for( int i = 0 ; i < n ; i++ )
        {
            for( int j = 0 ; j < n ; j++ )
            {

                if( i == j )
                {
                    graph[ i ][ j ] = 0 ;
                }
                else
                {
                     graph[ i ][ j ] = 9999999 ;
                }

            }
            totaldistance[ i ] = 0 ;
        }
        for( int i = 0 ; i < m ; i++ )
        {
            int nodea , nodeb , weight ;
            scanf("%d %d %d",&nodea,&nodeb,&weight) ;
            graph[ nodea-1 ][ nodeb-1 ] = weight ;
            graph[ nodeb-1 ][ nodea-1 ] = weight ;
        }
        FindAllPairsPath();
        for( int i = 0 ; i < n ; i++ )
        {
            if( i == 0 )
            {
                min_case = 0 ;
                shortestpath = totaldistance[ i ] ;
            }
            else
            {
                if( totaldistance[ i ] < shortestpath )
                {
                    min_case = i ;
                    shortestpath = totaldistance[ i ] ;
                }
            }
        }
        printf("Case #%d %s\n",cs,members[ min_case ].name) ;
        cs++ ;
        scanf("%d %d",&n,&m) ;
    }

    return 0;
}
