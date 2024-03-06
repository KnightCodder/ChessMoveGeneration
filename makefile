# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Isrc

# Source files directory
SRC_DIR = src

# Object files directory
OBJ_DIR = output

# Test files directory
TEST_DIR = tests

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

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
$(OBJ_DIR)/test1.o: $(TEST_DIR)/test1.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Clean target to remove object files and test executables
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/test1
