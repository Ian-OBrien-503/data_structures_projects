/*
 *  Ian O'Brien
 *  CS 163
 *  Pokemon Hash Table
 *  This program allows you to search for pokemon and pokemon related terms via a hash table
 *  and return data about the pokemon or term
*/

// include header file
#include "proj3_header.h"


// pokemon constructur sets all pointers in object struct to NULL
pokemon::pokemon()
{
   name = NULL;
   background = NULL;
   evolveName = NULL; 
   type = NULL;
}


// pokemon destructuor deallocates all dynamic memory for the object
pokemon::~pokemon()
{
    if(name)
        delete [] name;
    if(background)
        delete [] background;
    if(evolveName)
        delete [] evolveName;
    if(type)
        delete [] type;
}


// region constructor sets all pointers in region object to NULL
region::region()
{
    name = NULL;
    pokemonsHere = NULL;
}


// region destrutor deletes all dynmaic memory for a region object
region::~region()
{
    if(name)
        delete [] name;
    if(pokemonsHere)
        delete [] pokemonsHere;
}


// terminology constructor sets all pointers in object to NULL
terminology::terminology()
{
    word = NULL;
    definition = NULL;
}


// terminology destructor deletes all dynamic memory for a terminology object
terminology::~terminology()
{
    if(word)
        delete [] word;
    if(definition)
        delete [] definition;
}


// node constructur sets all data pointers in node to NULL
node::node()
{
   poke = NULL;
   reg = NULL;
   term = NULL;
   next = NULL;
}


// node destructor deletes all dynamic memory from node object
node::~node()
{
    if(poke)
        delete poke;
    if(reg)
        delete reg;
    if(term)
        delete term;
}


// default h_table constructor sets a size of the array of head pointers to whatever
// is spcified in header file, and then sets all head pointers to NULL
h_table::h_table()
{
    // make new array of head pointers size of global constant in header file
    hashTable = new node*[defConsArrSize];
    hashTableSize = defConsArrSize;
    
    for(int i = 0; i < defConsArrSize; i++)
    {
        hashTable[i] = NULL;
    }

}


// this non default constructur takes an argument specified by user as the arrsize of the array of heads.
// user are alerted that this MUST BE A PRIME NUMBER!!!! This can be played with when running the program
// different times to see how array Size might affect chaining/collisions
h_table::h_table(int tableSize)
{
    // make new array of head pointers to size specified by user
    hashTable = new node*[tableSize];
    hashTableSize = tableSize;

    for(int i = 0; i < tableSize; i++)
    {
        hashTable[i] = NULL;
    }
}


// desturctor for the h_table class traverses through the the array of head pointers
// and if they are not NULL it traverses through the LLL and deletes all nodes.  Once
// this is done the array of heads array is deleted
h_table::~h_table()
{
    node *temp, *curr;

    for(int i = 0; i < hashTableSize; i++)
    {
        if(hashTable[i] != NULL)
        {
            curr = hashTable[i];
            while(curr != NULL)
            {
                temp = curr;
                curr = curr -> next;
                delete temp;
            }
        }
    }
    delete [] hashTable;
}


// this function will never return an error flag, it takes the keyword from either a text file or from the client and performs a 
// hash on the c-string to create an index for the hash table. Other fucntions will call this hash to either add data to the hash 
// table or to query the hash table for data.
int h_table::hashFunction(char keyword [])
{
    int key = 3;
    int keywordLength = strlen(keyword);
    if (keyword == NULL)
        return -1;
    for(int i = 0; i < keywordLength; i++)
    {
        key *= keyword[i];
    }
    if (key < 0)
        key = key * -1;
    return key % hashTableSize;
}


//
int h_table::loadData(char filePath [])
{
   // local variables
   ifstream inFile;
   int hashIndex, count = 0;
   char checkType;
   char tempStr[strSize];
   node * temp;

   inFile.open(filePath);

   if(!inFile.is_open())
        return 0;
   else
   {
        inFile.get(checkType);
        inFile.ignore(256, '\n');
        while (!inFile.eof())
        {
            // if type pokemon is being read from data file
            if (checkType == 'p')
            {
                inFile.getline(tempStr, strSize);
                hashIndex = hashFunction(tempStr); 
                if (hashIndex == -1)
                    return 0;
                temp = new node;
                temp -> poke = new pokemon;
                temp -> poke -> name = new char[strlen(tempStr) + 1];
                strcpy(temp -> poke -> name, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> poke -> background = new char[strlen(tempStr) + 1];
                strcpy(temp -> poke -> background, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> poke -> evolveName = new char[strlen(tempStr) + 1];
                strcpy(temp -> poke -> evolveName, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> poke -> candy = atoi(tempStr);
                inFile.getline(tempStr, strSize);
                temp -> poke -> pokedex = atoi(tempStr);
                inFile.getline(tempStr, strSize);
                temp -> poke -> type  = new char[strlen(tempStr) + 1];
                strcpy(temp -> poke -> type, tempStr);
                // this ignores blank lines inbetween data blocks
                inFile.ignore(256, '\n');
                temp -> next = hashTable[hashIndex];
                hashTable[hashIndex] = temp;
                ++count;
                inFile.get(checkType);
                inFile.ignore();
            }
            // if type region is bering read from data file
            else if (checkType == 'r')
            {
                inFile.getline(tempStr, strSize);
                hashIndex = hashFunction(tempStr);
                if (hashIndex == -1)
                    return 0;
                temp = new node;
                temp -> reg = new region;
                temp -> reg -> name = new char[strlen(tempStr) + 1];
                strcpy(temp -> reg -> name, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> reg -> pokemonsHere = new char[strlen(tempStr) + 1];
                strcpy(temp -> reg -> pokemonsHere, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> reg -> numberOfPokemons = atoi(tempStr);
                // skips blank lines in between data blocks
                inFile.ignore(256, '\n');
                temp -> next = hashTable[hashIndex];
                hashTable[hashIndex] = temp;
                ++count;
                inFile.get(checkType);
                inFile.ignore();
            }
            // if type term is being read from data file
            else if (checkType == 't')
            {
                inFile.getline(tempStr, strSize);
                hashIndex = hashFunction(tempStr);
                if (hashIndex == -1)
                    return 0;
                temp = new node;
                temp -> term = new terminology;
                temp -> term -> word = new char[strlen(tempStr) + 1];
                strcpy(temp -> term -> word, tempStr);
                inFile.getline(tempStr, strSize);
                temp -> term -> definition = new char[strlen(tempStr) + 1];
                strcpy(temp -> term -> definition, tempStr);
                // skips blank lines between data blocks
                inFile.ignore(256, '\n');
                temp -> next = hashTable[hashIndex];
                hashTable[hashIndex] = temp;
                ++count;
                inFile.get(checkType);
                inFile.ignore();
            }
        }
        return count;
   }
}


// this displays all data on each node if it exists, this is a check to see if i read in data correctly
// and to look at how well my hash function works to minimize collisions and clustering
int h_table::displayChainLength(int & total)
{
    // local variables
    node * curr;
    total = 0;
    
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            int count = 0;
            curr = hashTable[i];
            while(curr != NULL)
            {
                curr = curr -> next;   
                ++count;
            }
            total += count;
            cout << "Chain length at index " << i << " is " << count << endl;
        }
    }
    return 1;
}


// this function takes argument from client and hashes the keyword sent in to try
// to find a match on the hash table, it first checks if the keyword is at head
// and if it is and and head is the only node on that LLL it deletes head, if it is not
// then the LLL list will be traversed with a previous pointer dragging behind, and if a match
// is found then it will link around the deleted node, if no match is found error flag is thrown
// back to client
int h_table::removeNode(char keyword[])
{
    // local variable
    int matchFlag = 0;
    int hashIndex;
    node * temp, *prev;

    hashIndex = hashFunction(keyword); 
    temp = hashTable[hashIndex];
    if (temp == NULL)
        return 0;
    else
    {
        // check head for match on keyword @ poke pointer
        if (temp -> poke != NULL && temp -> next == NULL)
        {
            if (strcmp(keyword,temp->poke->name)==0)
            {
                delete temp;
                hashTable[hashIndex] = NULL;
                matchFlag++;
            }
        }
        // check head for match on keyword @ region pointer
        if (temp -> reg != NULL && temp -> next == NULL)
        {
            if (strcmp(keyword,temp->reg->name)==0)
            {
                delete temp;
                hashTable[hashIndex] = NULL;
                matchFlag++;
            }
        }
        // check head for match on keyword @ terminology pointer
        if (temp -> term != NULL && temp->next == NULL)
        {
            if (strcmp(keyword,temp->term->word)==0)
            {
                delete temp;
                hashTable[hashIndex]=NULL;
                matchFlag++;
            }
        }
        //else traverse the LLL, and see if we can find a match,
        //if we do we delete the node and use the previous pointer to link
        //around the deleted node or to set the end of the LLL to NULL
        else
        {
            prev = hashTable[hashIndex];
            temp = prev -> next;
            // check head for match on keyword @ poke pointer
            while(temp != NULL)
            {
                if (temp -> poke != NULL)
                {
                    if (strcmp(keyword,temp->poke->name)==0)
                    {
                        prev -> next = temp -> next;
                        delete temp;
                        matchFlag++;
                    }
                }                        
                if (temp -> reg != NULL)
                {
                    if (strcmp(keyword,temp->reg->name)==0) 
                    {
                        prev -> next = temp -> next;
                        delete temp;
                        matchFlag++;
                    }
                }
                if (temp -> term != NULL)
                {
                    if (strcmp(keyword,temp->term->word)==0)
                    {
                        prev -> next = temp -> next;
                        delete temp;
                        matchFlag++;
                    }
                }
                prev = prev -> next;
                temp = temp -> next;
            }
            // if traveresed LLL and no match found and as result no nodes deleted
            // throw error flag to client
            if (matchFlag == 1)
                return 1;
            return 0;
        }
    }
}


//  display key data takes an agrument from the client and hashes the keyword from the client
//  to get appropriate index on the hash table, we then traverse the LLL at that index and check
//  if there is a match for the keyword passed in by the client via strcmp, if we find a match
//  we print all of the data of the object at that location
int h_table::displayKeyData(char keyword [])
{
    // local variables
    int hashIndex;
    node * temp;

    // hash on keyword from client
    hashIndex = hashFunction(keyword);
    temp = hashTable[hashIndex];

    // traverse LLL and search for match to print data
    while(temp != NULL)
    {
        if (temp -> poke != NULL)
        {
            if (strcmp(keyword,temp->poke->name)==0)
            {
                cout << endl << "here is the data for \"" << keyword << "\"" << endl
                     << "NAME: " << temp -> poke -> name << endl
                     << "BACKGROUND: " << temp -> poke -> background << endl
                     << "EVOLVE NAME: " << temp -> poke -> evolveName << endl
                     << "CANDY TO EVOLVE: " << temp -> poke -> candy << endl
                     << "POKEDEX # " << temp -> poke -> pokedex;
                return 1;
            }
        }                        
        if (temp -> reg != NULL)
        {
            if (strcmp(keyword,temp->reg->name)==0) 
            {
                cout << endl << "here is the data for \"" << keyword << "\"" << endl
                     << "NAME: " << temp -> reg -> name << endl
                     << "POKEMON IN AREA: " << temp -> reg -> pokemonsHere << endl
                     << "NUMBER OF POKEMON IN AREA: " << temp -> reg -> numberOfPokemons;
                return 1;
            }
        }
        if (temp -> term != NULL)
        {
            if (strcmp(keyword,temp->term->word)==0)
            {
                cout << endl << "here is the data for \"" << keyword << "\"" << endl
                     << "WORD: " << temp -> term -> word << endl
                     << "DEFINITION: " << temp -> term -> definition;
                return 1;
            }
        }
        temp = temp -> next;
    }
    // if not match is found throw error flag to the client
    return 0;
}
