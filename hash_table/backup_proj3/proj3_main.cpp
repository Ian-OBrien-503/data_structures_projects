/*
 *  Ian O'Brien
 *  CS 163
 *  Pokemon Hash Table
 *  This program allows you to search for pokemon and pokemon related terms via a hash table
 *  and return data about the pokemon or term
*/

// include header file
#include "proj3_header.h"

int main()
{
    // local variables
    char menuSelect;
    int errorCheck, tableSize, total = 0;
    char filePath[strSize], keyword[strSize], updateData[strSize];
    

    // application introduction
    cout << '\n' << "Welcome to Ian's pokedex Hash Search\n";

    // prompts user to specify what size they would like the array of head pointers to be for the array of head pointers
    cout << endl << endl << "What size would you like you Hash Table to be? (MUST BE PRIME NUMBER): ";
    cin >> tableSize;
    cin.ignore(100, '\n');
    
    //instantiates hash table to user specified size 
    h_table myHash(tableSize);
    
    // prompts user for .txt file and throws error and quits program if bad filePath
    cout << "What .txt file would you like to use? ";
    cin.getline(filePath,strSize);
    errorCheck = myHash.loadData(filePath);
    if(errorCheck == 0)
    {
        menuSelect = 'Q';
        cout << "\n\t bad file path specified, terminating program \n\n";
    }
    else
        cout << endl << '\t' << errorCheck << " Pokemon loaded to the hash table" << "\n\t all data hashed to table...all systems go...";
    
    // looping command menu 
    while(toupper(menuSelect) != 'Q')
    {
        cout << "\n\nWhat would you like to do?\n"
             << "(C)heck all chains, (S)earch, (R)emove data/item, (A)dd info, (D)ata Retrival, or (Q)uit\n";
        cin.get(menuSelect);
        cin.ignore();

        switch(toupper(menuSelect))
        {
            case 'C':
                myHash.displayChainLength(total);
                cout << endl << total << " pokemon on the table.";
                break;
            case 'S':
                cout << "what is the keyword of the data item you want to print data on? ";
                cin.getline(keyword, strSize);
                errorCheck = myHash.displayKeyData(keyword);
                if (errorCheck == 0)
                    cout << "\n\t no data item found by \"" << keyword << "\"";
                break;
            case 'R':
                cout << "What is the keyword of the data item you want to delete? (pokemon name, region, or term): ";
                cin.getline(keyword, strSize);
                errorCheck = myHash.removeNode(keyword);
                if (errorCheck == 0)
                    cout << "\n\t no data item found by \"" << keyword << "\"";
                else
                  cout << "\n\t data item found by \"" << keyword << "\" and deleted";
                break;
            case 'A':
                cout << "YOU CHOSE ADD INFO!!!\n\n";
                break;
            case 'D':
                cout << "YOU CHOSE DATA RETRIVAL!!!\n\n";
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
