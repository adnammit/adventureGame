
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
//**********************************************************************************
//
// CLASS HIERARCHY:
//
//  Global scale:
//	COLLECTIONS have OBJECTS
//  Local scale:
//	NODES are OBJECTS
//  
//  The base class of this inheritance hierarchy is 'object'. 
//  A node is an object but also has a next and previous pointer. 
//
//  Nodes are connected to make a doubly linked list, which the 'collection' class
//  has a pointer to.
//
//**********************************************************************************

#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <cstring>


namespace stuff
{
class object
{
    public:
	object(void);
	object(const char *, const char *, int);
	object(const object &);
	~object(void);
	void display(void) const;
	void displayfull(void) const;
	bool duplicate(const object &) const;
	int getpoints(void) const;
    protected:
	char * name;
	char * description;
	int pts;
};

class node : public object
{
    public:
	node(void);
	node(const char * new_obj);
	node(const object &);
	~node(void);
	node *& go_forward(void);
	node *& go_back(void);
	void connect_forward(node * connection);
	void connect_back(node * connection);
    protected:
	node * next;
	node * prev;
};
}

#endif

//**********************************************************************************
//  END CODE
//**********************************************************************************

