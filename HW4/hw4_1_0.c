
#include <stdio.h>
#include <stdlib.h>

typedef struct nd node;
struct nd
{
    int key;
    node *left , * right  ;
};

void printCurrentLevel( node* root, int level);
int height(  node* nd  );
// A utility function to create a new BST node
node* newNode(int item)
{
    node* temp = ( node*)malloc(sizeof(node));

    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder( node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
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


node* minValueNode( node* nd )
{

    node* current = nd ;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
    {
        current = current->left ;
    }

    return current;
}


node* deleteNode( node* root , int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }


        // (smallest in the right subtree)
        node* temp = minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Driver Code

void printLevelOrder( node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}

/* Print nodes at a current level */
void printCurrentLevel( node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

/* Compute the "height" of a tree */
int height(node* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

int main()
{
    node* root = NULL;
    int insertqry = 0 , deleteqry = 0 ;
    scanf("%d",&insertqry) ;
    while( insertqry-- )
    {
        int data = 0 ;
        scanf("%d",&data) ;
        root = insert( root , data ) ;
    }
    scanf("%d",&deleteqry) ;
    while( deleteqry-- )
    {
        int data = 0 ;
        scanf("%d",&data) ;
        root = deleteNode(root, data);
    }
    printf("Infixorder: ") ;
    inorder(root);
    printf("\n") ;
    printf("Levelorder: ") ;
    printLevelOrder(root);




    return 0;
}
