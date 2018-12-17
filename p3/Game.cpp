#include "Game.h"

#include "GameObject.h"
#include "MainMenuState.h"
#include "PlayState.h"

Game::Game() {
	initSDL();
	initTextures();

	stateMachine = new GameStateMachine();
	stateMachine->pushState(new MainMenuState(this));
}

Game::~Game() {
	closeSDL();
	destroyTextures();
}

//--------------------------------------------Inicializacion de Objetos--------------------------------------------
bool Game::initSDL() {
	bool load = true;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw SDLError(SDL_GetError());
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		bool load = false;
	}
	else {
		window = SDL_CreateWindow("SDL ARKANOID", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			throw SDLError(SDL_GetError());
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			bool load = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				throw SDLError(SDL_GetError());
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				bool load = false;
			}
		}
	}
	//if (TTF_Init() < 0)	throw SDLError("Error al cargar la librería TTF");

	return load;
}

void Game::initTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		nTexturas[i] = new Texture(renderer);
		nTexturas[i]->load(IMAGES_PATH + TEXT_ATT[i].nombre, TEXT_ATT[i].row, TEXT_ATT[i].col);
		if (nTexturas[i] == nullptr) {
			throw SDLError(SDL_GetError());
			cout << "Textures could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
		}
	}
}

//-------------Run------------

void Game::run() {
	Uint32 MSxUpdate = 120;
	//cout << "Play \n" << endl;
	Uint32 lastUpdate = SDL_GetTicks();
	while (!end) {
		if (SDL_GetTicks() - lastUpdate >= MSxUpdate) {//while(elapsed >= MSxUpdate)
			handleEvents();
			update();
			render();
			lastUpdate = SDL_GetTicks();
		}
		//stateMachine->currentState()->update();
		//stateMachine->currentState()->render();
		//stateMachine->currentState()->handleEvent();
	}
}

//Maneja los eventos de entrada
void Game::handleEvents() {
	SDL_Event e;

	//stateMachine->currentState()->handleEvent(e);

	while (SDL_PollEvent(&e) && !exit) {
		if (e.type == SDL_QUIT)	end = true;
		else stateMachine->currentState()->handleEvent(e);
	}
}

//Update de los objetos
void Game::update() {
	stateMachine->currentState()->update();
}

//Renderizado / dibujado
void Game::render() {
	SDL_RenderClear(renderer); //Limpiamos pantalla
	stateMachine->currentState()->render(); //Preparamos el dibujado de los obejtos
	SDL_RenderPresent(renderer); //Dibujamos
}

void Game::destroyTextures() {
	for (auto i : nTexturas) {
		delete i;
		i = nullptr;
	}
}

void Game::closeSDL() {
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}