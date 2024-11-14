CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

lizard: lizard.o
	$(CXX) -o $@ $^

lizardUni: lizardUni.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o lizard *.gc* *.dSYM
