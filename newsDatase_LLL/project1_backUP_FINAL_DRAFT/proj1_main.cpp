/*
 *  Ian O'Brien
 *  CS163
 *  Project 1 - News Database
 *  Sources: ?????????????????????????
*/

#include "proj1.h"


int main()
{
    news myNews; // instantiate object and call constructor

    // local variables
    char menuSelect;
    char userTitle[strSize];
    char userTopic[strSize];
    char userDescription[strSize];
    char userTimeStamp[strSize];
    char userSource[strSize];
    char updateTitle[strSize];
    char updateDescription[strSize];
    char removeTitle[strSize];
    char userSetTopic[strSize];
    int errorCheck;

    // application introduction
    cout << "\n Welcome to Ian's News Application.\n";
    
    while(toupper(menuSelect) != 'Q')
    {
        cout << "\n\nWhat would you like to do?\n"
             << "(A)dd a news story\n(U)pdate a news story\n(S)display topic of interest\n(D)isplay all news by time\n"
             << "(M)display most recent news\n(R)emove old news\n(B)remove news by title\n"
             << "(Q)uit\n";
        cin.get(menuSelect);
        cin.ignore();

        switch(toupper(menuSelect))
        {
            case 'A':
                cout << "title of new story: ";
                cin.getline(userTitle, strSize);
                cout << "topic of new story: "; 
                cin.getline(userTopic, strSize);
                cout << "description of new story (250 char. limit): ";
                cin.getline(userDescription, strSize);
                cout << "how old is this news? (XX hours): ";
                cin.getline(userTimeStamp, strSize);
                cout << "source of news? (FOX12, KATU, etc.): ";
                cin.getline(userSource, strSize);
                errorCheck = myNews.addArticle(userTitle, userTopic, userDescription, userTimeStamp, userSource);
                if (errorCheck == 0)
                    cout << "\n\tWAS NOT ABLE TO ADD ARTICLE TO DATABASE";
                else 
                    cout << "\n\tSUCESSFULLY ADDED ARTICLE TO DATABASE";
                break;
            case 'U':
                cout << "What is the title of the article you want to update? ";
                cin.getline(updateTitle, strSize);
                cout << "please Type article update: (250 char. max): ";
                cin.getline(updateDescription, strSize);
                errorCheck = myNews.updateArticle(updateTitle, updateDescription);
                if (errorCheck == 0)
                    cout << "\n\tNO MATCH FOUND WITH TITLE: " << "\"" << updateTitle << "\"";
                else
                    cout << "\n\tSUCESSFULLY UPDATED ARTICLE IN DATABASE";
                break;
            case 'S':
                cout << "What Topic of news would you like to view? ";
                cin.getline(userSetTopic, strSize);
                errorCheck = myNews.setAndDisplayTopic(userSetTopic);
                if (errorCheck == 0)
                    cout << "\n\tEITHER NO STORIES MATCHIG TOPIC OR DATABASE EMPTY.";
                break;
            case 'D':
                errorCheck = myNews.displayAll();
                if (errorCheck == 0)
                    cout << "\n\tNO NEWS TO DISPLAY";
                break;
            case 'M':
                errorCheck = myNews.displayRecent();
                if (errorCheck == 0)
                    cout << "\n\t EITHER NO NEWS IN DATABASE OR NO NEW NEWS IN THE PAST 24 HOURS.";
                break;
            case 'R':
                errorCheck = myNews.removeOld();
                if (errorCheck == 0)
                    cout << "\n\tEITHER NO NEWS IN DATABASE OR NO NEWS OLDER THAN 24 HOURS TO DELETE";
                else 
                    cout << "DELETED ALL NEWS OLDER THAN 24 HOURS FROM DATABASE";
                break;
            case 'B': 
                cout << "Title of news story to be removed: ";
                cin.getline(removeTitle, strSize);
                errorCheck = myNews.removeTitle(removeTitle);
                if (errorCheck == 1)
                    cout << "\n\tSUCESSFULLY REMOVED STORY FROM DATABASE";
                else
                    cout << "\n\tEITHER LIST IS EMPTY OR NO MATCHING TITLE IN DATABASE";
                break;
            case 'Q':
                cout << "\t QUITTING PROGRAM...\n";
                break;
            default:
                cout << "\t INVALID MENU SELECTION!\n";
                break;
        }
    }
    // end of application
    return 0;
}
