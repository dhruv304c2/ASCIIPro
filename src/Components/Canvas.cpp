#include "../.././includes/Components/Canvas.h"
#include <iostream>
#include <string>

Canvas::Canvas() : Component(CANVAS) {
    for(int i=0; i < MAX_Y; i++){
	for (int j=0; j < MAX_X; j++) {
	    canvas[i][j] = ' '; 	
	}
    }
}

Canvas::~Canvas() {
    // Destructor implementation
}

void Canvas::update(Time* time) {
    std::string wall = "#";

    system("cls");

    //add top border to the canvas
    std::string topBoreder = "\n" + wall;
    for(int j=0; j < MAX_X; j++){
	topBoreder += wall;
    }

    topBoreder += wall;
    std::cout<< topBoreder << std::endl;

    //Draw canvas lines with left and right borders
    for(int i=0; i< MAX_Y; i++){
	std::string line = wall;
	for(int j=0; j < MAX_X; j++){
	    line += canvas[i][j];
	}
	line += wall;
	std::cout << line << std::endl;
    }

    //draw bottom border
    std::string bottomBoreder = wall;
    for(int j=0; j < MAX_X; j++){
	bottomBoreder += wall;
    }
    bottomBoreder += wall;
    std::cout<< bottomBoreder;
}

