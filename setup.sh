#!/bin/bash

# Prompt user for directory and project name
read -p "Enter the directory where you want to create the project: " directory
read -p "Enter the project name: " project_name

# Construct the full paths
project_directory="$directory/$project_name"
include_zip_path="$project_directory/include.zip"
lib_zip_path="$project_directory/lib.zip"

# Create project directory
mkdir -p "$project_directory"

# Download include directory from GitHub
curl -L -o "$include_zip_path" "https://github.com/KnightCodder/ChessMoveGeneration/archive/main.zip"
unzip -qq "$include_zip_path" -d "$project_directory"
mv "$project_directory/your_project_repository-main/include" "$project_directory/"
rm "$include_zip_path"

# Download lib directory from GitHub
curl -L -o "$lib_zip_path" "https://github.com/KnightCodder/ChessMoveGeneration/archive/main.zip"
unzip -qq "$lib_zip_path" -d "$project_directory"
mv "$project_directory/your_project_repository-main/lib" "$project_directory/"
rm "$lib_zip_path"

# Create src and test directories
mkdir -p "$project_directory/src"
mkdir -p "$project_directory/test"

# Create Makefile
cat <<EOF > "$project_directory/Makefile"
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
SRCS = \$(wildcard \$(SRC_DIR)/*.cpp)

# List of object files
OBJS = \$(patsubst \$(SRC_DIR)/%.cpp,\$(OBJ_DIR)/%.o,\$(SRCS))

# Static library name
LIB_NAME = lib$project_name.a

# Main target
all: \$(LIB_DIR)/\$(LIB_NAME)

# Rule to compile individual source files into object files
\$(OBJ_DIR)/%.o: \$(SRC_DIR)/%.cpp
	\$(CXX) -c \$< \$(CXXFLAGS) -o \$@

# Rule to build static library
\$(LIB_DIR)/\$(LIB_NAME): \$(OBJS)
	ar rcs \$@ \$^

# Clean target to remove object files and static library
clean:
	rm -f \$(OBJ_DIR)/*.o \$(LIB_DIR)/\$(LIB_NAME)
EOF

echo "Project $project_name created in $directory"
