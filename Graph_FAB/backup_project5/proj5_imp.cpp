//
//Ian O'Brien
//CS 163
//3-14-2017
//project 5 (GRAPHS)
//this program will create a graph of the basement of the FAB 
//it will allow user to navigate the basement and add data to the graph
//

#include "proj5_header.h"

// default constructor will be invoked if someone makes an onbject of type graph without specifying the size as an argument
graph::graph()
{
    adjacencyList = new vertex[defaultConSize];
    listSize = defaultConSize;
    for(int i = 0; i < defaultConSize; i++)
    {
        adjacencyList[i].location=NULL;
        adjacencyList[i].head=NULL;
    }
}


// constructur sets the size of the array for the adjacency list from
// an argument from the client of size int.  it also sets all dynamic data items
// at each element of each array to NULL (location and head pointers)
graph::graph(int size)
{
    // if user specifies invalid size, a global constant size will be provided for them
    if (size < 0)
    {
        adjacencyList = new vertex[defaultConSize];
        listSize = defaultConSize;
        for(int i = 0; i < defaultConSize; i++)
        {
            adjacencyList[i].location=NULL;
            adjacencyList[i].head=NULL;
        }
    }
    adjacencyList = new vertex[size];
    listSize = size;
    for(int i = 0; i < listSize; i++)
    {
        adjacencyList[i].location=NULL;
        adjacencyList[i].head=NULL;
    }
}

// destructor first traverses the array and deletes all nodes of each LLL if head at that element is not NULL, then deletes the location
// char array at each element in the vertex array, and then deletes the dynamically allocated vertex array
graph::~graph()
{
    node * temp;

    for (int i = 0; i < listSize; i++)
    {
        if (adjacencyList[i].location != NULL)
        {
            while (adjacencyList[i].head != NULL)
            {
                temp = adjacencyList[i].head;
                adjacencyList[i].head = temp -> next;
                delete temp;
            }
        }
        for (int i = 0; i < listSize; i++)
        {
            if (adjacencyList[i].location != NULL)
            {
                delete [] adjacencyList[i].location;
            }
        }
        delete [] adjacencyList; 
    }
}


// this function will allow user to set locations in the basement of fab as verticies 
// in the graph, this function will take a location argument from the client and check
// the adjacency array for any blank spots to plop the new vertex, if there is room the vertex
// will be added, if there is not room this function will return 0 and flag error in the client
int graph::insertVertex(char location [])
{
    for(int i = 0; i < listSize; i++)
    {
        if(adjacencyList[i].location==NULL)
        {
            adjacencyList[i].location = new char[strlen(location) + 1];
            strcpy(adjacencyList[i].location, location);
            return 1;
        }
    }
    return 0;
}


// this function takes a char array as an argument which is the data member of the vertex, this function finds the match 
// in the vertex array and returns the index of that vertex, if no match is found a -1 is returned as an error flag
int graph::findLocation(char location [])
{
    for (int i = 0; i < listSize; i++)
    {
        if(adjacencyList[i].location != NULL && strcmp(location,adjacencyList[i].location) ==0)
        {
            return i;
        }
    }
    // if no match found return -1 for error as to not be confused with array element 0
    return -1;

}


// this function takes two char array arguments which are really data members of vertex, and allows you to build an edge between the two vertex, directionally.
// this will allow you to traverse from currLoc to adjLoc as there is now an edge built between the two verticies
int graph::insertEdge(char currLoc [], char adjLoc [])
{
    node * temp;

    int currIndex = findLocation(currLoc);
    int adjIndex = findLocation(adjLoc);
    // if no matches are found in find location or some other issues, throw error to client 
    if (currIndex == -1 || adjIndex == -1)
        return 0;
    else
    {
        temp = new node;
        temp -> adjacent = &adjacencyList[adjIndex];
        temp -> next = adjacencyList[currIndex].head;
        adjacencyList[currIndex].head = temp;
    }
}


//  this function finds the vertex for the character array passed into it, and then prints all edges locations 
//  and displays all verticies adjacent to the vertex passed into it.
//  this allows you to check where you can travel directly to via an edge from the current index
int graph::displayDirections(char location [])
{
    node * temp;

    int index = findLocation(location);
    if (index == -1)
        return 0;
    else
    {
        cout << "YOU CAN DIRECTLY TRAVEL TO..." << endl;
        temp = adjacencyList[index].head;
        while (temp != NULL)
        {
            cout << temp -> adjacent -> location << endl;
            temp = temp -> next;
        }
        return 1;
    }
}
