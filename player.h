
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
//  You are viewing 'player.h'
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
//  CLASS HIERARCHY:
//
//  Global scale:
//	GAME has COLLECTIONS which have OBJECTS
//  Local scale:
//	PIRATES, NINJAS and UNICORNS are COLLECTIONS which are PLAYERS
//  
//  The base class of this inheritance hierarchy is 'player' which contains basic
//  information about our player, such as score, name and their player number.
//
//  The derived class of player is 'collection', which serves as a 'hub' class for 
//  the three other classes: 'pirate', 'unicorn' and 'ninja'. 'Collection' 
//  includes a pointer to a doubly linked list of objects and several virtual 
//  functions for the derived classes to use. 
//  
//  The class 'map' has a pointer to an array of collection pointers which point
//  to members of the derived classes -- we never actually create a collection item.
//
//**********************************************************************************


#ifndef PLAYER_H
#define PLAYER_H
#include "object.h" 
namespace stuff
{

class player
{
    public:
	player(void);
	player(const player &);
	~player(void);
	void read(const int);
	void addpts(int to_add);
	void displaypts(void) const;
	int getpts(void) const;
    protected:
	int score;
	char * a_name;
	int p_num;	
};


class collection : public player
{
    public:
	collection(void);
	collection(const player &);
	virtual ~collection(void);
	void destroy(void);
	virtual void display(void) const = 0;
	virtual void displayname(void) const = 0;
	virtual void welcome(void) const = 0;
	virtual void displayfinal(void) const = 0;
	void displayitems(void) const;
	void additem(const object &);
	bool duplicate(const object &) const;
	void pickup(const object &);
    protected:
	node * head;
};

class ninja : public collection
{
    public:
	ninja(void);
	ninja(const player &, char*);
	~ninja(void);
	void display(void)const;
	void displayname(void)const;
	void welcome(void)const;
	void displayfinal(void) const;
    protected:
	char * pizza;
};


class pirate : public collection
{
    public:
	pirate(void);
	pirate(const player &, char*);
	~pirate(void);
	void display(void)const;
	void displayname(void)const;
	void welcome(void)const;
	void displayfinal(void) const;
    protected:
	char * beard;

};


class unicorn : public collection
{
    public:
	unicorn(void);
	unicorn(const player &, int);
	~unicorn(void);
	void display(void)const;
	void displayname(void)const;
	void welcome(void)const;
	void displayfinal(void) const;
    protected:
	int magic;
};
}

#endif

