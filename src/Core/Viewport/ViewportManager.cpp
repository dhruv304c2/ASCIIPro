#include "Core/Viewport/ViewportManager.h"
#include "Collection/BTree.h"
#include "Core/Viewport/Viewport.h"
#include "Core/Window.h"
#include "Math/Vector2D.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <unicode/unistr.h>

#ifdef _WIN64
#include <windows.h>
#endif

void writeToConsole(std::wstring const& frame_buffer, Vector2D<int> const& origin) {
#ifdef _WIN64
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE || hConsole == NULL) {
        std::wcerr << L"Error: Unable to get console handle.\n";
        return;
    }

    COORD pos = {static_cast<SHORT>(origin.x), static_cast<SHORT>(origin.y)};
    SetConsoleCursorPosition(hConsole,pos);

    // Write the wide string to the console
    DWORD charsWritten;
    WriteConsoleW(hConsole, frame_buffer.c_str(), static_cast<DWORD>(frame_buffer.size()), &charsWritten, NULL);
#endif
}

std::string wstringToUtf8(const std::wstring& wideString) {
    icu::UnicodeString unicodeString(wideString.c_str(), static_cast<int32_t>(wideString.length()));

    std::string utf8String;
    unicodeString.toUTF8String(utf8String);

    return utf8String;
}

ViewportManager::ViewportManager(Window* window) : _window(window) {
    _root = new Viewport(_window->width(), _window->height(), _window->originScreenCoord());
    _viewport_tree = new BTree<Viewport>(_root);
    _selected = _viewport_tree->root();
    std::cout << "created viewport width: " << _selected->item->width() << std::endl;
    std::cout << "created viewport height: " << _selected->item->height() << std::endl;
    std::cout << "view port manager created" << std::endl;

    _window->on_window_resize.addListener([&](){
	this->resize();
    });
}

ViewportManager::~ViewportManager() {}

void ViewportManager::start(){
    setvbuf(stdout, nullptr, _IONBF, 0);
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

ViewportNode* ViewportManager::selected(){
    return _selected;
}

ViewportNode* ViewportManager::root(){
    return _viewport_tree->root();
}

void ViewportManager::resize(){
    system("cls");
    _viewport_tree->recurse([&](BTreeNode<Viewport>* node) {
	int height = _window->height() * node->item->vertical_split;
	int width = _window->width() * node->item->horizontal_split;

	if(node->right) {
	    node->right->item->setOrigin(node->item->origin() + Vector2D<int>(width+1, 0));
	}else{
	    width = _window->width() - node->item->origin().x;
	}
	if(node->left) {
	    node->left->item->setOrigin(node->item->origin() + Vector2D<int>(0, height));
	}
	else {	
	    height = _window->height() - node->item->origin().y;
	}
	node->item->resize(width, height);
    });
}

ViewportNode* ViewportManager::split(ViewportNode* parent, ViewportSplit split_style, float split){
    if(split < 0) split = 0;
    if(split > 1) split = 1;
 
    auto parent_port = parent->item;

    switch (split_style) {
	case ViewportSplit::Horizontal: {

		///////////////////Executing split
		int old_port_width = parent_port->width() * split;
		int new_port_width = parent_port->width() - old_port_width - 1;
		parent_port->resize(old_port_width, parent_port->height());
		auto origin = parent_port->origin() + Vector2D<int>(parent_port->width() + 1 ,0);
		auto new_port_horz = new Viewport(new_port_width, parent_port->height(), origin);
		auto node = new ViewportNode(new_port_horz);
		parent->addRight(node); //Horizontal ports are added as right node

		///////////////////Saving split
		new_port_horz->horizontal_split = (parent_port->horizontal_split * (1 -split));
		parent_port->horizontal_split *= split;
		return node;
	}
	case ViewportSplit::Vertical: {
		
		///////////////////Executing split
		int old_port_height = parent_port->height() * split;
		int new_port_height = parent_port->height() - old_port_height;
		parent_port->resize(parent_port->width(), old_port_height);
		auto origin = parent_port->origin() + Vector2D<int>(0,parent_port->height());
		auto new_port_vert = new Viewport(parent_port->width(), new_port_height, origin);
		auto node = new ViewportNode(new_port_vert);
		parent->addLeft(node); //Vertical ports are added as left node

		///////////////////Saving split
		new_port_vert->vertical_split = (parent_port->vertical_split * (1-split));
		parent_port->vertical_split *= split;
		return node;
	}
	default:
		return nullptr;
    }
}

void clearCanvas(wchar_t** canvas, int const& width, int const& height){
    for(int i=0; i < height; i++){
	std::fill(canvas[i],canvas[i] + width,L' ');
    }
}

void ViewportManager::render(){
    int width, height;
    auto left_end = _viewport_tree->root()->item;
    auto top_end = left_end;
    auto right_end = _viewport_tree->rightMostNode()->item;
    auto bottom_end = _viewport_tree->leftMostNode()->item;

    int left_lt = left_end->origin().x;
    int right_lt = right_end->topRight().x;
    int top_lt = top_end->origin().y;
    int bottom_lt = bottom_end->bottomLeft().y;

    int w = right_lt - left_lt;
    int h = bottom_lt - top_lt;

    //allocating canvas memory 
    //TODO: should not be heap allocated each frame should be pre-allocated
    wchar_t** canvas = new wchar_t*[h];
    for(int i=0; i < h; i++){
	canvas[i] = new wchar_t[w];
    }
    clearCanvas(canvas, w, h);
    _viewport_tree->root()->forEach([&](Viewport* port) {
	port->writeToBuffer(canvas, w, h);
    });

    std::wstring frame_buffer;
    frame_buffer += L"\033[32m";
    for(int i=0; i < h; i++){
	for(int j=0; j < w; j++){
	    frame_buffer += canvas[i][j];
	}
	frame_buffer += L'\n';
    }

    writeToConsole(frame_buffer, _root->origin());
}

void ViewportManager::select(ViewportNode* node){
    _selected = node;
}
