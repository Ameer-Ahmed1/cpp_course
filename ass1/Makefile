# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Directory paths
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Final executable name
TARGET = $(BIN_DIR)/game.exe

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default build target
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Build and run the program
run: all
	$(TARGET)

.PHONY: all clean run
