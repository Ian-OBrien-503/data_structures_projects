/*
 *  Ian O'Brien
 *  CS163
 *  Project 1 - News Database
*/

#include "proj1.h"


// constructor
news::news()
{
    headTime = NULL;
    headTopic = NULL;
}

// destructor
news::~news()
{
    node *prev, *curr;
    if (headTime == NULL)
        return;
    prev = curr = headTime;
    while (curr != NULL)
    {
        curr = curr -> nextTime;
        delete [] prev -> title;
        delete [] prev -> topic;
        delete [] prev -> description;
        delete [] prev -> source;
        delete prev;
        prev = curr;
    }
}


// this function takes the temp pointer of type node built in addArticle function and finds out where to put it according to topic
int news::insertTopicNode(node *tempPtr)
{
    // local variables
    node *currTopic, *nTopic;

    // if life is empty make new node head
    if (headTopic == NULL)
    {
        headTopic = tempPtr;
        return 1;
    }
    // if list is NOT empty
    else
    {
        // if head is alphabetically after or eqivalent to tempPtr, make tempPtr new head
        if (strcmp (headTopic -> topic, tempPtr -> topic) >= 0)
        {
            tempPtr -> nextTopic = headTopic;
            headTopic = tempPtr;
            return 1;
        }
        else 
        {
            currTopic = headTopic;
            nTopic = headTopic -> nextTopic;
            while (nTopic != NULL)
            {
                // place new node in between two nodes
                if (strcmp(currTopic -> topic, tempPtr -> topic) <= 0 && strcmp (nTopic -> topic, tempPtr -> topic) >= 0)
                {
                    currTopic -> nextTopic = tempPtr;
                    tempPtr -> nextTopic = nTopic;
                    return 1;
                }
                // compare with next two nodes on LLL
                else
                {
                    currTopic = nTopic;
                    nTopic = nTopic -> nextTopic;
                }
            }
            // if node does not go at begininning of list, or middle, add to the end of the list
            if (nTopic == NULL)
            {
                currTopic -> nextTopic = tempPtr;
                return 1;
            }
        }
    }
    // if none of the above code executes, node was not added, return error flag
    return 0;
}


// this function takes the temp pointer of type node build in add article and finds where to add it in LLL, and adds it
int news::insertTimeNode(node *tempPtr)
{
    // local variables
    node *currTime, *nTime;

    // if list is empty make new node head
    if (headTime == NULL)
    {
        headTime = tempPtr;
        return 1;
    }
    // list is not empty, find out where to put new node
    else
    {   // if head has later time stamp then new node, make new node the head
        if (headTime -> timeStamp > tempPtr -> timeStamp)
        {
            tempPtr -> nextTime = headTime;
            headTime = tempPtr;
            return 1;
        }
        // if head has earlier time stamp than new node, find out where to put node
        else
        {
            currTime = headTime;
            nTime = headTime -> nextTime;
            while (nTime != NULL)
            {
                // place new node in between two nodes
                if (currTime -> timeStamp <= tempPtr -> timeStamp && nTime -> timeStamp >= tempPtr -> timeStamp)
                {
                    currTime -> nextTime = tempPtr;
                    tempPtr -> nextTime = nTime;
                    return 1;
                }
                // move comparison nodes down one node
                else
                {
                    currTime = nTime;
                    nTime = nTime -> nextTime;
                }
            }
            // if new node doesnt go in beginning middle or end, add to the end of the list
            if (nTime == NULL)
            {
                currTime -> nextTime = tempPtr;
                return 1;
            }
        }
    }
    // if none of the above code executes, node was not added, return error flag
    return 0; 
}


//this function prompts user from client for title, topic, description
//time-stamp, and source, passes all of these char arrays as arguments 
//to the function to be added to LLL
int news::addArticle(char userTitle[],char userTopic[],char userDescription[],char userTimeStamp[],char userSource[])
{
    // local variables
    node *tempPtr;  
    int error1, error2;

    tempPtr = new node;
    tempPtr -> title = new char [strlen(userTitle)+1];
    strcpy(tempPtr -> title, userTitle);
    tempPtr -> topic = new char [strlen(userTopic)+1];
    strcpy(tempPtr -> topic, userTopic);
    tempPtr -> description = new char [strlen(userDescription)+1];
    strcpy(tempPtr -> description, userDescription);
    tempPtr -> timeStamp = atoi(userTimeStamp);
    tempPtr -> source = new char [strlen(userSource)+1];
    strcpy(tempPtr -> source, userSource);
    tempPtr -> nextTopic = NULL;
    tempPtr -> nextTime = NULL;
    error1 = insertTimeNode(tempPtr);
    error2 = insertTopicNode(tempPtr); 
    if (error1 == 1 || error2 == 1)
        return 1;
    else 
        return 0;
}

// this is my recursive function that takes an argument of article number from the display all function in the NEWS class
// the function prints the existing node (if list is not empty) and then checks if a next node exists, if it does it calls it self
// and prints that node as well, and traverses through the whole LLL recursively
int node::recursivePrintAll(int articleNumber)
{
    cout << "ARTICLE #" << articleNumber << '\n';
    cout << "TITLE: " << title << '\n'
         << "TOPIC: " << topic << '\n'
         << "DESCRIPTION: " << description << '\n'
         << "TIMESTAMP: " << timeStamp << " hours ago" << '\n'
         << "SOURCE: " << source << "\n\n"; ++articleNumber;
    if(nextTime)
    {
        nextTime -> recursivePrintAll(articleNumber);
        return 1;
    }
    else
        return 0;
}


// this function checks if list is empty if it is not it will print the head node via calling the recursive function that is a member of the 
// node struct, 
int news::displayAll() const
{
    int articleNumber = 1;

    if(headTime==NULL)
        return 0;
    else
        headTime -> recursivePrintAll(articleNumber);
    return 1;
}


// this function only displays news from the past 24 hours, will return error flag if list is empty
int news::displayRecent() const
{
    // local variables
    node *curr;
    int articleNumber = 1, timeMatch = 0;
    
    curr = headTime;
    if (headTime == NULL)
        return 0;
    else
    {
        while (curr != NULL)
        {
            if (curr -> timeStamp < 24)
            {
                cout << "ARTICLE #" << articleNumber << '\n';
                cout << "TITLE: " << curr -> title << '\n'
                     << "TOPIC: " << curr -> topic << '\n'
                     << "DESCRIPTION: " << curr -> description << '\n'
                     << "TIMESTAMP: " << curr -> timeStamp << " hours ago" << '\n'
                     << "SOURCE: " << curr -> source << "\n\n";
                     ++timeMatch;
                     ++articleNumber;
            }
            curr = curr -> nextTime; 
        }
    }
    if (timeMatch > 0)
        return 1;
    else
        return 0;
}


// this function gets c-string argument from client to delete a node from the LLL by matching title
// if no matching title throw error flag, if scuessful return 1 and delete node
int news::removeTitle(char removeTitle[])
{
    // local variables
    node *curr, *prev;

    if (headTime == NULL)
        return 0;
    else 
    {   
        // if deleting head node
        if (strcmp(headTime -> title, removeTitle) == 0)
        {
            curr = headTime;
            headTime = headTime -> nextTime;
            delete [] curr -> title;
            delete [] curr -> topic;
            delete [] curr -> description;
            delete [] curr -> source;
            delete curr;
            return 1;
        }
        else 
        {
            prev = headTime;
            curr = headTime -> nextTime;
            while (curr != NULL)
            {
                // if match found after head and before end of list
                if (strcmp(removeTitle, curr -> title) == 0 && curr -> nextTime != NULL)
                {
                    prev -> nextTime = curr -> nextTime;
                    delete [] curr -> title;
                    delete [] curr -> topic;
                    delete [] curr -> description;
                    delete [] curr -> source;
                    delete curr;
                    return 1;
                }
                // match found at last item in LLL
                else if (strcmp(removeTitle, curr -> title) == 0 && curr -> nextTime == NULL)
                {
                    prev -> nextTime = NULL;
                    delete [] curr -> title;
                    delete [] curr -> topic;
                    delete [] curr -> description;
                    delete [] curr -> source;
                    delete curr;
                    return 1;
                }
                // if no match found traverse the list and try again
                else 
                {
                    prev = curr;
                    curr = curr -> nextTime;
                }
            }
            
        }
    }
}


// this function takes topic selected by client as argument, and tests to see if it is either
// news, traffic, or weather if it is one of these topics, this function will print all stories with matching 
// topics
int news::setAndDisplayTopic(char userSetTopic[])
{
    //local variables
    node *curr;
    int articleNumber = 0, topicMatch = 1;

    curr = headTopic;
    if (headTopic == NULL)
        return 0;
    else 
    { 
        while (curr != NULL)
        {
            if (strcmp(userSetTopic, curr->topic) == 0)
            {
                cout << "ARTICLE #" << articleNumber << '\n';
                cout << "TITLE: " << curr -> title << '\n'
                     << "TOPIC: " << curr -> topic << '\n'
                     << "DESCRIPTION: " << curr -> description << '\n'
                     << "TIMESTAMP: " << curr -> timeStamp << " hours ago" << '\n'
                     << "SOURCE: " << curr -> source << "\n\n";
                     ++topicMatch;
                     ++articleNumber;
            }
            curr = curr -> nextTopic;
        }
    }
    if (topicMatch > 0)
        return 1;
    else 
        return 0;
}

// this function deletes news that is older than 24 hours, returns error flag if list is empty
// or if list has no news older than 24 hours
int news::removeOld()
{
    //local variables
    node *curr, *prev;
    int deletedNode = 0;

    if (headTime == NULL)
        return 0;
    else
    {
        // if head is older than 24 hours
        if (headTime -> timeStamp > 24)
        {
            curr = headTime;
            headTime = NULL;
            delete [] curr -> title;
            delete [] curr -> topic;
            delete [] curr -> description;
            delete [] curr -> source;
            delete curr;
            return 1;
        }
        // if other nodes before the end of the list are older than 24 hours delete them and have prev -> next point to curr -> next
        else 
        {
            prev = headTime;
            curr = headTime -> nextTime;
            while (curr != NULL)
            {
                if (curr -> timeStamp > 24)
                {
                    // if last node is deleted, below line sets last node in LLL to NULL
                    prev -> nextTime = curr -> nextTime;
                    delete [] curr -> title;
                    delete [] curr -> topic;
                    delete [] curr -> description;
                    delete [] curr -> source;
                    delete curr;
                    curr = prev -> nextTime;
                    ++deletedNode;
                }
                // traverse down the list
                else 
                {
                    prev = curr;
                    curr = curr -> nextTime;
                }
            }
        }
        if (deletedNode > 0)
            return 1;
        else
            return 0;
    }
}


// this function takes user prompted title and description from client as argument
// finds matching article by title and clobbers existing description with description argument
int news::updateArticle(char updateTitle[],char updateDescription[])
{
    // local variables
    node *curr;

    curr = headTime;
    while (curr != NULL)
    {
        if (strcmp(updateTitle, curr -> title) == 0)
        {
            delete [] curr -> description;
            curr -> description = new char[strlen(updateDescription)+1];
            strcpy(curr -> description, updateDescription);
            return 1;
        }
        curr = curr -> nextTime;
    }
    // if not match found for title return error flag
    return 0;
}

