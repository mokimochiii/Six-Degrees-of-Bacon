CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

OBJECTS = sixdegrees.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees sixdegrees.o

sixdegrees.o: sixdegrees.cpp graph.h
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp

clean: 
	rm -f *.o
	rm sixdegrees
