/* 
  * Ian O'Brien
  * CS163 Project 2
  * Card Game w/ shuffle (using random number generator)
*/

#include "project2.h"


// constructur sets head of LLL of arrays, index, and card count to NULL
// also goes through card pointer array and sets each pointer to NULL
// it also declares the length of the shuffle pointer array to Global const deck size
// so it can be changed as needed (more/less card data in .txt file)
game::game()
{
    index = 0;
    head = NULL;
    shuffleArray=new card*[deckSize];     
    for(int i = 0; i < deckSize; i++)
    {
        shuffleArray[i] = NULL;
    }
}


// desctutor will free all memory allocated dynamically, this includes the pointer array for the shuffleing of cards
// as well as all new nodes and dynamic arrays built for the cards, checked with valgrind and no memory leaks detected
game::~game()
{
    // local variables
    node *tempPtr;

    // destroys shuffle array
    for(int i = 0; i < deckSize -1; ++i)
    {
        if (shuffleArray[i] != NULL)
        {
            delete shuffleArray[i]->subject;
            delete shuffleArray[i]->question;
            delete shuffleArray[i]->answer;
            delete shuffleArray[i]->hint;
            delete shuffleArray[i];
            shuffleArray[i]=NULL;
        }
    }

    // destroys stack
    while(head!=NULL)
    {
        tempPtr = head;
        head = head->next;
        delete [] tempPtr->arrayOfCards;
        delete tempPtr;
    }
    head = NULL;
}


//this function reads the card data from the CSV .txt file to build the shuffleArray 
//of pointers, each pointer will point to a card object which will later be shuffled 
//and pushed onto the stack, this function also sets each cards visit Flag to 0, which
//will be used to check if the card has been pushed onto the stack during the shuffle function
//this function will throw error flag if bad file path for the .txt file is used and cause the 
//program to terminate
int game::setup(char filePath [])
{
    // local variables
    ifstream inFile; 
    int count = 0;
    char tempStr[strSize];
    card *tempPtr;

    inFile.open(filePath);

    if (!inFile.is_open())
        return 0;
    else
    {
        inFile.getline(tempStr, strSize, ',');
        while (!inFile.eof() && count < deckSize -1)
        {
            tempPtr = new card;
            tempPtr -> subject = new char[strlen(tempStr) +1];
            strcpy(tempPtr -> subject, tempStr);
            inFile.getline(tempStr, strSize, ',');
            tempPtr -> question = new char[strlen(tempStr) +1];
            strcpy(tempPtr -> question, tempStr);
            inFile.getline(tempStr, strSize, ',');
            tempPtr -> difficulty = atoi(tempStr);
            inFile.getline(tempStr, strSize, ',');
            tempPtr -> answer = new char[strlen(tempStr) +1];
            strcpy(tempPtr -> answer, tempStr);
            inFile.getline(tempStr, strSize, '\n');
            tempPtr -> hint = new char[strlen(tempStr) +1];
            strcpy(tempPtr -> hint, tempStr);
            tempPtr -> visitFlag = 0;
            shuffleArray[count] = tempPtr;
            ++count;
            inFile.getline(tempStr, strSize, ',');
        }
    }
    return count;
}


// this private function receieves a card pointer argument from the shuffle
// function, if a card is pushed from the shuffle function this function 
// will  the card onto the top of the stack.  if head is null a new node will be created
// and the card will be pushed into the 0th element of the LLL of arrays (now with one node).
// after head node is created the fucntion will push the next card onto the next index until 
// it reaches the max arrsize index (which is set to 5 as a global const), at that point
// a new node is added to head and a new dynamic array is built onto the node, and the new card
// is pushed to the zeroth element of the array.  this processes can be repeated as many times as needed
// depending on the deck size and available memory.  we will also set the visit flag to one to signal to
// the shuffle function that this node has been pushed onto the stack, and does not need to be visited again.
int game::addCard(card * & pushPtr) 
{
    // local variables
    node * temp; 
    
    if(head == NULL && index == 0 )
    {
        head = new node; 
        head -> next = NULL; 
        head -> arrayOfCards = new card*[arrSize];
        // set all elements of dynamic pointer array to NULL
        for(int i= 0; i < arrSize; ++i)
        {
            head -> arrayOfCards[i]=NULL;
        }
        head -> arrayOfCards[index] = pushPtr;
        pushPtr -> visitFlag = 1;
        ++index;
        return 1;
    }
    if(head != NULL && index >= 0 && index < arrSize-1)
    {
        head -> arrayOfCards[index] = pushPtr;
        pushPtr -> visitFlag = 1;
        ++index;
        return 1;
    }
    if(index == arrSize-1)
    {
        head -> arrayOfCards[index] = pushPtr;
        pushPtr -> visitFlag = 1;
        temp = new node;
        temp -> next = head;
        head = temp;
        temp -> arrayOfCards = new card*[arrSize];
        // set all elements of dymanic pointer array to NULL
        for(int i= 0; i < arrSize; ++i)
        {
            head->arrayOfCards[i]=NULL;
        }
        index = 0;
        return 1;
    }
    // index is decremented so that when cards are popped of stack during play 
    // we are starting at the top index WITH data in it, not the next empty array spot
    --index;
    return 0;
}


//this function generates a random number and mods each time through the do while loop
//so that everytime through the loop a index is referenced on the shuffle array, if a card
//its visit flag is still set to 0, it will be pushed onto the stack and the visitFlag will be
//set to 1.  each time through the loop we will traverse the array and check to see if either
//all cards have been pushed to the stack, or ther are null elements.  the function will keep
//generating random numbers, pushing cards onto the stack until all visit flags = 1 for elements
//that are not NULL
int game::shuffle()
{
    //local variables
    unsigned int pushNum;
    int flag;
    int success = 0;
    srand(time(NULL));
    rand();

    do
    {
        // generate random number and mod it to get an index
        pushNum = rand() % (deckSize);
        if(shuffleArray[pushNum] != NULL && shuffleArray[pushNum]->visitFlag == 0)
        {
            success += addCard(shuffleArray[pushNum]);   //call to my PUSH FUNCTION
        }
        // traverse the array and check all visit flags, if not all cards have been pushed onto the stack
        // then keep looping and generating random numbers until all visit flags == 1
        flag = 0;
        for(int i = 0; i < deckSize -1; i++)
        {
            if(shuffleArray[i] != NULL && shuffleArray[i] -> visitFlag == 0)
            {
                ++flag; 
            }
        }
    }while(flag != 0);
    if(success == 0)
        return 0;
    return 1;
}


//this function traverses through the LLL of arrays and prints each element of each array
//so the user can see all of the cards that remain in the stack.  if the max index is reached
//at the node it is printing from, the index is reset to 0 and the print function traverses
//to the next node unil it reaches the NULL pointer
//I SHOULD have started at the top index and then decremented the count on the array and THEN
//have traversed to the next node and done the same HOWEVER, what I did was start on the 0th element
//of the head node and then traverse down the array and then move to the next node, so this isn't the exact
//order but I have to turn this in by 7pm today.  ooops ;)e
int game::displayAllCards()
{
    // local variables
    node * tempPtr;
    int printIndex = 0;
    int cardNumber = 1;
    
    tempPtr = head;
    if(tempPtr == NULL)
        return 0;
    while(tempPtr != NULL && tempPtr->arrayOfCards[printIndex]!=NULL)
    {
        cout << "CARD # " << cardNumber << endl;
        cout << "SUBJECT: " <<  tempPtr->arrayOfCards[printIndex]->subject << endl; 
        cout << "QUESTION: " << tempPtr->arrayOfCards[printIndex]->question << endl;
        cout << "DIFFICULTY: " << tempPtr->arrayOfCards[printIndex]->difficulty << endl; 
        cout << "ANSWER: " << tempPtr->arrayOfCards[printIndex]->answer << endl;
        cout << "HINT: " << tempPtr->arrayOfCards[printIndex]->hint << endl << endl;
        ++cardNumber;
        ++printIndex;
        if(printIndex==arrSize-1)
        {
            if (tempPtr->arrayOfCards[printIndex] != NULL)
            {
                cout << "CARD # " << cardNumber << endl;
                cout << "SUBJECT: " <<  tempPtr->arrayOfCards[printIndex]->subject << endl; 
                cout << "QUESTION: " << tempPtr->arrayOfCards[printIndex]->question << endl;
                cout << "DIFFICULTY: " << tempPtr->arrayOfCards[printIndex]->difficulty << endl; 
                cout << "ANSWER: " << tempPtr->arrayOfCards[printIndex]->answer << endl;
                cout << "HINT: " << tempPtr->arrayOfCards[printIndex]->hint << endl << endl;
            }
            ++cardNumber;
            printIndex = 0;
            tempPtr = tempPtr->next;
        }
    }
    return 1;
}

//this function will pop cards off the stack, and at the same time it will print the data so the user can play the card.
//the index was decremented in the add card function so that we are starting the index at the top index WTIH data in it instead
//of the next empty array spot. if we reach the zeroth index of a node, we will traverse to the next node, and start at the 4th element
//and delete the previous array of cards, and delete the previous node, once head = NULL we will return 0 to signal to the client that we
//have played all of the cares in the deck.
int game::play()
{
    node *tempPtr;

    if(!head)
        return 0;
    if(head->arrayOfCards[index]==NULL)
        --index;
    if(index!=0)
    {
        cout << "YOU HAVE 30 SECONDS TO ANSWER THIS QUESTION: " << endl << endl;
        cout << "SUBJECT: " <<  head->arrayOfCards[index]->subject << endl; 
        cout << "QUESTION: " << head->arrayOfCards[index]->question << endl;
        cout << "DIFFICULTY: " << head->arrayOfCards[index]->difficulty << endl; 
        cout << "ANSWER: " << head->arrayOfCards[index]->answer << endl;
        cout << "HINT: " << head->arrayOfCards[index]->hint << endl;
        --index; 
        return 1;
    }
    if(index==0)
    {
        cout << "YOU HAVE 30 SECONDS TO ANSWER THIS QUESTION: " << endl << endl;
        cout << "SUBJECT: " <<  head->arrayOfCards[index]->subject << endl; 
        cout << "QUESTION: " << head->arrayOfCards[index]->question << endl;
        cout << "DIFFICULTY: " << head->arrayOfCards[index]->difficulty << endl; 
        cout << "ANSWER: " << head->arrayOfCards[index]->answer << endl;
        cout << "HINT: " << head->arrayOfCards[index]->hint << endl;
        index = arrSize - 1;
        tempPtr = head;
        head = head->next;   
        delete [] tempPtr ->arrayOfCards;
        delete tempPtr;
        return 1;
    }
}
