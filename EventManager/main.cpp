#include "Game.h"

int main() {
	Game game;
	while (!game.IsDone()) {
		game.HandleInput();
		game.Update();
		game.Render();
	}
	return 0;
}