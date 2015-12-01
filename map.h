
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
//  You are viewing 'map.h'
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
//	GAME has a MAP
//  Local scale:
//	MAP has LEVELS which have pointers to NODES which are EDGES.
//	each LEVEL also has an OBJECT.
//
//  Map class contains a pointer to an array of level pointers. 
//  Each level has a pointer to a linear linked list of edge nodes, as well as an 
//  object.
//
//**********************************************************************************

#ifndef MAP_H
#define MAP_H
#include <cstring>
#include <iostream>
#include "object.h"


class edge
{
    public: 
	edge(void);
	edge(const int, const char[], const char[]);
	edge(const edge &);
	~edge(void);
	void display(void) const;
	void displaytrip(void) const;
    protected:
	int index;
	char * description;
	char * trip;
};


class node : public edge
{
    public:
	node(void);
	node(const int, const char[], const char[]);
	node(const edge &);
	~node();
	node *& go_next(void);
	int getindex(void) const;
    protected:
	node * next;
};


class level
{
    public:
	level(void);
	level(const char[], const char[]);
	level(const level &, const stuff::object &);
	~level(void);
	void display(void) const;
	void display(node*&)const;
	void displayname(void) const;
	bool addedge(const edge &);
	bool addedge(node *&, const edge &);
	stuff::object & getitem(void);
	int whereto(void);
	void whereto(node *&);
	bool isvalid(int);
	bool isvalid(node *&, int);
	void thistrip(int);
	void thistrip(node *&, int);
    protected:
	node * head;
	char * name;
	char * description;
	stuff::object * item;
};


class map
{
    public:
	map();
	map(const char*file);
	~map();
	bool displaylevels(void) const;
	int levelcount(void) const;
	stuff::object & getitem(int);
	void locate(int);
	int nextmove(int);
    protected:
	level * vertices[20];
};

#endif


