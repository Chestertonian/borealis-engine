CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = $(wildcard src/*.cpp)

TARGET = borealis

debug:
	$(CXX) $(CXXFLAGS) -g -O0 $(SRC) -o $(TARGET)

release:
	$(CXX) $(CXXFLAGS) -O3 -DNDEBUG $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

all: 
	release