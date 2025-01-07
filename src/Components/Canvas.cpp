#include "Components/Canvas.h"
#include "Components/Transform.h"
#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unicode/unistr.h>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

std::string wstringToUtf8(const std::wstring& wideContent) {
    icu::UnicodeString unicodeStr(reinterpret_cast<const UChar*>(wideContent.data()), wideContent.length());
    std::string utf8Content;
    unicodeStr.toUTF8String(utf8Content);
    return utf8Content;
}

void writeToConsole(const std::wstring& frame_buffer, int const& width, int const& height) {
#ifdef _WIN32
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    DWORD written = 0;
    COORD cursorPos = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPos);

    WriteConsoleW(hConsole, frame_buffer.c_str(), static_cast<DWORD>(frame_buffer.size()), &written, NULL);
#else
    std::wcout << L"\033[H"; // ANSI escape to reset cursor to top-left
    std::wcout << frame_buffer;
#endif
}

Canvas::Canvas(void* ent_ptr) : Component(ent_ptr) {}

void Canvas::start(){
    std::cout<<"Initializing canvas..." << std::endl;
    resizeCanvas(window() -> width(), window() -> height());
    clearCanvas();
    setvbuf(stdout, nullptr, _IONBF, 0);
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    window()->on_window_resize.addListener([this](){
	system("cls");
	this -> resizeCanvas(window() -> width(), window() -> height());
	static_assert(true, "window resized");
    });
}

Canvas::~Canvas() {}

void Canvas::clearCanvas(){
    for(int i=0; i < height(); i++){
	for (int j=0; j < width(); j++) {
	    canvas[i][j] = L' ';	
	}
    }
}

void Canvas::resizeCanvas(int const& width, int const& height){
    this -> _width = width;
    this -> _height = height;

    canvas = new wchar_t*[height];
    for (size_t i = 0; i < height; ++i) {
        canvas[i] = new wchar_t[width];
    }
}

int Canvas::width(){
    return _width;
}

int Canvas::height(){
    return _height;
}

void Canvas::update() { 
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
    border.reserve(width());
    for(int i =0; i < width(); i++) border += horz;

    std::wstring frame_buffer;
    frame_buffer.reserve((width() + 3) * (height() + 2));

    //add top border to the canvas
    frame_buffer += top_left + border + top_right + L"\n";

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
    writeToConsole(frame_buffer, width() + 3, height() + 2);
}

Vector2D<int> Canvas::clipPoint(Vector2D<int> const& point,int const& canvas_width, int const& canvas_height){
    int x = std::min(point.x,canvas_width - 1);
    x = std::max(x,0);

    int y = std::min(point.y,canvas_height-1);
    y = std::max(y,0);

    return Vector2D<int>(x,y);
}

void Canvas::drawASCII(ASCIIGraphic& graphics){
    auto transfom = graphics.getAttached<Transform>();
    auto pos = transfom -> position;
    auto mat = graphics.pixelMatrix();

    Vector2D<int> topLeft = clipPoint(pos - graphics.center, width(), height());
    Vector2D<int> size = Vector2D<int>(graphics.width(), graphics.height());
    Vector2D<int> bottomRight = clipPoint(pos + size - graphics.center, width(), height());

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

