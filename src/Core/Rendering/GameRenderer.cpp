#include "Core/Rendering/GameRenderer.h"
#include "Core/Game.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/Viewport.h"

GameRenderer::GameRenderer(Viewport* viewport, Game* game) : Renderer(viewport, game) {}

GameRenderer::~GameRenderer() {}

void GameRenderer::render(){
    for(auto graphic :_game->allComponent<ASCIIGraphic>()){
	    drawASCII(*graphic);
    }
}

void GameRenderer::drawASCII(ASCIIGraphic& graphics){
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
	    _viewport->buffer[i][j] = pix;
	}
    }
}

