#include "Components/Canvas.h"
#include "Components/Transform.h"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include <algorithm>
#include <unicode/unistr.h>

std::string wstringToUtf8(const std::wstring& wideContent) {
    icu::UnicodeString unicodeStr(reinterpret_cast<const UChar*>(wideContent.data()), wideContent.length());
    std::string utf8Content;
    unicodeStr.toUTF8String(utf8Content);
    return utf8Content;
}

Canvas::Canvas(void* ent_ptr) : Component(ent_ptr) {
    std::cout<<"Initializing canvas..." << std::endl;
    clearCanvas();
    setvbuf(stdout, nullptr, _IONBF, 0);
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
}

Canvas::~Canvas() {}

void Canvas::clearCanvas(){
    for(int i=0; i <= MAX_Y; i++){
	for (int j=0; j <= MAX_X; j++) {
	    canvas[i][j] = L' '; 	
	}
    }
}


void clearScreen() {
    system("cls");
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
#else
    std::wcout << L"\033[H"; // ANSI escape code for cursor home
#endif
}

void Canvas::update() {
    clearScreen();
    clearCanvas();

    std::wstring vert = L"┃";
    std::wstring horz = L"━"; 
    std::wstring top_left = L"┏";
    std::wstring top_right = L"┓";
    std::wstring bottom_left = L"┗";
    std::wstring bottom_right = L"┛";

    for(auto graphic : all<ASCIIGraphic>()){
	    drawASCII(*graphic);
    }

    std::wstring border;
    for(int i =0; i <= MAX_X; i++) border += horz;

    std::wstring frame_buffer;

    //add top border to the canvas
    frame_buffer += L"\n" + top_left + border + top_right + L"\n";

    //Draw canvas lines with left and right borders
    for(int i=0; i<= MAX_Y; i++){
	frame_buffer += vert;
	for(int j=0; j <= MAX_X; j++){ 
	    frame_buffer += canvas[i][j];
	}
	frame_buffer += vert;
	frame_buffer += L"\n";
    }

    //draw bottom border
    frame_buffer += bottom_left + border + bottom_right + L"\n";
    std::string utf8_frame_buffer = wstringToUtf8(frame_buffer);
    std::cout << utf8_frame_buffer; 
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
    auto mat = graphics.pixelMatrix();

    Vector2D<int> topLeft = clipPoint(pos - graphics.center);
    Vector2D<int> size = Vector2D<int>(graphics.width(), graphics.height());
    Vector2D<int> bottomRight = clipPoint(pos + size - graphics.center);

    // std::cout << "top left: " <<topLeft.toString() << std::endl;
    // std::cout << "bottom right: " << bottomRight.toString() << std::endl;
    // std::cout << "graphic pos: " << pos.toString() << std::endl;
    // std::cout << "graphic center: " << graphics.center.toString() << std::endl;
    // std::cout << "size: " << size.toString() << std::endl; 
    // graphics.debugPrint();

    for(int i = topLeft.y; i < bottomRight.y; i++){
	for(int j=topLeft.x; j < bottomRight.x; j++){
	    int pix_i = i-topLeft.y;
	    int pix_j = j-topLeft.x;
	    if(pix_i > mat.size() -1) continue;
	    if(pix_j > mat[pix_i].size() -1) continue;
	    wchar_t pix = mat[pix_i][pix_j];
	    canvas[i][j] = pix;
	}
    }
}

