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


//pre-processor directives
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


// global constants
const int strSize = 500;

// this is the definition of the node struct at each node we will have a CS term 
// as a dynamiccaly allocated character array, and and a definition for the term
// as a dynamiccaly allocated character array, and a node * left/node * right pointers
// and constructur and destructor for the node
struct node
{
    char * csTerm;
    char * def;
    node * left;
    node *right;
    node ();
    ~node (); 
};

// this is the binary search tree class, it has a constructur that will set its root to null
// and a descturctor that will deallocate all dynamic memory upon exiting of the program, the only
// functions that will modify the tree are insert and remove so they are the only functions that will
// pass root by value.  more specific function definitions can be found in proj4_imp.cpp
class bst
{
public:
    bst();                                                                      // done
    ~bst();                                                                     // done
    int loadData(char filePath []);                                             // done
    int insert(char userCSterm [], char userCSdef [], int & count);             // done
    int remove(char userCSterm []);                                             // done
    int retrieve(char userCSterm [], node & tempNode);                          // done
    int getHeight();                                                            // done
    bool isEfficient();                                                         // done
    int displayAll();                                                           // done
    int displayRange(char lowerBound, char upperBound);                         // done
private:
    // delete all is called by the destructor so it is void
    void deleteAll(node * & root);                                                  //done 
    int insert(node * & root, char userCSterm [], char userCSdef [], int & count);  //done
    int remove(node * & root, char userCSterm []);                                  //done
    int retrieve(node * root, char userCSterm [], node & tempNode);                 //done
    int getHeight(node * root);                                                     //done
    int displayAll(node * root, int & count);                                       //done
    int displayRange(node * root, char lowerBound, char upperBound, int & count);   //done
    node * root;
};
