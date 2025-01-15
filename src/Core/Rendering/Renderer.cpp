#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/Viewport.h"
#include "Core/Game.h"
#include "Math/Vector2D.h"
#include <cassert>
#include <algorithm>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

Renderer::Renderer(Viewport* viewport, Game* game): _viewport(viewport), _game(game) {}

Renderer::~Renderer() {}

void Renderer::update(){
    _viewport->clearViewportBuffer();
    render();
}

void Renderer::render(){}

Vector2D<int> Renderer::clipPoint(Vector2D<int> const& point){
    int x = std::min(point.x,_viewport->width()-1);
    x = std::max(x,0);

    int y = std::min(point.y,_viewport->height()-1);
    y = std::max(y,0);

    return Vector2D<int>(x,y);
}

ViewportRect Renderer::viewport(){
    auto rect = ViewportRect();
    rect.width = _viewport->width();
    rect.height = _viewport->height();
    rect.origin = _viewport->origin();
    return rect;
}

