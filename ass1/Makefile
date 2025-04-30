CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic
TARGET = tanks_game
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
rm -f $(TARGET) $(OBJS)

.PHONY: all clean
