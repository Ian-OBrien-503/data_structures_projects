//
//Ian O'Brien
//CS 163
//3-14-2017
//project 5 (GRAPHS)
//this program will create a graph of the basement of the FAB 
//it will allow user to navigate the basement and add data to the graph
//

#ifndef proj5_header_h_
#define proj5_header_h_

// preprocessor directives
#include <iostream>
#include <cstring>
using namespace std;


// global constants
const int strSize = 100;
const int defaultConSize = 7;


// this is a vertex struct and one will be located at each element of the adjacency list array
// this will be pointed to by edge nodes to know what verticies are adjacent to each other
struct vertex
{
    char * location;
    struct node * head;
};


// these are nodes on the LLL/edge list each of these nodes simply points to a vertex and 
// allows us to know which verticies are adjacent to each other
struct node
{
    vertex * adjacent;
    node * next;
};


// this class is the meat and potatoes of the program, it contains the listSize as an argument from
// default constructor and construtor with arguments
class graph
{
public:
    // default constructor
    graph();
    // constructor w/ arguments
    graph(int listSize);
    ~graph();
    int insertVertex(char location[]);
    int insertEdge(char currLoc [], char adjLoc []);
    int findLocation(char location[]);
    int displayDirections(char location[]);
private:
    vertex * adjacencyList;
    int listSize;
};


#endif // project 5 header file
