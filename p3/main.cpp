#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "Game.h"
//#include "checkML.h"

using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game* pGame = new Game();
	try {
		pGame->run();

		delete pGame;
	}
	catch (string& error) {
		cout << error << endl;
	}

	//system("pause");
	return 0;
}