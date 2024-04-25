#include <SDL/SDL.h>
#include "MainGame.h"

int main(int argc, char** argv) {
	MainGame game;
	game.run();
	system("pause");
	return 0;
}