CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

mt-collatz: mt-collatz.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o mt-collatz *.gc* *.dSYM