
//************************************************************************
//
//  CHOOSE YOUR OWN ADVENTURE GAME
//  Portland State University :: Computer Science 202
//	APRIL 30, 2014
//  AMANDA RYMAN :: amanda.ryman@gmail.com
//  
//************************************************************************
//  
//	This is an adventure game in which the player chooses to go one 
//  way or another and picks up objects along the way.
//
//************************************************************************
//
//  You are viewing 'object.h'
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
//************************************************************************

#include "game.h"
using namespace std;

//************************************************************************
//  GAME CLASS
//
//	This is the 'master' class, which is to say that it has a map object and a
//  pointer to players and therefore moderates game play (as opposed to doing this
//  in 'main'). 
//************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR

game::game(void) :
    players(0)
{}

//**********************************************************************************
//  CONSTRUCTOR

game::game(const int num_of_players, const char * filename) :
    world(filename),
    p_num(num_of_players),
    l_num(world.levelcount())
{
// Read in all the players:
    readplayers();

// Create the array of ints which tells us where everyone is:
    resetwhere();

// CHECK THAT THE FILE LOADED: only for verifying that the external file loaded
//  correctly -- comment out for user usage
    //world.displaylevels();
}


//**********************************************************************************
//  CREATE THE PLAYER ARRAY:
//	Create the array of players of various types, reading in from user:

void game::readplayers(void)
{
// Create a player object to read player data into:
    player p_info;
    char tempword[100];
    int tempnum = 0;

// Create an array of collection pointers as big as the number of players:
    players = new collection * [p_num];

// Read in the players' info until we have read for all players:
    char response = '\0';
    for (int i=0; i<p_num; ++i)
    {
    // Get player info:
	cout << "\nENTER P" << i+1 << "'S NAME:\t";
	p_info.read(i);
    
    // Get player type:
	cout << "Player " << i+1 
	    << ", are you a Ninja [N], a Unicorn [U] or a Pirate [P]?\t";
	cin >> response;
	cin.clear();
	cin.ignore(100,'\n');
	response = toupper(response);
    // Check that the response was valid:
	while (response != 'N' && response != 'U' && response != 'P')
	{
	    cout << "\nPlease enter N, U or P:\t";
	    cin >> response;
	    cin.clear();
	    cin.ignore(100, '\n');
	    response = toupper(response);
	}
    // Put the player in the game:
	switch(response)
	{
	    case 'N': 
		cout << "\nDude, what's your favorite kind of pizza?\t";
		cin.get(tempword, 100, '\n');
		cin.ignore(1000,'\n');
		for (int j=0; j<strlen(tempword); j++)
		    tempword[j] = toupper(tempword[j]);
		players[i] = new ninja(p_info, tempword);
		break;
	    case 'P': 
		cout << "\nArrrrr, what color be yer beard?\t";
		cin.get(tempword, 100, '\n');
		cin.ignore(1000,'\n');
		for (int j=0; j<strlen(tempword); j++)
		    tempword[j] = toupper(tempword[j]);
		players[i] = new pirate(p_info, tempword);
		break;
	    case 'U': 
		cout << "\nNaaaa-a-a-a-ay! What does it smell like when the "
		    << "golden tulips"
		    << " frolic in the sunshine?\t";
		cin.get(tempword, 100, '\n');
		cin.clear();
		cin.ignore(1000,'\n');
		tempnum = 0;
		for (int j=0; j<strlen(tempword); j++)
		    ++tempnum;
		players[i] = new unicorn(p_info, tempnum);
		break;
	}
	players[i]->welcome();
	wait();
    }
}


//**********************************************************************************
//  RESET PLAYER LOCATIONS
//	Set all players back to the beginning. Called by the constructor to set up 
//  the game, and can be used to reset for another round.

void game::resetwhere(void)
{
    for (int i=0; i<6; i++)
	where[i] = 0;
}


//**********************************************************************************
//  DECONSTRUCTOR

game::~game(void)
{
// Delete the players:
    for (int i=0; i<p_num; i++)
    {	
	delete players[i];
	players[i] = NULL;
    }

// Set visits to NULL:
    resetwhere();
    p_num = 0;
}


//**********************************************************************************
//  GAME PLAY
//	Where turns are taken, levels are traversed...
//  All the while we're calling endgame() to check and see if anyone has won yet.

void game::gameplay(void)
{
// Until someone reaches the end, we'll play:
    while(!endgame())
    {
    // For each player, tell them where they're at and where they can go:
	for (int i=0; i<p_num; i++)
	{
	// As long as they aren't dead:
	    if (!done(i))
	    {
	    // Whose turn it is:
		cout << endl;
		players[i]->display();

	    // Where they are:
		cout << endl;
		world.locate(where[i]);

	    // Items found, if any:
		cout << endl;
		players[i]->additem(world.getitem(where[i]));
	 
	    // Move to the next level:
		cout << endl;
		where[i] = world.nextmove(where[i]);
		wait();
	    }
	}	 
    }
    
    whowon();

    return;
}


//**********************************************************************************
//  WAIT
//	We just showed the user some information. Wait until they hit enter to continue doing our thang.

void game::wait(void)
{
    cout << "\nPRESS [ENTER] TO CONTINUE" << endl;
    cin.get();
    return;
}


//**********************************************************************************
//  IS THE GAME OVER YET?
//	Look through the array 'where' to see if anyone is at the last level.

bool game::endgame(void) const
{
    for (int p=0; p<p_num; p++)
    {
    // If anyone has not reached the end level, return false:
	if (where[p] < l_num-1)
	    return false;
    }
// Otherwise everyone is done:
    return true;
}


//**********************************************************************************
//  PLAYER DONE?
//	If this player isn't at the end yet, they get to keep playing:

bool game::done(int p) const
{
    if (where[p] < l_num-1)
	return false;
    return true;
}


//**********************************************************************************
//  WHO WON?
//	Display end stats and the winner.

void game::whowon(void) const
{
    int winner = 0;
    int high_score=0;

    for (int i=0; i<p_num; i++)
    {	
	
	cout << endl << endl;
	players[i]->displayfinal();
	if (players[i]->getpts() > high_score)
	{
	    high_score = players[i]->getpts();
	    winner = i;
	}
    }
    
    cout << endl << endl 
	<< "****************************************************************" 
	<< endl << "\t\t\t\t   ";
    cout << endl
	<< "                _" << endl
	<< "              _\\ /_" << endl
	<< "              >_X_< " << endl
	<< "       .---._  /_\\  _.---.\t";
    players[winner]->displayname();
    cout << endl
	<< "     /`.---._`{/ \\}`_.---.`\\" << endl
	<< "    | /   ___`{\\_/}`___   \\ |" << "\t  CONGRATULATIONS" << endl
	<< "    \\ \\.\"`*  `\"{_}\"`  *`\"./ /" << endl
	<< "     \\ \\  )\\  _\\ /_  /(  / /" << endl
	<< "      \\ *<()( >_X_< )()>* /" << "\tYOU ARE THE WINNER!" << endl
	<< "       |._)/._./_\\._.\\(_.|" << endl
	<< "       |() () () () () ()|" << endl
	<< "       <<o>><<o>><o>><<o>>" << endl
	<< "      `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`" << endl
	<< "****************************************************************" 
	<< endl; 



    return;
}


//**********************************************************************************
//  END CODE
//**********************************************************************************

