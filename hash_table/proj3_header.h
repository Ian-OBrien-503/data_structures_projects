/*
 *  Ian O'Brien
 *  CS 163
 *  Pokemon Hash Table
 *  This program allows you to search for pokemon and pokemon related terms via a hash table
 *  and return data about the pokemon or term
*/


// preprocessor directives
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <cctype>
using namespace std;

//global constants
const int strSize = 500;
const int defConsArrSize = 17;

// this struct will hold all data relevant to pokemon
// it will also contain a consturtur that will set all 
// pointers to NULL, and the destructor will delete all
// dynamic memory if it is not already NULL
struct pokemon 
{
    char *name;
    char *background;
    char *evolveName;
    int candy;
    int pokedex;
    char *type;
    pokemon();
    ~pokemon();
};

// this struct will hold all data relevant to a certain regions
// including name, name of pokemons there, and number of pokemons present
// it will also have a constructor to set all pointers to NULL and a destructuor 
// that will delete all dynamic memory
struct region
{
    char *name;
    char *pokemonsHere;
    int numberOfPokemons;
    region();
    ~region();
};

// this struct will hold data related to terminology related to pokemon, it will
// have a constructor to set all pointers to NULL and also a destructor to delete 
// all dynamic memory not set to NULL
struct terminology 
{
    char *word;
    char *definition;
    terminology();
    ~terminology();
};

// this is the struct node, each node will contain 3 data pointers, and one next pointer.  Any one node
// will only have one data pointer not set to NULL, the constructor will set all pointers in NULL
// and the destrurtor will delete all dynamic memeory that is not set to NULL
struct node
{
    pokemon *poke;
    region *reg;
    terminology *term;
    node *next;
    node();
    ~node();
};


// this is the hash table class it contains all member function including a constructor w/ and w/ out arguments
// this is where the array of head pointers lives and allows the client to choose the size of the array (they will
// be specified to choose a prime number), there are also three different retrieve functions depending on which type of 
// item they are trying to retrive data on. 
class h_table
{
public:
    h_table();                          //done
    h_table(int tableSize);             //done
    ~h_table();                         //done
    int hashFunction(char keyword []);  //done
    int loadData(char filePath []);     //done
    int displayChainLength(int & total);//done
    int removeNode(char keyword []);    //done (pokemon will delete, but regions and terms wont for some reason)
    int addInfo(char updateData []);     
    int displayKeyData(char keyword []);//done
    // retrives should take care of case sensitivity (assume all data in .txt is lowercase)
    int retrieve(char keyword [], terminology & termRetrieve);
    int retrieve(char keyword [], region & regionRetrieve);
    int retrieve(char keyword [], pokemon & pokemonRetrieve);
private:
    node ** hashTable;
    int hashTableSize;
};
