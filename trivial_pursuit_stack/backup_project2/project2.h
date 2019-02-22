/*
 * Ian O'Brien
 * CS163 Project 2
 * Card Game w/ shuffle (using random number generator)
*/

// pre-processor directives
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// global constants
const int deckSize = 30; //for array of pointers to build and shuffle deck when setting up
const int arrSize = 5;    //array size per node of LLL of arrays
const int strSize = 250;    //for passing arguments to functions from the client

struct card
{
    char *subject;
    char *question;
    int difficulty;
    char *answer;
    char *hint;
    int visitFlag;
};

struct node
{
    card **arrayOfCards;
    node * next;
};

class game
{
public:
    game();
    ~game();
    int setup(char filePath []);
    int shuffle();
    int displayAllCards();
    int play();
private:
    int addCard(card * & pushPtr);
    node *head;
    card **shuffleArray;
    int index;
};
