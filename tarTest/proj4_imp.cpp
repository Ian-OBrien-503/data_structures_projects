/*
 *Ian O'Brien
 *CS163
 *March 5th, 2017
 *project 4 - CS Terminology BST
 *this program builds a binary search tree with data from an external text file each node
 *in bst conatains a CS term as a keyword as a dynamically allocated character array and 
 *a definition of the term as a dynamiclly allocated character array, and a left and a right 
 *node pointer
*/

// include header file
#include "proj4_header.h"


// node constructor sets all pointers to NULL inside each node
node::node()
{
    csTerm = NULL;
    def = NULL;
    left = NULL;
    right = NULL;
}


// node desctructor will deallocate all dynamic memory of the node when invoked
node::~node()
{
    if(csTerm)
        delete [] csTerm;
    if(def)
        delete [] def;
}


// bst constructor will just set root to NULL
bst::bst()
{
    root = NULL;
}


// bst destructor will call void function delete all (which deallocates all dynamic memory from the BST) deletes nodes
bst::~bst()
{
    deleteAll(root);        
}


// this function will recurse to all leaves of the BST, and on the return delete each node (at the delete root line the node
// desturtor is called and all data in the node is deleted as well
void bst::deleteAll(node * & root)
{
    if(root == NULL)
        return;
    else
    {
        deleteAll(root -> right);
        deleteAll(root -> left);
        delete root;
    }
}


// load data will read data from a text file one line at a time, and call insert function (public version), with both term and definition
// as arguments
int bst::loadData(char filePath [])
{
    // local variables
    fstream inFile;  
    char userCSterm[strSize];
    char userCSdef[strSize];
    int count = 0;
    int dataItems;

    inFile.open(filePath);

    if (!inFile.is_open())
        return 0;
    else
    {
        inFile.getline(userCSterm, strSize, ':');
        while(!inFile.eof())
        {
            inFile.getline(userCSdef, strSize);
            dataItems = insert(userCSterm, userCSdef, count);
            inFile.getline(userCSterm, strSize, ':');
        }
        return dataItems;
    }
}


// this is the wrapper  insert function is used to call private insert function which will take root by reference as a argument and 
// call the recursive function with a root argument to add a new node to the BST
int bst::insert(char userCSterm [], char userCSdef [], int & count)
{
    return insert (root, userCSterm, userCSdef, count);
}


// this insert function takes two char string arguments, and the root by reference as arguments, as changes are being
// made the to BST (inserting a new node).  this function recursively adds a node to the LLL by traversing along the tree
// comparing its csTerm argument to the root csTerm and if the argument is less than the root we will traverse left, if it is
// greater we traverse right until we hit a null root, and then add a new node
int bst::insert(node * & root, char userCSterm [], char userCSdef [], int & count)
{
    if (root == NULL)
    {
        root = new node;
        root -> csTerm = new char[strlen(userCSterm) + 1];
        strcpy(root -> csTerm, userCSterm);
        root -> def = new char[strlen(userCSdef) +1];
        strcpy(root -> def, userCSdef);
        ++count;
        return count;
    }
    else
    {
        if (strcmp(userCSterm,root -> csTerm) < 0)
        {
            insert(root->left, userCSterm, userCSdef, count);
        }
        else
            insert(root->right, userCSterm, userCSdef, count);
    }
}


// this is the wrapper display all function that calls the recursive displayall function with the root node argument
int bst::displayAll()
{
    int count = 0;
    displayAll(root, count);
    return count;
}


// this function does an in-order traversal of the BST and prints out data at each node, recursively, also returns a count
// of how many nodes were visted and data was printed from
int bst::displayAll(node * root, int & count)
{   
    if (root == NULL)
        return 0;
    else
    {
        ++count;
        displayAll(root->left, count);
        cout << root -> csTerm << endl;
        cout << root -> def << endl << endl;
        displayAll(root->right, count);
        return count;
    }
}


// this wrapper function calls the private getHeight function with the node * root argument
int bst::getHeight()
{
    return getHeight(root);
}


//the get height function compares the left subtree vs the right subtree height whcih is defined as the number of nodes traversed from 
//root to the fartherst away leaf
int bst::getHeight(node * root)
{
    if (root == NULL)
        return 0;
    return max(getHeight(root -> left), getHeight(root->right)) + 1;
}


//this wrapper function will take char upper and lower bound arguments from the client and pass the arguments into the recursive display range function
// with a node * root argument
int bst::displayRange(char lowerBound, char upperBound)
{
    int count = 0;
    return displayRange(root, lowerBound, upperBound, count);
}


// this recursive function will take lower bound and upper bound chars as arguments from the client and compare them to the first letter of the csTerm at each node
// if the csTerm is greater than or equal to lower bound and less than or equal to upper bound then we will print the data at the node and return the number of matches
// we found
int bst::displayRange(node * root, char lowerBound, char upperBound, int & count)
{
    if (root == NULL)
        return 0;
    else
    {
        displayRange(root -> left, lowerBound, upperBound, count);
        if (root -> csTerm[0] >= lowerBound && root -> csTerm[0] <= upperBound)
        {
            ++count;
            cout << root -> csTerm << endl;
            cout << root -> def << endl << endl;
        }
        displayRange(root -> right, lowerBound, upperBound, count);
        return count;
    }
}


// this wrapper function takes a CSterm argument from the client and passes it to the private recursive function that will search for a node containing the exact match
// of the term sent by the client
int bst::remove(char userCSterm [])
{
    return remove(root, userCSterm);

}


// this function will recursively serach for a match on the BST for the CSterm sent in as an argument, there are 7 cases to consider for BST removal.  
//
int bst::remove(node * & root, char userCSterm [])
{
    // local variables
    node * temp;

    if (root == NULL)
        return 0;
    if (strcmp(userCSterm, root -> csTerm) == 0)
    {
        // delete from a leaf
        if(root -> left == NULL && root -> right == NULL)
        {
            delete root;
            root = NULL;
        }
        // if match node has a left child, and no right child
        else if(root -> left != NULL && root -> right == NULL)
        {
            temp = root -> left;
            delete root;
            root = temp;
        }
        // if match has a right child, and no left child
        else if(root -> right != NULL && root -> left == NULL)
        {
            temp = root -> right;
            delete root;
            root = temp;
        }
        // if node to be deleted has two children
        else if(root->right && root->left)
        {
            temp = root -> right;
            // if root -> right -> left exists (in order sucessor), copy its data to root and delete the node where the match was found
            // if root -> right -> left does NOT exist copy data from right hand inorder sucessor and delete temp
            while(temp -> left)
            {
                temp = temp -> left;
            }
            char * tempStr = new char[strlen(temp -> csTerm) + 1];
            char * tempDef = new char[strlen(temp -> def) + 1];
            strcpy(tempDef, temp -> def);
            strcpy(tempStr, temp -> csTerm);
            // do not call delete or could have lost data/memory leaks
            remove(root, temp->csTerm);
            delete [] root -> csTerm;
            delete [] root -> def;
            root -> csTerm = new char[strlen(tempStr) + 1];
            root -> def = new char[strlen(tempDef) +1];
            strcpy(root->csTerm, tempStr);
            strcpy(root->def, tempDef);
            delete [] tempStr;
            delete [] tempDef;
        }
        return 1;
    }
    // recursively traverse the tree to try to find match
    else
    {
        if(strcmp(userCSterm,root->csTerm) < 0)
            remove(root->left, userCSterm);
        else
            remove(root->right, userCSterm);
    }
}


// the efficnecy test checks the height of the left and the right subtrees and subtracts the two values to get a balance factor
// if the balance factor is in range of [-1,1] then we can say the tree is relatively balanced as the left and right subtree heights
// vary by no more than 1, if not we return false and say that the left and right subtrees are at least relatively unbalanced
// but this does not tell us HOW unbalanced the left and right subtrees are. 
bool bst::isEfficient()
{
    int left = 0, right = 0, efficient = 0;
    
    left =  getHeight(root->left);
    right = getHeight(root->right);

    efficient = left - right;
    if (efficient >= -1 && efficient <= 1)
        return true;
    return false;
}


// this wrapper function will take a char array and a temp node object from the client as arguments and pass them to the private recursive retrieve function
// to try to find a match to retrieve data on
int bst::retrieve(char userCSterm [], node & tempNode)
{
    return retrieve(root, userCSterm, tempNode);
}


// this recursive private function will traverse the bst and look for a match on the userCSterm, if it is found it will return both the 
// term and definition to the tempNode object passed by reference from the client that were passed by reference, if no match is found an 
// error flag will be thrown back to the client
int bst::retrieve(node * root, char userCSterm [], node & tempNode)
{

    if (root == NULL)
        return 0;
    else
    {
        if (strcmp(userCSterm, root -> csTerm) == 0)
        {
            tempNode.csTerm = new char[strlen(root->csTerm) +1];
            strcpy(tempNode.csTerm, root->csTerm);
            tempNode.def = new char[strlen(root->def) +1];
            strcpy(tempNode.def, root->def);
            return 1;
        }
        else
        {   
            if(strcmp(userCSterm,root->csTerm) < 0)
                retrieve(root->left, userCSterm, tempNode);
            else
                retrieve(root->right, userCSterm, tempNode);
        }
    }
}
