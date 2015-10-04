CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp QuadTree.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=quad

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o
