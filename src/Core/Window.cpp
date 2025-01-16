#include "Core/Window.h"
#include "Math/Vector2D.h"
#include <limits>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

Window::Window() {
    _origin_screen_coord = Vector2D<int>(0,0);
}

Window::~Window() {}

void Window::update(){
    int curr_width = width();
    int curr_height = height();
    if(_prev_width != curr_width || _prev_height != curr_height){
       on_window_resize.trigger();
    }

    _prev_width = curr_width;
    _prev_height = curr_height;
}

int Window::width(){
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
	int terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return terminalWidth - 2;
    }
#endif
    return std::numeric_limits<int>::max();
}

int Window::height(){
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
	int terminalHeight = csbi.srWindow.Bottom - (csbi.srWindow.Top + 1);
	return terminalHeight;
    }
#endif
    return std::numeric_limits<int>::max();
}

Vector2D<int> Window::originScreenCoord(){
    return _origin_screen_coord;
}
