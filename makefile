SHELL := /bin/bash

# Define variables
BUILD_DIR = build
GAME_EXECUTABLE = $(BUILD_DIR)/game/target/game

# Default target: Compile and Build
all: compile build

# Compile CMake into the build directory
compile:
	@cmake -G "Ninja" -S . -B $(BUILD_DIR)

# Build the project
build: compile
	@cmake --build $(BUILD_DIR)

# Run the game
run: build
	@$(GAME_EXECUTABLE)

