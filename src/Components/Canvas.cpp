#include "../.././includes/Components/Canvas.h"
#include "../../includes/Components/Transform.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Canvas::Canvas() : Component() {
    clearCanvas();
}

Canvas::~Canvas() {
    // Destructor implementation
}

void Canvas::clearCanvas(){
    for(int i=0; i < MAX_Y; i++){
	for (int j=0; j < MAX_X; j++) {
	    canvas[i][j] = ' '; 	
	}
    }
}

void Canvas::update(Time* time, std::vector<Component*> all, InputManager* input) {
    std::string wall = "#";

    system("cls");
    clearCanvas();

    for(auto comp : all){
	if (auto graphic = dynamic_cast<ASCIIGraphic*>(comp)){
	    drawASCII(*graphic);
	}
    }

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

Vector2D<int> Canvas::clipPoint(Vector2D<int> point){
    int x = std::min(point.x,MAX_X);
    x = std::max(x,0);

    int y = std::min(point.y,MAX_Y);
    y = std::max(y,0);

    return Vector2D<int>(x,y);
}

void Canvas::drawASCII(ASCIIGraphic& graphics){
    auto transfom = graphics.getAttached<Transform>();
    auto pos = transfom -> position;
    auto mat = graphics.ascii();
    Vector2D<int> topLeft = static_cast<Vector2D<int>>(pos) - graphics.center;
    topLeft = clipPoint(topLeft);
    Vector2D<int> bottomRight = 
	Vector2D<int>(pos.x + (graphics.width() - graphics.center.x), 
	    pos.y + (graphics.height() - graphics.center.y));
    bottomRight = clipPoint(bottomRight);

    for(int i = topLeft.y; i < bottomRight.y; i++){
	for(int j=topLeft.x; j < bottomRight.x; j++){
	    char pix = mat[i-topLeft.y][j-topLeft.x];
	    canvas[i][j] = pix;
	}
    }
}

