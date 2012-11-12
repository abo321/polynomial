CXXFLAGS += -g -Wall -Wextra

TESTS = main

all : $(TESTS)

clean :
	rm -f $(TESTS) *.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c $^

term.o : term.cpp
	$(CXX) $(CXXFLAGS) -c $^

poly.o : poly.cpp
	$(CXX) $(CXXFLAGS) -c $^

polynomial.o : polynomial.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(TESTS): term.o poly.o polynomial.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
