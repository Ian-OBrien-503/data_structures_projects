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

int main()
{
    // local variables
    char menuSelect;
    int errorCheck;
    char filePath[strSize];
    char userCSterm[strSize];
    char userCSdef[strSize];
    char lowerBound, upperBound;
    bool efficientTest;
    

    // application introduction
    cout << '\n' << "Welcome to Ian's Binary Search Tree\n";
    
    // instantiate binary search tree 
    bst myTree;
    // need a temp object for retrieve function
    node tempNode;

    // prompts user for .txt file and throws error and quits program if bad filePath
    cout << "What .txt file would you like to use? ";
    cin.getline(filePath,strSize);
    errorCheck = myTree.loadData(filePath);
    if(errorCheck == 0)
    {
        menuSelect = 'Q';
        cout << "\n\t bad file path specified, terminating program \n\n";
    }
    else
        cout << endl << errorCheck << " data items loaded to BST";
    
    // looping command menu 
    while(toupper(menuSelect) != 'Q')
    {
        cout << "\n\nWhat would you like to do?\n"
             << "(A)dd new terms/definitions" << endl
             << "(R)emove data" << endl
             << "(D)ata retrivial" << endl
             << "(F)ind tree height" << endl
             << "(E)fficeny test" << endl
             << "(G)display all data" << endl
             << "(N)display range of data" << endl
             << "(Q)uit\n";
        cin.get(menuSelect);
        cin.ignore();

        switch(toupper(menuSelect))
        {
            case 'A': 
                errorCheck = 0;
                cout << "What is the term you would like to add to the tree? ";
                cin.getline(userCSterm, strSize);
                cout << "What is the definition of said term? ";
                cin.getline(userCSdef, strSize);
                errorCheck = myTree.insert(userCSterm, userCSdef, errorCheck);
                if (errorCheck != 0)
                    cout << " DATA ITEM SUCESSFULLY ADDED TO TREE\n";
                break;
            case 'R':
                cout << "What term would you like to remove from the tree? ";
                cin.getline(userCSterm, strSize);
                errorCheck = myTree.remove(userCSterm);
                if (errorCheck == 0)
                    cout << "NO MATCH FOUND OR TREE IS EMPTY";
                else
                    cout << "NODE CONTAINING \"" << userCSterm << "\" FOUND AND DELETED";
                break;
            case 'D':
                cout << "What CS term would you like to search for? ";
                cin.getline(userCSterm, strSize);
                for (int i = 0; i < strlen(userCSterm); i++)
                  {
                    userCSterm[i] = tolower(userCSterm[i]);
                  }
                errorCheck = myTree.retrieve(userCSterm, tempNode);
                if (errorCheck == 0)
                    cout << "NO MATCH FOUND OR TREE IS EMPTY";
                else
                {
                    cout << "HERE IS MATCHING DATA FOR YOUR QUERY: \n";
                    cout << tempNode.csTerm << endl;
                    cout << tempNode.def << endl;
                }
                // deallocating temp node object memory that was used to retrieve data
                delete [] tempNode.csTerm;
                delete [] tempNode.def;
                break;
            case 'F':
                errorCheck = myTree.getHeight();
                if (errorCheck == 0)
                    cout << "NO DATA ON TREE HEIGHT";
                else
                    cout << errorCheck << " IS THE HEIGHT OF THE TREE\n";
                break;
            case 'E':
                efficientTest = myTree.isEfficient(); 
                if (efficientTest == true)
                    cout << "TREE IS RELATIVELY EFFICIENT";
                else
                    cout << "LEFT AND RIGHT SUBTREE ARE NOT EFFICIENT";
                break;
            case 'G':
                cout << endl;
                errorCheck = myTree.displayAll();
                if (errorCheck == 0)
                    cout << "NO DATA TO DISPLAY...\n";
                else
                    cout << errorCheck << " terms and definitions printed.";
                break;
            case 'N':
                cout << "what char do you want to use as lower bounds? ";
                cin.get(lowerBound);
                cin.ignore();
                cout << "what char do you want to use as upper bounds? ";
                cin.get(upperBound);
                cin.ignore();
                cout << endl;
                errorCheck = myTree.displayRange(lowerBound,upperBound);
                if (errorCheck == 0)
                    cout << "NO DATA FOUND IN SPECIFIED BOUNDS...";
                else
                    cout << errorCheck << " DATA ITEMS FOUND MATCHING YOUR QUERY";
                break;
            case 'Q':
                cout << "\t QUITTING PROGRAM...\n\n";
                break;
            default:
                cout << "\t INVALID MENU SELECTION!\n\n";
                break;
        }
    }
    // end of program
    return 0;
}
