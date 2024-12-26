SHELL := /bin/bash
# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = build/bin/game

# Find all .cpp files in the src directory and its subdirectories
SRCS = $(wildcard src/*.cpp) $(foreach dir, $(wildcard src/*), $(wildcard $(dir)/*.cpp))

# Convert .cpp files to corresponding .o files in the build/obj directory
OBJS = $(SRCS:src/%.cpp=build/obj/%.o)

# Default target
build: export_res $(TARGET)

# Export resources
export_res: setup
	@echo moving resources
	@copy ".\resources\*" ".\build\resources"

# Create build directories
.PHONY: setup
setup: clean
	@if not exist build mkdir build
	@if not exist "build/bin" mkdir "build/bin"
	@if not exist "build/resources" mkdir "build/resources"
	@if not exist "build/obj" mkdir "build/obj"

# Rule to link the target executable
$(TARGET): $(OBJS)
	@echo Building Target: $@ ...
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo Building Success!!

# Rule to compile .cpp files into .o files
build/obj/%.o: src/%.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	@echo compiling $< ...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	@if exist build rmdir /s /q build
