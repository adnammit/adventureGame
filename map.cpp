
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
//  You are viewing 'map.cpp'
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

#include "map.h"
#include <fstream> 
#include <iostream>
using namespace std;

//**********************************************************************************
//  EDGE CLASS
//
//	Contains an index for the next possible levels accessible from a given 
//  vertex. Edge is the base class of node.
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

edge::edge(void) :
    index(0),
    description(0),
    trip(0)
{}


//**********************************************************************************
//  CONSTRUCTOR
//	Set the data member index to the new value:

edge::edge(const int new_index, const char new_desc[], const char new_trip[]) : 
    index(new_index)
{
    if (new_desc)
    {
	description = new char[strlen(new_desc)+1];
	strcpy(description, new_desc);
    }
    if (new_trip)
    {
	trip = new char[strlen(new_trip)+1];
	strcpy(trip, new_trip);
    }
}



//**********************************************************************************
//  CONSTRUCTOR
//	Set the data member index to the new value:

edge::edge(const edge & new_edge) : 
    index(new_edge.index)
{
    if (new_edge.description)
    {
	description = new char[strlen(new_edge.description)+1];
	strcpy(description, new_edge.description);
    }
    if (new_edge.trip)
    {
	trip = new char[strlen(new_edge.trip)+1];
	strcpy(trip, new_edge.trip);
    }

}


//**********************************************************************************
//  DECONSTRUCTOR

edge::~edge(void) 
{
    index = 0;
    
    if (description)
    {
	delete description;
	description = NULL;
    }
    if (trip)
    {
	delete trip;
	trip = NULL;
    }
}


//**********************************************************************************
//  DISPLAY EDGE

void edge::display(void) const
{
    cout << description << endl;
    return;
}


//**********************************************************************************
//  DISPLAY TRIP
//	If the user selects this edge, display the trip:

void edge::displaytrip(void) const
{
    cout << trip << endl;
    return;
}


//**********************************************************************************
//  NODE CLASS
//
//	Node is a derived class of edge and contains a next pointer in addition to
//  edge data.
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR

node::node(void) :
    next(0)
{}


//**********************************************************************************
//  CONSTRUCTOR
//	Set the data member index to the new value:

node::node(const int new_index, const char new_desc[], const char new_trip[]) : 
    edge(new_index, new_desc, new_trip),
    next(0)
{}


//**********************************************************************************
//  CONSTRUCTOR
//	Set the data member index to the new value:

node::node(const edge & to_add) : 
    edge(to_add),
    next(0)
{}



//**********************************************************************************
//  DECONSTRUCTOR

node::~node(void) 
{
    next = 0;
}


//**********************************************************************************
//  GO TO THE NEXT NODE

node *& node::go_next(void)
{
    return next;
}


//**********************************************************************************
//  RETURN THE VALUE OF THE EDGE INDEX

int node::getindex(void) const
{
    return index;
}


//**********************************************************************************
//  LEVEL CLASS
//
//	Level is the 'vertex' component of the map graph. The map consists of an 
//  array of levels which point to linear linked lists of edge nodes.
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

level::level(void)
{}


//**********************************************************************************
//  CONSTRUCTOR: 
//	Set level data members visit and head to null values, and copy the data
//  read from the file:

level::level(const char new_name[], const char new_desc[]) :
    head(0),
    item(0)
{

// If there is nothing to copy:
    if (!new_name || !new_desc)
	return;

// Otherwise copy the data:
    name = new char[strlen(new_name)+1];
    strcpy(name, new_name);

    description = new char[strlen(new_desc)+1];
    strcpy(description, new_desc);
}


//**********************************************************************************
//  CONSTRUCTOR: 
//	Set level data members visit and head to null values, and copy the data
//  read from the file:

level::level(const level & new_level, const stuff::object & new_object) :
    head(0)
{
    name = new char[strlen(new_level.name)+1];
    strcpy(name, new_level.name);

    description = new char[strlen(new_level.description)+1];
    strcpy(description, new_level.description);
    
    item = new stuff::object(new_object);
}


//**********************************************************************************
//  DECONSTRUCTOR

level::~level(void)
{
    if (head)
    {	
	node * current = head;
	while (current->go_next())
	{
	    current = current->go_next();
	    delete head;
	    head = current;
	}
	delete head;
	head = current = NULL;
    }

    if (name)
    {
	delete name;
	name = NULL;
    }

    if (description)
    {
	delete description;
	description = NULL;
    }
    if (item)
    {
	delete item;
	item = NULL;
    }
}


//**********************************************************************************
//  DISPLAY LEVEL

void level::display(void) const
{
    cout << name << '\n' << description << endl;
    node * current = head;
    display(current);
    return;
}

//**********************************************************************************
//  DISPLAY POSSIBLE DESTINATIONS

void level::display(node *& current) const
{
    if (current)
    {
	current->display();
	display(current->go_next());
    }
    return; 
}


//**********************************************************************************
//  DISPLAY LEVEL

void level::displayname(void) const
{
    cout << name << '\n' << description << endl;
    return;
}
//**********************************************************************************
//  ADD AN EDGE: wrapper

bool level::addedge(const edge & to_add)
{
    if (!addedge(head, to_add))
	return false;
    return true;
}


//**********************************************************************************
//  ADD AN EDGE: 
//	Recursively traverse the linear linked list of edges to insert a new edge.
//  Check using duplicate function to make sure the new edge is valid.

bool level::addedge(node *& current, const edge & to_add)
{
    if (!current)
	current = new node(to_add);
    else   
	addedge(current->go_next(), to_add);
    return true;
}


//**********************************************************************************
//  RETURN ADDRESS OF ITEM  

stuff::object & level::getitem(void)
{
    return *item;
}


//**********************************************************************************
//  DISPLAY POSSIBLE DESTINATIONS : WRAPPER
//	Return the value of the player's selection, which is an index to the next
//  vertex they wish to visit.

int level::whereto(void)
{
    int next = 0;
    cout << "\nFrom here you can choose: " << endl;
    
    node * current = head;
    whereto(current);

    cout << "\nWHERE TO?\t";
    do
    {
	cin >> next;
	cin.clear();
	cin.ignore(100, '\n');
    }while(!isvalid(next));

// Display the trip they've selected:
    thistrip(next);

    return next;
}


//**********************************************************************************
//  DISPLAY POSSIBLE DESTINATIONS

void level::whereto(node *& current)
{
    if (current)
    {
	current->display();
	whereto(current->go_next());
    }
    return; 
}


//**********************************************************************************
//  IS VALID : WRAPPER
//	Search the list of edges to make sure that the user input matches one of
//  the possible edges. If it doesn't, display an error message and return false.

bool level::isvalid(int next_move) 
{
    if (isvalid(head, next_move))
	    return true;
    cout << "\nYou didn't enter a valid number! \nReenter your selection:\t" 
	<< endl;
    return false;
}


//**********************************************************************************
//  IS VALID: 
//	Recursively traverse the linear linked list of edges. Return true if a 
//  match is found and return true if the next call returned true. Otherwise 
//  return false.

bool level::isvalid(node *& current, int next_move)
{
    if (current)
    {
	if (current->getindex() == next_move)
	    return true;
	if (isvalid(current->go_next(), next_move))
	    return true;
    }
    return false;
}


//**********************************************************************************
//  DISPLAY THIS TRIP: WRAPPER 

void level::thistrip(int next)
{
    thistrip(head, next);
    return;
}


//**********************************************************************************
//  DISPLAY THIS TRIP: 
//	Recurse through the list of edges until we find the one the user selected
//  and display it. 

void level::thistrip(node *& current, int next) 
{
    if (!current)
	return;
    if (current->getindex() == next)
	current->displaytrip();
    else
	thistrip(current->go_next(), next);
    return;
}




//**********************************************************************************
//  MAP CLASS
//
//	The map class consists of an adjacency list (an array of level pointers) as
//  well as a corresponding boolean array to record whether each has been visited. 
//  The map is built by reading in from an exteral file.
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

map::map(void)
{}


//**********************************************************************************
//  CONSTRUCTOR
//	Here's where a lot of heavy lifting happens. Reads in from the external 
//  file and builds the adjacency list. Takes filename as an arg in case the user
//  wants to specify which game to play.

map::map(const char * file)
{

    int L_NUM = 20;
// Set the vertices array to null by default:
    for (int j=0; j < L_NUM; j++)
	vertices[j] = NULL;

// Open stream for reading and set some temporary variables:
//  indexnum holds the value for the number of indices so we can loop through them.
    ifstream fin;
    fin.open(file);
    int N_MAX = 100;
    int D_MAX = 1000;
    char tempname[N_MAX];
    char tempobj[N_MAX];
    char tempobj_desc[D_MAX];
    char temptrip[D_MAX];
    char tempdesc[D_MAX];
    int tempindex, indexnum, pts = 0;

// for each vertex in the graph...
    for (int i=0; i < L_NUM && !fin.eof(); i++) 
    {	

    // ...and as long as we haven't reached the end of file read in:
    // LEVEL NAME:
	fin.get(tempname, N_MAX, ':');
	fin.ignore(N_MAX,':');
    // LEVEL DESCRIPTION:
	fin.get(tempdesc, D_MAX, ':');
	fin.ignore(D_MAX, ':');
    // OBJECT NAME:
	fin.get(tempobj, N_MAX, ':');
	fin.ignore(N_MAX,':');
    // OBJECT POINTS:
	fin >> pts;
	fin.clear();
	fin.ignore(D_MAX, ':');
    // OBJECT DESCRIPTION:
	fin.get(tempobj_desc, D_MAX, ':');
	fin.ignore(D_MAX,':');

    // make a new level and a new object with that data:
	level new_level(tempname, tempdesc);
	stuff::object new_object(tempobj, tempobj_desc, pts);

    // and add them to the vertex array:
	vertices[i] = new level(new_level, new_object);

    // read in the number of edges for this vertex:
	fin >> indexnum;
	fin.clear();
	fin.ignore(D_MAX, ':');

    // and then read them in:
	for (int k=0; k < indexnum; k++)
	{
	// EDGE INDEX:
	    fin >> tempindex;
	    fin.clear();
	    fin.ignore(N_MAX, '<');
	// EDGE DESCRIPTION:
	    fin.get(tempdesc, D_MAX, '-');
	    fin.ignore(D_MAX, '-');
	// TRIP DESCRIPTION:
	    fin.get(temptrip, D_MAX, '-');
	    fin.ignore(D_MAX, '-');

	    edge new_edge(tempindex, tempdesc, temptrip);

	    vertices[i]->addedge(new_edge);
	    tempindex=0;
	}
	fin.ignore(D_MAX, '\n');
    }

// Close stream:
    fin.close();
}


//**********************************************************************************
//  DECONSTRUCTOR

map::~map(void)
{
    for (int j=0; j < 20; j++)
    {
	if (vertices[j])
	    delete vertices[j];
	vertices[j] = NULL;
    }
}


//**********************************************************************************
//  DISPLAY ALL LEVELS: 
//	This is mostly just handy for making sure the external file read in okay.
//  The user would not actually see all of the levels at one time.

bool map::displaylevels(void) const
{
    cout << "\n\nHERE'S THE ENTIRE WORLD:" << endl;
    
    if (!vertices[0])
	return false;
    int i=0;
    while (vertices[i] && i < 20)
    {
	vertices[i]->display();
	cout << endl << endl;
	++i;
    }
    return true;
}


//**********************************************************************************
//  COUNT THE NUMBER OF LEVELS:

int map::levelcount() const
{
    int i = 0;
    while (vertices[i] && i < 20)
	i++;
    return i;
}


//**********************************************************************************
//  GET ITEM:
//	Pull the object item from the level so the player can pick it up:

stuff::object & map::getitem(int index)
{
    return vertices[index]->getitem(); 
}


//**********************************************************************************
//  CURRENT LOCATION
//	Display the current location.

void map::locate(int current)
{
    cout << "\n\nCURRENT LOCATION: ";
    vertices[current]->displayname();   
}


//**********************************************************************************
//  NEXT MOVE:
//	Display the current location, possible next locations, and return the
//  new location.

int map::nextmove(int current)
{
    return vertices[current]->whereto();
}


//**********************************************************************************
//  END CODE
//**********************************************************************************

