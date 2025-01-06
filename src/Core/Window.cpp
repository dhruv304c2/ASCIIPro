#include "Core/Window.h"
#include <limits>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

Window::Window() {}

Window::~Window() {}

void Window::update(){
    INPUT_RECORD input_record;
    if(input_record.EventType == WINDOW_BUFFER_SIZE_EVENT){
	on_window_resize.trigger();
    }
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
	int terminalWidth = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return terminalWidth - 5;
    }
#endif
    return std::numeric_limits<int>::max();
}

