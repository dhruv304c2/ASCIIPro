#include <iostream>
#include <thread>
#include "../includes/Core/Time.h"
#include "../includes/Core/Game.h"

void runGame(Game game){
	game.run();
}

int main() {
	std::cout << "\033[?25l";
	std::cout << "starting game..";
	Time* time = new Time();
	auto game = new Game(time, 0.01f);

	auto canvasEnt = game->createEntity("canvasEnt");
	canvasEnt->addComponent(CANVAS);

	std::thread gameThread([&] {game -> run();});
	gameThread.join();
	return 0;
}

