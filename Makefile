# Author:		Denis Perepelyuk
# Student ID:	C00259076

CXX = g++ #-fopenmp
CPPFILES = wator-sim.cpp
CPPFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system #-libomp -fopenmp
EXE = wator-sim-test

# Define where SFML is installed from Homebrew
SFML_IMPORT = -I/opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIBRARY = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

SRCS = wator-sim.cpp #Semaphore.cpp Semaphore.h
OBJS = $(subst .cpp,.o,$(SRCS))

# This rule says that each .o file depends on a .cpp file of the same name
# This is actually built into Make but anyways...
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(SFML_IMPORT) $(DEBUGFLAGS)

ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS) $(SFML_LIBRARY)
