SHELL := /bin/bash

# Define variables
BUILD_DIR = build
GAME_EXECUTABLE = $(BUILD_DIR)/game/target/game

# Default target: Compile and Build
all: compile build

# Compile CMake into the build directory
compile:
	@cmake -G "NMake Makefiles" -S . -B $(BUILD_DIR)

# Build the project
build: compile
	@cmake --build $(BUILD_DIR)

clean-build: compile
	@cmake --build $(BUILD_DIR) --clean-first

# Run the game
run: build
	@$(GAME_EXECUTABLE)

