
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
//  You are viewing 'object.cpp'
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

#include "object.h"
using namespace std;
using namespace stuff;

//**********************************************************************************
//  OBJECT CLASS
//	
//	Object is the base class of node. Object's data member is a char pointer
//  which holds the name of the item. 
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

object::object(void)
{}


//**********************************************************************************
//  CONSTRUCTOR :

object::object(const char * new_obj, const char * new_desc, int points) :
    pts(points)
{
    if (new_obj && new_desc)
    {
	name = new char[strlen(new_obj)+1];
	strcpy(name, new_obj);

	description = new char[strlen(new_desc)+1];
	strcpy(description, new_desc);
    }
}


//**********************************************************************************
//  CONSTRUCTOR :

object::object(const object & new_object)
{
    name = new char[strlen(new_object.name)+1];
    strcpy(name, new_object.name);
    
    description = new char[strlen(new_object.description)+1];	
    strcpy(description, new_object.description);

    pts = new_object.pts;
}



//**********************************************************************************
//  DECONSTRUCTOR

object::~object(void)
{
    if (name)
	delete [] name;
    if (description)
	delete [] description;
    pts = 0;
}


//**********************************************************************************
//  DISPLAY OBJECT NAME

void object::display(void) const
{
    cout << name;
}


//**********************************************************************************
//  DISPLAY FULL OBJECT INFO

void object::displayfull(void) const
{
    cout << description << endl;
}


//**********************************************************************************
//  IS DUPLICATE?
//	Determine whether the object being passed in already exists.
//  If the object names are the same, return false. Otherwise return true.

bool object::duplicate(const object & to_add) const
{
    if (strcmp(name, to_add.name))
	return false;
    return true;
}


//**********************************************************************************
//  GET POINTS
//	Return the number of points that this object is worth.

int object::getpoints(void)const
{
    return pts;
}


//**********************************************************************************
//  NODE CLASS
//
//	Node is a derived class of object -- it is an object and also contains the
//  pointers to form a doubly linked list of objects. This node class is one of two 
//  node classes in this program and are differentiated by namespaces. 
//	The collection class (which 'is a' player) contains a head pointer to a
//  linked list of objects.
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : 

node::node(void) : 
    next(0),
    prev(0)
{}


//**********************************************************************************
//  CONSTRUCTOR : SET NAME

node::node(const object & new_obj) :
    object(new_obj),
    next(0),
    prev(0)
{}


//**********************************************************************************
//  DECONSTRUCTOR

node::~node(void) 
{
    next = NULL;
    prev = NULL;
}


//**********************************************************************************
//  GO FORWARD
//	Returns the node's next pointer.

node *& node::go_forward(void)
{
    return next;
}


//**********************************************************************************
//  GO BACK
//	Returns the node's previous pointer.

node *& node::go_back(void)
{
    return prev;
}


//**********************************************************************************
//  CONNECT FORWARDS
//	Sets the node's next pointer to the node pointer passed in as an arg

void node::connect_forward(node * connection)
{
    next = connection;
    return;
}


//**********************************************************************************
//  CONNECT BACKWARDS
//	Sets the node's previous pointer to the node pointer passed in as an arg

void node::connect_back(node * connection)
{
    prev = connection;
    return;
}



//**********************************************************************************
//  END CODE
//**********************************************************************************

