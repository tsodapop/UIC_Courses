

CC = g++
FLAGS = -std=c++11 -g

SOURCES := $(wildcard *.cpp)

EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

% : %.cpp Graph.h _util.h
	$(CC) $(FLAGS)  $< -o $@

clean:
	rm -f $(EXECUTABLES)

