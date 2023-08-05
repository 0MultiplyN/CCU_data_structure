#include <stdio.h>
#include <stdlib.h>

typedef struct nd node;
struct nd
{
    int key;
    node *left , * right  ;
};


int num_patha = 0 ;
int num_pathb = 0 ;
int last = 0 ;
// A utility function to create a new BST node
node* newNode(int item)
{
    node* temp = ( node*)malloc(sizeof(node));

    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}



/* A utility function to
   insert a new node with given key in
 * BST */
node* insert(node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}






int CalculatePatha(node* root , int * path  , int x )
{
    // if root is NULL
    // there is no path
    if ( !root ) return 0 ;


    // push the node's value in 'arr'
    path[ num_patha ] = root -> key ;
    num_patha++ ;

    // if it is the required node
    // return true
    if (root->key == x) return 1 ;

    // else check whether the required node lies
    // in the left subtree or right subtree of
    // the current node
    if ( CalculatePatha(root->left , path , x ) ||CalculatePatha (root->right, path, x) ) return 1 ;


    // required node does not lie either in the
    // left or right subtree of the current node
    // Thus, remove current node's value from
    // 'arr'and then return false
    num_patha -- ;
    path[ num_patha ] = -1 ;
    return 0 ;
}

int CalculatePathb(node* root , int * path  , int x )
{
    // if root is NULL
    // there is no path
    if ( !root ) return 0 ;


    // push the node's value in 'arr'
    path[ num_pathb ] = root -> key ;
    num_pathb++ ;

    // if it is the required node
    // return true
    if (root->key == x) return 1 ;

    // else check whether the required node lies
    // in the left subtree or right subtree of
    // the current node
    if ( CalculatePathb(root->left , path , x ) || CalculatePathb (root->right, path, x) ) return 1 ;


    // required node does not lie either in the
    // left or right subtree of the current node
    // Thus, remove current node's value from
    // 'arr'and then return false
    num_pathb -- ;
    path[ num_pathb ]= -1 ;
    return 0 ;
}

void PrintPathKey(node* root , int na , int nb )
{
    // array to store the path of
    // first node na from root
    // na for original nb for final
    int patha[ 1000 ] ;
    num_patha = 0 ;

    // array to store the path of
    // second node nb from root
    int pathb[ 1000 ] ;
    num_pathb = 0 ;

    CalculatePatha(root , patha   , na);
    CalculatePathb(root ,  pathb , nb );

    int repeatnode = -1;

    // Get repeat point
    int i = 0, j = 0;
    while ( i != num_patha || j != num_pathb)
    {
        // Keep moving forward until no repeatnode
        // is found
        if (i == j && patha[ i ] == pathb[ j ] )
        {
            i++;
            j++;
        }
        else
        {
            repeatnode = j - 1;
            break;
        }
    }

    // Print the required path
    for (int i = num_patha - 1 ; i > repeatnode; i--)
    {
        printf("%d->",patha[ i ]) ;
    }

    for ( int i = repeatnode ; i < num_pathb ; i++)
    {
        if( i == num_pathb - 1 )
        {
            last = pathb[ i ] ;
        }
        printf("%d->",pathb[ i ]) ;
    }

}

void PrintPathTreasure(node* root , int na , int nb )
{
    // array to store the path of
    // first node na from root

    int patha[ 1000 ] ;
    num_patha = 0 ;

    // array to store the path of
    // second node nb from root
    int pathb[ 1000 ] ;
    num_pathb = 0 ;

    CalculatePatha(root , patha   , na);
    CalculatePathb(root ,  pathb , nb );

    int intersection = -1;

    // Get repeat point
    int i = 0, j = 0;
    while ( i != num_patha || j != num_pathb)
    {
        // Keep moving forward until no repeatnode
        // is found
        if (i == j && patha[ i ] == pathb[ j ] )
        {
            i++;
            j++;
        }
        else
        {
            intersection = j - 1;
            break;
        }
    }

    // Print the required path
    for (int i = num_patha - 1 ; i > intersection; i--)
    {
        if( last == patha[ i ] )
        {
            continue ;
        }
        printf("%d->",patha[ i ]) ;
    }

    for ( int i = intersection ; i < num_pathb ; i++)
    {
        if( last == pathb[ i ] )
        {
            continue ;
        }
        printf("%d",pathb[ i ]) ;
        if( i != num_pathb - 1  )
        {
            printf("->") ;
        }
    }
}

int main()
{
    node* root = NULL;
    int insertqry = 0  ;
    scanf("%d",&insertqry) ;
    while( insertqry-- )
    {
        int data = 0 ;
        scanf("%d",&data) ;
        root = insert( root , data ) ;
    }
    int org = root->key ;
    int num_key = 0 , num_treasure = 0 ;
    scanf("%d %d",&num_key,&num_treasure) ;
    PrintPathKey(root ,  org , num_key  );
    PrintPathTreasure(root, num_key , num_treasure );
    return 0;
}
