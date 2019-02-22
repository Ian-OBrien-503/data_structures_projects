//
//Ian O'Brien
//CS 163
//3-14-2017
//project 5 (GRAPHS)
//this program will create a graph of the basement of the FAB 
//it will allow user to navigate the basement and add data to the graph
//

#include "proj5_header.h"

int main()
{
    // local variables
    char menuSelect;
    int errorCheck;
    int tableSize;
    char location[strSize], currLoc[strSize], adjLoc[strSize];

    // application introduction
    cout << endl << "~~~~~Welcome to Ian's FAB Navigator~~~~~\n";
    cout << endl << "How many verticies do you want in your graph? ";
    cin >> tableSize;
    cin.ignore();

    graph myGraph(tableSize);
    
    while(toupper(menuSelect) != 'Q')
    {
        cout << "\n\nWhat would you like to do?\n"
             << "(V) insert a vertex" << endl
             << "(E) insert an edge" << endl
             << "(D) display possibile directions" << endl
             << "(P) display longest path" << endl
             << "(Q)uit\n";
        cin.get(menuSelect);
        cin.ignore();

        switch(toupper(menuSelect))
        {
            case 'V':
                cout << "Please enter a location in FAB: ";
                cin.getline(location, strSize);
                errorCheck = myGraph.insertVertex(location);
                if (errorCheck == 0)
                    cout << "out of room, adjacency list is full";
                else
                    cout << "sucessfully added \"" << location <<"\" to graph";
                break;
            case 'E':
                cout << "Please enter two locations that are adjacent to each other" << endl;
                cout << "Current Location: ";
                cin.getline(currLoc, strSize);
                cout << "Current location adjacent to...: ";
                cin.getline(adjLoc, strSize);
                errorCheck = myGraph.insertEdge(currLoc, adjLoc);
                if (errorCheck == 0)
                    cout << "ERROR: no vertex found with eiter or both locations";
                else
                    cout << "edge created between \"" << currLoc << "\" & \"" << adjLoc << "\"";
                break;
            case 'D':
                cout << "From where do you want directions from? ";
                cin.getline(location, strSize);
                errorCheck = myGraph.displayDirections(location);
                if (errorCheck == 0)
                    cout << "NO MATCH FOR LOCATION \"" << location <<"\"";
                break;
            case 'P':
                cout << "YOU CHOSE P";
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
