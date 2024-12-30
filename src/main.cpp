#include <iostream>
#include <ostream>
#include <thread>
#include "Core/Game.h"
#include "Components/Canvas.h"
#include "Components/ASCIISprite.h"
#include "SnakeGame/PlayerMovementController.h"

void runGame(Game game){
	game.run();
}

int main() {
	std::cout << "\033[?25l";
	std::cout << "starting game.." << std::endl;

	auto game = new Game(0.1f);

	auto canvasEnt = game->createEntity("canvasEnt");
	canvasEnt->addComponent<Canvas>();

	auto sprite = game -> createEntity("sprite");
	sprite -> getComponent<Transform>() -> position = Vector2D<float>(50,25);

	auto player_mvt_cmp = sprite -> addComponent<PlayerMovementController>();
	player_mvt_cmp -> speed = Vector2D<float>(1,1);

	auto player_sprite_exp = SpriteExport("../resources/sprite.txt");
	auto sprite_cmp = sprite->addComponent<ASCIISprite>();
	sprite_cmp -> useExport(player_sprite_exp);	

	std::thread gameThread([&] {game -> run();});	
	gameThread.join();
	return 0;
}
