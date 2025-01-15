#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Components/ASCIIGraphic.h"
#include "Core/Rendering/Renderer.h"

class Viewport;
class Game;

class GameRenderer : public Renderer {
public:
    GameRenderer(Viewport* viewport, Game* game);
    ~GameRenderer();
    void render() override;
private:
    void drawASCII(ASCIIGraphic& graphics);
};

#endif
