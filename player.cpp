
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
//  You are viewing 'player.cpp'
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

#include "player.h"
#include <iostream>
#include <cstring>
using namespace std;
using namespace stuff;

//**********************************************************************************
//  PLAYER CLASS
//
//	Player is a base class for collection. Its data members are a name, score, 
//  and their player number. This will be helpful for the next iteration of this 
//	program and in naming lazy players who don't enter their name. 
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

player::player(void) : 
    score(0),
    a_name(0),
    p_num(0)
{}

//**********************************************************************************
//  CONSTRUCTOR : SET NAME

player::player(const player & input) : 
    score(0),
    p_num(input.p_num)
{
    // Set their name to the char passed in:
    if (input.a_name)
    {
	a_name = new char[strlen(input.a_name)+1];
	strcpy(a_name, input.a_name);
    }
    return;   
}


//**********************************************************************************
//  DECONSTRUCTOR

player::~player(void) 
{
    if (a_name)
	delete [] a_name;
    a_name = NULL;
    score = p_num = 0;
}


//**********************************************************************************
//  READ PLAYER INFO

void player::read(const int player_num)
{
    char temp[20];
    cin.get(temp,20,'\n');
    cin.ignore(100,'\n');

    for (int i=0; i<strlen(temp); ++i)
	temp[i] = toupper(temp[i]);

    a_name = new char[strlen(temp)+1];
    strcpy(a_name, temp);

    p_num = player_num;
}


//**********************************************************************************
//  ADD POINTS TO SCORE

void player::addpts(int to_add)
{
    score += to_add;
    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S SCORE

void player::displaypts(void) const
{
    cout << "\n" << a_name << "'s final score is " << score;
    return;
}


//**********************************************************************************
//  ADD POINTS TO SCORE

int player::getpts(void) const
{
    return score;
}


//**********************************************************************************
//  COLLECTION CLASS
//
//	Collection is a derived class of player and has one or many items of 
//  object class. The collection is a doubly linked list of objects that is 
//  added to as the player progresses in the game. 
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

collection::collection(void)
{}


//**********************************************************************************
//  CONSTRUCTOR: CREATE NEW PLAYER WITH OBJECT COLLECTION

collection::collection(const player & input) :
    player(input),
    head(0)
{}


//**********************************************************************************
//  DESTRUCTOR 

collection::~collection(void)
{}


//**********************************************************************************
//  DESTROY: 
//	The actual deconstructor for collection, called by the derived classes

void collection::destroy(void)
{
    if (!head)
	return;

    node * current = head;
    while (current->go_forward())
    {
	current = current->go_forward();
	delete head;
	head->go_back() = NULL;
	head->go_forward() = NULL;
	head = current;
    }
    delete head;
    head->go_back() = NULL;
    head->go_forward() = NULL;
    head = current = NULL;
}



//**********************************************************************************
//  IS A DUPLICATE?
//	Traverse the linked list of objects and look for a duplicate. If one is
//  found, return true. Otherwise return false.

bool collection::duplicate(const object & to_add) const
{
// If the list is empty, the new item cannot be a duplicate:
    if (!head)
	return false;
// Otherwise, traverse the list of objects:
    node * current = head;
    while (current->go_forward())
    {
    // If the new object is the same as the current object, return true.
	if(current->duplicate(to_add))
	    return true;
	current = current->go_forward();
    }
// Check the last object:
    if(current->duplicate(to_add))
	return true;
// If no duplicates are found, return false:
    return false;
}


//**********************************************************************************
//  ADD ITEM:
//	Call duplicate to check whether or not the player already has the object.
//  If they don't already have it, ask the player whether or not to pick it up.

void collection::additem(const object & new_object)
{
// Check to see if the player already has the item:
    if(duplicate(new_object))
	return;
// Otherwise ask the user if they want to add the item to the collection:
    new_object.displayfull();
    cout << "\nAdd "; 
    new_object.display();
    cout << " to your collection? [Y/N]\t"; 
    char response = '\0';
    cin >> response;
    cin.ignore(100,'\n');

    if(toupper(response) == 'Y')
    {
	pickup(new_object);
	addpts(new_object.getpoints());
	cout << "\nYou added ";
	new_object.display();
	cout << " to your collection and earned " << new_object.getpoints() 
	    << " points!" << endl;

    }
    return;
}



//**********************************************************************************
//  PICK UP:
//	Add a new object to the player's collection:

void collection::pickup(const object & new_object)
{
// If head is null, insert here. Both pointers of the new node are set to null by
//  the constructor.
    if (!head)
	head = new node(new_object);
// Otherwise traverse until we find and empty spot:
    else
    {
	node * current = head;
	while (current->go_forward())
	    current = current->go_forward();
	current->go_forward() = new node(new_object);
    // Link up the new node's previous pointer to point at current. The new node's
    //	next pointer was set to null by the constructor.
	current->go_forward()->connect_back(current);
    }
    return;
}

//**********************************************************************************
//  DISPLAY ALL ITEMS:

void collection::displayitems(void) const
{
    if (!head)
    {
	cout << "\t[--No items in inventory--]";
	return;
    }
    node * current = head;
    cout << '\t';
    while (current->go_forward())
    {
	current->display();
	cout << "\n\t";
	current = current->go_forward();
    }
    current->display();
}


//**********************************************************************************
//  NINJA CLASS
//
//
//                  _.---._
//              _.-(_o___o_)
//              )_.'_     _'.
//            _.-( (_`---'_) )-._
//          .'_.-'-._`"""`_.-'-._'.
//          /` |    __`"`__    | `\
//         |   | .'`  ^:^  `'. |   |
//         )'-.//      |      \\.-'(
//        /   //       |       \\   \
//        \   |=======.=.=======|   /
//         )`-|      ( R )      |-'(
//         \  \======/-\'\======/  /
//          \,=(    <_/;\_|    )=,/
//          /  -\      |      /-  \
//          | (`-'\    |    /'-`) |
//          \\_`\  '.__|__.'  /`_//
//            /     /     \     \
//           /    /`       `\    \
//          /_,="(           )"=,_\
//          )-_,="\         /"=,_-(
//           \    (         )    /
//            \    |       |    /
//            )._ |       | _.(
//        _.-'   '/       \'   '-._
//       (__,'  .'         '.  ',__)
//           '--`             `--'
//
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

ninja::ninja(void) : 
    collection()
{}


//**********************************************************************************
//  CONSTRUCTOR :

ninja::ninja(const player & input, char * flavor) : 
    collection(input)
{
    pizza = new char[strlen(flavor)+1];
    strcpy(pizza, flavor);
    return;
}


//**********************************************************************************
//  DECONSTRUCTOR

ninja::~ninja(void)
{
    destroy();
    delete [] pizza;
    pizza = NULL;
}


//**********************************************************************************
//  DISPLAY PLAYER'S TURN

void ninja::display(void) const
{
    cout << endl << "   ********************************************************" << endl
	<< "                  _.---._" << endl
	<< "              _.-(_o___o_)" << endl
	<< "              )_.'_     _'." << endl
	<< "            _.-( (_`---'_) )-._" << endl
	<< "          .'_.-'-._`\"\"\"`_.-'-._'." 
	<< "\tCOWABUNGA, " << a_name << "ATELLO!" << endl
	<< "          /` |    __`\"`__    | `\\" << endl
	<< "         |   | .'`  ^:^  `'. |   |" 
	<< "\tYOU'RE UP, DUDE!" << endl
	<< "         )'-.//      |      \\\\.-'(" << endl
	<< "        /   //       |       \\\\   \\" << endl
	<< "        \\   |=======.=.=======|   /" << endl
	<< "         )`-|      ( R )      |-'(" << endl
	<< "         \\  \\======/-\\'\\======/  /" << endl
	<< "          \\,=(    <_/;\\_|    )=,/" << endl
	<< "          /  -\\      |      /-  \\" << endl
	<< "          | (`-'\\    |    /'-`) |" << endl
	<< "          \\\\_`\\  '.__|__.'  /`_// " << endl
	<< "            /     /     \\     \\" << endl
	<< "           /    /`       `\\    \\" << endl
	<< "          /_,=\"(           )\"=,_\\" << endl
	<< "          )-_,=\"\\         \\/\"=,_-(" << endl
	<< "           \\    (         )    /" 
	<< "\t\tCURRENT SCORE: " << score << endl
	<< "            \\    |       |    /" << endl
	<< "             )._ |       | _.(" << endl
	<< "         _.-'   '/       \\'   '-._ " << endl
	<< "        (__,'  .'         '.  ',__)" << endl
	<< "           '--`             `--'" << endl
	<< "   ********************************************************" << endl;
    
    return;
}

//**********************************************************************************
//  WELCOME PLAYER TO THE CLASS

void ninja::welcome(void) const
{
    cout << endl << "   ********************************************************" << endl
	<< "                  _.---._" << endl
	<< "              _.-(_o___o_)" << endl
	<< "              )_.'_     _'." << endl
	<< "            _.-( (_`---'_) )-._" << endl
	<< "          .'_.-'-._`\"\"\"`_.-'-._'." 
	<< "\tCOWABUNGA, " << a_name << "ATELLO!" << endl
	<< "          /` |    __`\"`__    | `\\" << endl
	<< "         |   | .'`  ^:^  `'. |   |" 
	<< "\tDUDE, " << pizza << " IS TOTALLY RADICAL!" << endl
	<< "         )'-.//      |      \\\\.-'(" << endl
	<< "        /   //       |       \\\\   \\" << endl
	<< "        \\   |=======.=.=======|   /" << endl
	<< "         )`-|      ( R )      |-'(" << endl
	<< "         \\  \\======/-\\'\\======/  /" << endl
	<< "          \\,=(    <_/;\\_|    )=,/" << endl
	<< "          /  -\\      |      /-  \\" << endl
	<< "          | (`-'\\    |    /'-`) |" << endl
	<< "          \\\\_`\\  '.__|__.'  /`_// " << endl
	<< "            /     /     \\     \\" << endl
	<< "           /    /`       `\\    \\" << endl
	<< "          /_,=\"(           )\"=,_\\" << endl
	<< "          )-_,=\"\\         \\/\"=,_-(" << endl
	<< "           \\    (         )    /"  << endl
	<< "            \\    |       |    /" << endl
	<< "             )._ |       | _.(" << endl
	<< "         _.-'   '/       \\'   '-._ " << endl
	<< "        (__,'  .'         '.  ',__)" << endl
	<< "           '--`             `--'" << endl
	<< "   ********************************************************" << endl;
    
    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S FINAL STATS:

void ninja::displayfinal()const 
{
    cout << endl << "   ********************************************************" << endl
	<< "                  _.---._" << endl
	<< "              _.-(_o___o_)" << endl
	<< "              )_.'_     _'." << endl
	<< "            _.-( (_`---'_) )-._" << endl
	<< "          .'_.-'-._`\"\"\"`_.-'-._'." << "\tCOWABUNGA, " << a_name << "ATELLO!" << endl
	<< "          /` |    __`\"`__    | `\\" << endl
	<< "         |   | .'`  ^:^  `'. |   |" << "\tTHAT WAS BODACIOUS!" << endl
	<< "         )'-.//      |      \\\\.-'(" << endl
	<< "        /   //       |       \\\\   \\" << endl
	<< "        \\   |=======.=.=======|   /" << endl
	<< "         )`-|      ( R )      |-'(" << endl
	<< "         \\  \\======/-\\'\\======/  /" << endl
	<< "          \\,=(    <_/;\\_|    )=,/" << endl
	<< "          /  -\\      |      /-  \\" << endl
	<< "          | (`-'\\    |    /'-`) |" << endl
	<< "          \\\\_`\\  '.__|__.'  /`_// " << endl
	<< "            /     /     \\     \\" << endl
	<< "           /    /`       `\\    \\" << endl
	<< "          /_,=\"(           )\"=,_\\" << endl
	<< "          )-_,=\"\\         \\/\"=,_-(" << endl
	<< "           \\    (         )    /"  << endl
	<< "            \\    |       |    /" << "\tFINAL SCORE: " << score << endl
	<< "             )._ |       | _.(" << endl
	<< "         _.-'   '/       \\'   '-._ " << endl
	<< "        (__,'  .'         '.  ',__)" << endl
	<< "           '--`             `--'" << endl
	<< "   ********************************************************" << endl
	<< '\t' << a_name << "ATELLO'S INVENTORY IS:" << endl;
    displayitems();
    cout << "\n   ********************************************************" << endl;

    return;
}

//**********************************************************************************
//  DISPLAY PLAYER'S NAME

void ninja::displayname(void) const
{
    cout << a_name << "ATELLO";
    return;
}


//**********************************************************************************
//  PIRATE CLASS
//
//       _.--""--._
//      /  _    _  \
//   _  ( (_\  /_) )  _
//  { \._\   /\   /_./ }
//  /_"=-.}______{.-="_\
//   _  _.=("""")=._  _
//  (_'"_.-"`~~`"-._"'_)
//  {_"            "_}
//
//**********************************************************************************



//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

pirate::pirate(void) : 
    collection()
{}


//**********************************************************************************
//  CONSTRUCTOR :

pirate::pirate(const player & input, char * color) : 
    collection(input)
{
    beard = new char[strlen(color)+1];
    strcpy(beard,color);
    return;
}


//**********************************************************************************
//  DECONSTRUCTOR

pirate::~pirate(void)
{
    destroy();
    delete [] beard;
    beard = NULL;
}


//**********************************************************************************
//  DISPLAY PLAYER'S TURN

void pirate::display(void) const
{
    cout << endl << "   ********************************************************" << endl
	<< "     _.--\"\"--._" << endl
	<< "    /  _    _  \\" << endl
	<< " _  ( (_\\  /_) )  _" 
	<< '\t' << "AVAST!" << endl
	<<"{ \\._\\   /\\   /_./ }" 
	<< '\t' << "CAP'N " << a_name << ' ' << beard << " BEARD" << endl
	<< "/_\"=-.}______{.-=\"_\\" 
	<< '\t' << "YE BE PLAYIN'" << endl
	<< " _  _.=(\"\"\"\")=._  _" << endl
	<< "(_'\"_.-\"`~~`\"-._\"'_)" << "\tCURRENT SCORE: " << score << endl
	<< " {_\"            \"_}" << endl
	<< "\n   ********************************************************" << endl;

    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S NAME

void pirate::displayname(void) const
{
    cout << "CAP'N " << a_name << ' ' << beard << " BEARD";
    return;
}


//**********************************************************************************
//  DISPLAY WELCOME TO THE CLASS

void pirate::welcome(void) const
{

    cout << endl << "   ********************************************************" << endl
	<< "     _.--\"\"--._" << endl
	<< "    /  _    _  \\" << endl
	<< " _  ( (_\\  /_) )  _" 
	<< '\t' << "YARRRR!" << endl
	<<"{ \\._\\   /\\   /_./ }" 
	<< '\t' << "WELCOME CAP'N " << endl
	<< "/_\"=-.}______{.-=\"_\\" 
	<< '\t' << a_name << ' ' << beard << " BEARD." << endl
	<< " _  _.=(\"\"\"\")=._  _" << endl
	<< "(_'\"_.-\"`~~`\"-._\"'_)" << endl
	<< " {_\"            \"_}" << endl
	<< "\n   ********************************************************" << endl;

    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S FINAL STATS:

void pirate::displayfinal(void) const
{
    cout << endl << "   ********************************************************" << endl
	<< "     _.--\"\"--._" << endl
	<< "    /  _    _  \\" << endl
	<< " _  ( (_\\  /_) )  _" 
	<< '\t' << "CAP'N " << a_name << ' ' << beard << " BEARD" << endl
	<<"{ \\._\\   /\\   /_./ }" << endl
	<< "/_\"=-.}______{.-=\"_\\" << endl
	<< " _  _.=(\"\"\"\")=._  _" << endl
	<< "(_'\"_.-\"`~~`\"-._\"'_)" << "\tFINAL SCORE: " << score << endl
	<< " {_\"            \"_}" << endl
	<< "   ********************************************************" << endl
	<< '\t' << "CAP'N " << a_name << ' ' 
	<< beard << " BEARD'S INVENTORY IS:" << endl;
    displayitems();
    cout << "\n   ********************************************************" << endl;


    return;
}





//**********************************************************************************
//  UNICORN CLASS
//
//                     ,%%%,
//                   ,%%%` %==--
//                   ,%%`( '|
//                 ,%%@ /\_/
//       ,%.-"""--%%% "@@__
//      %%/             |__`\
//     .%'\     |   \   /  //
//     ,%' >   .'----\ |  [/
//        < <<`       ||
//         `\\\       ||
//           )\\      )\
//   ^^^^^^^^"""^^^^^^""^^^^^^^^^^
//	
//**********************************************************************************


//**********************************************************************************
//  DEFAULT CONSTRUCTOR : never invoked

unicorn::unicorn(void) : 
    collection()
{}


//**********************************************************************************
//  CONSTRUCTOR :

unicorn::unicorn(const player & input, int num) : 
    collection(input),
    magic(num)
{}


//**********************************************************************************
//  DECONSTRUCTOR

unicorn::~unicorn(void)
{
    destroy();
    magic = 0;
}



//**********************************************************************************
//  DISPLAY PLAYER'S TURN

void unicorn::display(void) const
{
    cout << endl
	<< "   ********************************************************" << endl
	<< "\t                   ,\%\%%," << endl
	<< "\t                 ,\%\%%` %==--" 
	<< "\tWHINNY! " << a_name << "CORN," << endl
	<< "\t                ,\%\%`( '|" << endl
	<< "\t               ,\%\%@ /\\_/ "
	<< "\tIT'S YOUR TURN TO SHIMMER!" << endl
	<< "\t     ,%.-\"\"\"--\%\%\% \"@@__" << endl
	<< "\t    \%\%/             |__`\\" << endl
	<< "\t   .%'\\     |   \\   /  //" << endl
	<< "\t   ,%' >   .'----\\ |  [/" 
	<< "\tCURRENT SCORE:" << score << endl
	<< "\t      < <<`       ||" << endl
	<< "\t       `\\\\\\       ||" << endl
	<< "\t         )\\\\      )\\" << endl
	<< "\t ^^^^^^^^\"\"\"^^^^^^\"\"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl
	<< "\n   ********************************************************" << endl;

    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S NAME

void unicorn::displayname(void) const
{
    cout << a_name << "CORN";
    return;
}


//**********************************************************************************
//  DISPLAY WELCOME TO THE CLASS

void unicorn::welcome(void) const
{

    cout << endl 
	<< "   ********************************************************" << endl
	<< "           .,,." << endl
	<< "         ,;;*;;;;," 
	<< "\tNAAA-A-A-A-AY! WELCOME " << a_name << "CORN!" << endl
	<< "        .-'``;-');;."
	<< "\tYOU HAVE " << magic << " POWER GEMS!" << endl
	<< "       /'  .-.  /*;;" << endl
	<< "     .'    \\d    \\;;               .;;;," << endl
	<< "    / o      `    \\;    ,__.     ,;*;;;*;," << endl
	<< "    \\__, _.__,'   \\_.-') __)--.;;;;;*;;;;," << endl
	<< "     `""`;;;\\       /-')_) __)  `\\' ';;;;;;" << endl
	<< "        ;*;;;        -') `)_)  |\\ |  ;;;;*;" << endl
	<< "        ;;;;|        `---`    O | | ;;*;;;" << endl
	<< "        *;*;\\|                 O  / ;;;;;*" << endl
	<< "       ;;;;;/|    .-------\\      / ;*;;;;;" << endl
	<< "      ;;;*;/ \\    |        '.   (`. ;;;*;;; " << endl
	<< "      ;;;;;'. ;   |          )   \\ | ;;;;;;" << endl
	<< "      ,;*;;;;\\/   |.        /   /` | ';;;*;" << endl
	<< "       ;;;;;;/    |/       /   /__/   ';;;" << endl
	<< "       '*;;;/     |       /    |      ;*;" << endl
	<< "            `""""`        `""""`     ;'" << endl
	<< "\n   ********************************************************" << endl;

    return;
}


//**********************************************************************************
//  DISPLAY PLAYER'S FINAL STATS:

void unicorn::displayfinal(void) const
{

    cout << endl << "   ********************************************************" << endl
	<< "           .,,." << endl
	<< "         ,;;*;;;;," 
	<< '\t' << a_name << "CORN!" << endl
	<< "        .-'``;-');;." 
	<< "\tYOUR FINAL SCORE IS " << score << endl
	<< "       /'  .-.  /*;;" << endl
	<< "     .'    \\d    \\;;               .;;;," << endl
	<< "    / o      `    \\;    ,__.     ,;*;;;*;," << endl
	<< "    \\__, _.__,'   \\_.-') __)--.;;;;;*;;;;," << endl
	<< "     `""`;;;\\       /-')_) __)  `\\' ';;;;;;" << endl
	<< "        ;*;;;        -') `)_)  |\\ |  ;;;;*;" << endl
	<< "        ;;;;|        `---`    O | | ;;*;;;" << endl
	<< "        *;*;\\|                 O  / ;;;;;*" << endl
	<< "       ;;;;;/|    .-------\\      / ;*;;;;;" << endl
	<< "      ;;;*;/ \\    |        '.   (`. ;;;*;;; " << endl
	<< "      ;;;;;'. ;   |          )   \\ | ;;;;;;" << endl
	<< "      ,;*;;;;\\/   |.        /   /` | ';;;*;" << endl
	<< "       ;;;;;;/    |/       /   /__/   ';;;" << endl
	<< "       '*;;;/     |       /    |      ;*;" << endl
	<< "            `""""`        `""""`     ;'" << endl
	<< "   ********************************************************" << endl
	<< '\t' << a_name << "CORN'S INVENTORY IS:" << endl;
    displayitems();
    cout << "\n   ********************************************************" << endl;
    return;
}




//**********************************************************************************
//  END CODE
//**********************************************************************************

