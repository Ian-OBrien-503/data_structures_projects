/*
 *  Ian O'Brien
 *  CS163
 *  Project 1 - News Database
 *  Sources: ?????????????????????????
*/


#ifndef project1_h_
#define project1_h_


// preprocessor directives
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdlib>
using namespace std;


// global constants
const int strSize = 250;


// struct definition
// info contained in each node of LLL
// each node contains two next pointers to sort LLL by title and by topic
struct node
{
    char *title;
    char *topic;
    char *description;
    int timeStamp;
    char *source;
    node *nextTime;
    node *nextTopic;
    int recursivePrintAll(int articleNumber);
};


// class defintion
class news
{
public:
    news();
    ~news();
    int addArticle(char userTitle[],char userTopic[],char userDescription[],char userTimeStamp[],char userSource[]);
    int updateArticle(char updateTitle[],char updateDescription[]);
    int setAndDisplayTopic(char userSetTopic[]);
    int displayAll() const;
    int displayRecent() const;
    int removeOld(); 
    // this is the extra function I added
    int removeTitle(char userTitle[]);
private:
    //int displayAll(node *headTime);
    int insertTimeNode(node *tempPtr);
    int insertTopicNode(node *tempPtr);
    node *headTopic;
    node *headTime;
};

#endif // proj1.h
