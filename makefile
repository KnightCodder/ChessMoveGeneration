# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Isrc -Wall -Wextra -g

# Source files directory
SRC_DIR = src

# Object files directory
OBJ_DIR = output

# Test files directory
TEST_DIR = tests

UI_DIR = ui

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of header files
Header = $(wildcard $(SRC_DIR)/*.h)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Main target
all: $(OBJS) $(OBJ_DIR)/test1.o
	$(CXX) $(OBJS) $(OBJ_DIR)/test1.o -o $(OBJ_DIR)/test1
	./$(OBJ_DIR)/test1

# Rule to compile individual source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Rule to compile test1.cpp into object file
$(OBJ_DIR)/test1.o: $(UI_DIR)/main.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Clean target to remove object files and test executables
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/test1
