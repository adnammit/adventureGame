# HERE IS A MAKE FILE FOR MY ADVENTURE GAME:

# COMPILER:
CC=g++

# FLAGS:
CFLAGS=-g -c
LDFLAGS=

#EXECUTABLE:
EXE=play

# SOURCE FILES:
SOURCES=main.cpp player.cpp object.cpp map.cpp game.cpp

# OBJECT FILES:
OBJECTS=$(SOURCES:.cpp=.o)



all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
    
clean:	
	rm -rf *.o play
