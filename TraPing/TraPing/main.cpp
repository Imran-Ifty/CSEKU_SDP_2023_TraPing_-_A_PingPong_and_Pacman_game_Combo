#include "Game.h"
#include "Header.h"
int main(void)
{
#if defined(_DEBUG)
	std::cout << "TraPing" << std::endl;
#endif

	Game* g = new Game();

	g->RunGame();

	return EXIT_SUCCESS;
}