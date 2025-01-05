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

void clearScreen() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
#else
    std::wcout << L"\033[H"; // ANSI escape code for cursor home
#endif
}

Canvas::Canvas(void* ent_ptr) : Component(ent_ptr) {
    std::cout<<"Initializing canvas..." << std::endl;
    resize(_width,_height);
    clearCanvas();
    setvbuf(stdout, nullptr, _IONBF, 0);
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
}

Canvas::~Canvas() {}

void Canvas::clearCanvas(){
    for(int i=0; i < height(); i++){
	for (int j=0; j < width(); j++) {
	    canvas[i][j] = L' '; 	
	}
    }
}

void Canvas::resize(int const& width, int const& height){
    this -> _width = width;
    this -> _height = height;

    canvas = new wchar_t*[height];
    for (size_t i = 0; i < height; ++i) {
        canvas[i] = new wchar_t[width];
    }
}

int Canvas::width(){
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            int terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            return std::min(_width, terminalWidth-2); //padding helps
        }
#endif
	// Fallback if not on Windows or an error occurs
        return _width; 
}

int Canvas::height(){
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            int terminalHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return std::min(_height, terminalHeight-2); //padding helps
        }
#endif
	// Fallback if not on Windows or an error occurs
        return _height; 
}

void Canvas::update() {
    if(_prev_rend_width != width() || _prev_rend_height != height()){
	system("cls");
    }

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
    for(int i =0; i < width(); i++) border += horz;

    std::wstring frame_buffer;

    //add top border to the canvas
    frame_buffer += L"\n" + top_left + border + top_right + L"\n";

    //Draw canvas lines with left and right borders
    for(int i=0; i< height(); i++){
	frame_buffer += vert;
	for(int j=0; j < width(); j++){ 
	    frame_buffer += canvas[i][j];
	}
	frame_buffer += vert;
	frame_buffer += L"\n";
    }

    //draw bottom border
    frame_buffer += bottom_left + border + bottom_right + L"\n";
    std::string utf8_frame_buffer = wstringToUtf8(frame_buffer);

    clearScreen();
    std::cout << utf8_frame_buffer; 

    _prev_rend_width = width();
    _prev_rend_height = height();
}

Vector2D<int> Canvas::clipPoint(Vector2D<int> point){
    int x = std::min(point.x,width()-1);
    x = std::max(x,0);

    int y = std::min(point.y,height()-1);
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

