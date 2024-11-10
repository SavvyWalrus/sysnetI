CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

main: main.o cat.o lizard.o constants.o global.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o main *.gc* *.dSYM
