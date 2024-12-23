#include <iostream>
#include <thread>
#include "../includes/Core/Time.h"
#include "../includes/Core/Game.h"
#include "../includes/Components/Canvas.h"
#include "../includes/Components/ASCIISprite.h"
#include "../includes/SnakeGame/PlayerMovementController.h"
#include <windows.h>

void runGame(Game game){
	game.run();
}

int main() {
	std::cout << "\033[?25l";
	std::cout << "starting game..";
	Time* time = new Time();
	auto game = new Game(time, 0.1f);

	auto canvasEnt = game->createEntity("canvasEnt");
	canvasEnt->addComponent<Canvas>();

	auto sprite = game -> createEntity("sprite");
	sprite -> getComponent<Transform>() -> position = Vector2D<float>(50,25);

	auto playerMvtCmp = sprite -> addComponent<PlayerMovementController>();
	playerMvtCmp -> speed = Vector2D<float>(1,1);

	auto sprite_cmp = sprite->addComponent<ASCIISprite>();
	sprite_cmp -> sprite =
	{{'#','#','#'},
	 {'#','#','#'},
	 {'#','#','#'},};

	std::thread gameThread([&] {game -> run();});
	while (true) {
		if (GetAsyncKeyState('W') & 0x8000) {
		    std::cout << "Moving Up!" << std::endl;
		}
	}
	gameThread.join();
	return 0;
}

