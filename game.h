
//**********************************************************************************
//
//  CHOOSE YOUR OWN ADVENTURE GAME
//  Portland State University :: Computer Science 202
//	APRIL 30, 2014
//  AMANDA RYMAN :: amanda.ryman@gmail.com
//  
//**********************************************************************************
//  
//	This is an adventure game in which the player chooses to go one way or 
//  another and picks up objects along the way.
//
//**********************************************************************************
//
//  You are viewing 'game.h'
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
//
// CLASS HIERARCHY:
//
//  Global scale:
//	GAME has a MAP and an array of COLLECTIONS
//
//  Game has only a 'has a' relationship with map and collection.
//  It contains a bit of other info (an array to keep track of player location,
//  a number of levels and a number of players) to do its job: moderating game flow.
//
//**********************************************************************************


#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "player.h"

using namespace stuff;


class game
{
    public:
	game(void);
	game(const int p_num, const char* file);
	~game(void);
	void readplayers(void);
	void resetwhere(void);
	void resetvisits(void);
	void gameplay(void);
	void wait(void);
	bool endgame(void) const;
	bool done(int) const;
	void whowon(void) const;
    protected: 
	map world;
	collection ** players;
	int where[6];
	int p_num;
	int l_num;
};

#endif

//**********************************************************************************
//  END CODE
//**********************************************************************************

