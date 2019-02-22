/*
 * Ian O'Brien
 * CS163 Project 2
 * Card Game w/ shuffle (using random number generator)
*/

#include "project2.h"

int main()
{
    game myGame; // instantiate object and call constructor

    // local variables
    char menuSelect;
    int errorCheck;
    char filePath[strSize];
    

    // application introduction
    cout << '\n' << "Welcome to Ian's Trivial Pursuit Game\n";
    cout << '\n' << '\n' << "What .txt file would you like to use to build your deck of cards? ";
    cin.getline(filePath,strSize);
    errorCheck = myGame.setup(filePath);
    if(errorCheck == 0)
    {
        menuSelect = 'Q';
        cout << "\n\t bad file path specified, terminating program \n\n";
    }
    else
        cout << errorCheck << endl << "cards added ,please Setup game to shuffle cards and prepare for play.";
    
    
    while(toupper(menuSelect) != 'Q')
    {
        cout << "\n\nWhat would you like to do?\n"
             << "(S)et-up game, (D)isplay all cards, (P)lay, or (Q)uit\n";
        cin.get(menuSelect);
        cin.ignore();

        switch(toupper(menuSelect))
        {
            case 'S':
                errorCheck = myGame.shuffle();
                if(errorCheck == 0)
                    cout << "\nGAME NOT SET-UP,PLEASE CONSULT PROGRAMMER WHO MADE THIS\n";
                else
                    cout << "\nGAME IS READY TO PLAY!!!";
                break;
            case 'D':
                errorCheck = myGame.displayAllCards();
                if(errorCheck==0)
                    cout << "\nYOU MUST FIRST ADD CARDS TO THE DECK TO DISPLAY THEM.";
                break;
            case 'P':
                errorCheck = myGame.play();
                if(errorCheck == 0)
                    cout << "\nEITHER GAME HAS NOT BEEN SETUP OR ALL CARDS HAVE BEEN PLAYED!";
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
