
INTRODUCTION:

This is a Choose Your Own Adventure-style game made with the objective
that I would glean some experience working with object oriented
programming using dynamic binding and derived classes in C++.

One to six players may enjoy a text-based challenge to earn points and
collect objects. Each player wakes up in a cold dark cell and must
make their way out of the castle using their wits and instincts. If you
are of a strong mind and pure heart, you may even encounter Steve Martin.


TO USE:

After downloading and extracting the files, type 'make' and './play' on
the command line. If there is more than one player, they will trade off
turns as prompted.

To play again, simply type './play'
To recompile after making changes, type "make" again.
To delete all executables, type "make clean".


REVIEW:

Through this program I was able to experience and practice the concept of
dynamic binding, which made working with my class objects simple and easy.
I chose to implement dynamic binding in my “player” hierarchy by allowing
the user to be one of several different types of character. In the first
iteration of this program, “collection” (the derived class of “player”)
was a player which also had a node pointing to a collection of objects
that the user picked up along the way. In the second version of the game,
“collection” becomes a “hollow” hub class for the three specialized
character classes: unicorn, ninja and pirate. A collection object is never
created, but collection pointers are used to keep track of the different
characters in the game. This way the users can choose unique character
identities but all be managed the same way during game play.


FUTURE IMPROVEMENTS:

My imagination wasn’t too great in terms of fleshing out and
differentiating the three classes -- each has only a distinct data member
and different display functions -- but the groundwork now exists to create
more elaborate subclasses which are managed through dynamic binding. With
a more complex program it would have also been appropriate and useful to
implement dynamic binding with different subclasses of levels: perhaps
some levels have objects to pick up, others don’t; some levels have a
“boss” to fight, others might have a challenge or contain a shortcut.
Objects could have easily been more fully differentiated with dynamic
binding as well -- some objects could have magical powers, others could
have monetary value while other objects are necessary to pass on to the
next level. The opportunities for further development of this program is
practically endless.

One inefficiency I encountered is the fact that when a class becomes pure
virtual, its destructor can no longer be used -- the destructor must be
virtual to ensure that the derived subclass destructors are called. In
my case this seemed to mean that the code I had written to deallocate the
doubly linked list of objects in collection class would have to be copied
and pasted three times. This is not significant for three classes, but what
about future programs? What if the hub class had more subclasses? What if
it had ten, or fifty? The solution I found was to write a collection class
function called ‘destroy’ which is called by the derived classes’
destructors to do the same amount of work cleanly, with the same amount of
code. Additionally, I still did not find a good way to put the doubly
linked list of objects to work, wasting memory with unnecessary pointers,
but with more time to elaborate on the project I would design a means for
the user to cycle through and use their objects.

I attempted to keep my classes as clean and delineated as possible: for
the most part, the innermost bits (such as functions which copy node data,
moderate the linked list and edge traversal, etc) control the data while
the upper layers of the program (the client and the game class) interact
with the user. However as the program gained complexity I got a bit 
sloppy. For example, the collection class (which manages the doubly linked
list of items) contains a function called “add item” which asks the user 
if they want to pick up a particular item and echos back to confirm that 
it was added. Arguably this function should have returned the object to 
the game class, where the user would be prompted to take action. In future
programming tasks I would like to be more disciplined in tightly
controlling the boundary between data structures and the rest of the
program.

Hierarchies are used wherever possible. However the game class is not
incredibly object oriented -- it is only so in the way that the client
program creates a game object. From that point, game class is simply a
series of modular functions controlling the flow of game play -- it has
no base nor derived classes. However, game class could be used on a more
complex scale to moderate different games with different players and the
ability to toggle between one game and another.

That's it!
Hope you enjoy my silly program.
-Amanda
