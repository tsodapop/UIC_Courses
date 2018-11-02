

CC = g++
FLAGS = -std=c++11 -g

SOURCES := $(wildcard t*.cpp)

EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

% : %.cpp bst.h _tutil.h
	$(CC) $(FLAGS)  $< -o $@

clean:
	rm -f $(EXECUTABLES)

