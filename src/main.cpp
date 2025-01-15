#include <iostream>
#include <ostream>
#include <thread>
#include "Core/CLI/ArgsParser.h"
#include "Core/Game.h"
#include "Components/ASCIISprite.h"
#include "SnakeGame/PlayerMovementController.h"

void runGame(Game game){
	game.run();
}

int main(int args, char* argv[]) {
	std::cout << "\033[?25l";
	std::cout << "starting game.."<< std::endl;

	auto arg_parser = ArgsParser(args,argv);
	auto arg = arg_parser.parse();	

	if(arg.debug_mode){
		std::cout << "running in debug mode"  << std::endl;
	}

	auto game = new Game();

	auto sprite = game -> createEntity("sprite");
	sprite -> getComponent<Transform>() -> position = Vector2D<float>(50,25);

	auto player_mvt_cmp = sprite -> addComponent<PlayerMovementController>();

	auto sprite_cmp = sprite->addComponent<ASCIISprite>();
	sprite_cmp -> useRaw("../resources/sprite.txt");	

	std::thread gameThread([&] {game -> run();});	
	gameThread.join();
	return 0;
}
