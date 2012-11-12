CXXFLAGS += -g -Wall -Wextra

TARGET = polynomial1 polynomial2 polynomial3

CLEANUP = rm -f $(TARGET) *.o

all : $(TARGET)

clean :
	$(CLEANUP)

all:
polynomial1: polynomial1.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
polynomial2: polynomial2.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
polynomial3: polynomial3.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
