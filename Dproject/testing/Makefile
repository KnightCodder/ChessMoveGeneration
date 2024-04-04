# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Iinclude -Wall -Wextra -g

# Source files directory
SRC_DIR = src

# Object files directory
OBJ_DIR = output

# Library directory
LIB_DIR = lib

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Static library name
LIB_NAME = libtesting.a

# Main target
all: $(LIB_DIR)/$(LIB_NAME)

# Rule to compile individual source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Rule to build static library
$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

# Clean target to remove object files and static library
clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/$(LIB_NAME)
