
//**********************************************************************************
//
//  CHOOSE YOUR OWN ADVENTURE GAME
//  Portland State University :: Computer Science 202
//  APRIL 30, 2014
//  AMANDA RYMAN :: amanda.ryman@gmail.com
//  
//**********************************************************************************
//  
//  This is an adventure game in which the player chooses to go one way or 
//  another and picks up objects along the way.
//
//**********************************************************************************
//
//  You are viewing 'main.cpp'
//  
//  Associated files:
//  - main.cpp
//  - game.h
//  - game.cpp
//  - player.h
//  - player.cpp
//  - map.h
//  - map.cpp
//  - object.h
//  - object.cpp
//  - game.txt
//  
//**********************************************************************************

#include "game.h"
#include "map.h"
using namespace std;

//**********************************************************************************
// MAIN FUNCTION DECLARATIONS:

bool more(void);
int getNum(void);


//**********************************************************************************
//  MAIN -- CLIENT/CALLING ROUTINE 
//**********************************************************************************


int main()
{

//**********************************************************************************
// SET UP SOME VARIABLES:

// The external file containing all of the game content. Can easily be set up to 
//  be read in from the user if they would like to select a different game file.
    char filename[] = "game.txt";

    cout << "\n\nSUPER SEGATENDO" << endl;

    int p_num = 0;

//**********************************************************************************
// CREATE AND BEGIN A GAME SESSION:

    do
    {
    // Get the number of players:
	p_num = getNum();

    // Create the game:
	game play(p_num, filename);

    // Play the game:
	play.gameplay();

    // Play again?
	cout << "\nPlay again? [Y/N]\t";

    }while (more());


//**********************************************************************************
// ALL DONE!
    return 0;
}


//**********************************************************************************
//  MAIN FUNCTION DEFINITIONS: 
//**********************************************************************************


//**********************************************************************************
//  ENTER MORE DATA
//     OR CONTINUE?
//
// 	More() returns true to continue the
// 	loop; returns false to quit

bool more(void)
{
    char reply='\0';
    cin >> reply;
    cin.ignore(100,'\n');
    if (tolower(reply)=='y')
	return true;
    return false;
}


//**********************************************************************************
//  GET NUM OF PLAYERS
//	
//	Prompt user to enter number of players. Keep asking until a number between
//  one and 6 is entered.

int getNum(void)
{
    int num = 0;
    cout << "\nHow many players? [1-6]\t";
    cin >> num;
    cin.clear();
    cin.ignore(100,'\n');

    while (num < 1 || num > 6)
    {
	cout << "\nPlease enter a number between 1 and 6:\t";
	cin >> num;
	cin.clear();
	cin.ignore(100,'\n');
    }
    return num;
}



//**********************************************************************************
// SMILE. YOU DONE!
//**********************************************************************************

