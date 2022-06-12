// PvZ.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Game.h"

int SDL_main(int argc, char* argv[])
{
	std::cout << "Start\n";

	Game game;
	bool success = game.Initialize();
	if (success) 
	{
		game.RunLoop();
	}
	game.Shutdown();
	std::cout << "End\n";

	return 0;
}