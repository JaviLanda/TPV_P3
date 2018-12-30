#include <time.h>

#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(Game* g) : GameState(g) {
	srand(time(0));

	app = g;
	rend = g->getRend();

	vidas = 3;

	firstUpdate = true;
	app->scoreRect.x = (WIN_WIDTH / 2) + 50;
	app->scoreRect.y = -5;
	app->scoreRect.w = 300;
	app->scoreRect.h = 50;
}

bool PlayState::OnEnter() {
	cout << "En el PlayState" << endl;
	return true;
}

bool PlayState::OnExit() {
	cout << "Saliendo del PlayState" << endl;
	return true;
}

void PlayState::initObjects() {
	initMap();
	objects.push_back(new Ball(rend, app->getText(Game::TBall), this));
	ballIt = --(objects.end());
	objects.push_back(new Paddle(rend, app->getText(Game::TPaddle), this));
	paddleIt = --(objects.end());
	objects.push_back(new Wall(rend, app->getText(Game::TSide), POS_WALL_L_ROOF, false));
	objects.push_back(new Wall(rend, app->getText(Game::TSide), POS_WALL_R, false));
	objects.push_back(new Wall(rend, app->getText(Game::TTopSide), POS_WALL_L_ROOF, true));
	lastIt = --(objects.end());
}

void PlayState::initMap() {
	blockMap = new BlockMap(rend, app->getText(Game::TBrick));
	if (level < 3) blockMap->load(maps[level]);
	if (blockMap == nullptr) {
		//throw FileNotFoundError(SDL_GetError());
		cout << "Map cannot be loaded! \nSDL_Error: " << SDL_GetError() << '\n';
	}
	objects.push_front(blockMap);
	mapIt = objects.begin();
}

void PlayState::createReward(const SDL_Rect &rect) {
	int aux = rand() % REWARD_CHANCE;
	if (aux == 0) {
		int r = rand() % 4;
		switch (r) {
		case 0:
			objects.push_back(new RewardX1(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			break;
		case 1:
			objects.push_back(new RewardX2(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			break;
		case 2:
			objects.push_back(new RewardX3(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			break;
		case 3:
			objects.push_back(new RewardX4(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			break;
		default:
			break;
		}
	}
}

//------------------UPDATE-----------
void PlayState::update() {
	if (firstUpdate) {
		if (!l) { initObjects(); }
		else load();
		firstUpdate = false;
	}

	if (!win && !lose) {	//Comprobacion de fin de partida

		GameState::update();

		//Comprobacion de siguiente nivel
		if (static_cast<BlockMap*>(*mapIt)->getNumBlocks() == 0) nextLevel();
		if (nivel) nextLevel();

		//Comprobacion de guardado
		if (s) { save(); }
	}
	else {
		app->getStateMachine()->changeState(new EndState(app));
	}
	//if (win || lose) { app->getStateMachine()->changeState(new EndState(app)); }
}


//--------------------RENDER---------------
void PlayState::render() {
	
	GameState::render();
	
	//Dibujado de la puntuacion
	stringstream strm;
	strm << "Score: " << app->getScore() << "                " << "Vidas: " << vidas;
	app->tScore->loadFont(rend, app->font, strm.str().c_str(), app->red);

	app->tScore->render(app->scoreRect);
}

//--------------------HANDLE_EVENTS------------
void PlayState::handleEvents(SDL_Event& e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_p:	//Pausa
			app->getStateMachine()->pushState(new PauseState(app));
			break;
			//---------------CHEATS	(only programmers will know)-------------
		case SDLK_o:	//Pasar de nivel
			nextLevel();
			break;
		case SDLK_i:	//Añadir vida
			addLife();
			break;
		default:
			break;
		}
	}

	GameState::handleEvents(e);
}

//--------------------------------------------------------------Colisiones-------------------------------------------------------
bool PlayState::collidesBall(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector) {
	bool c = false;

	//Caso especial en caso de bug y que se salga de la pantalla, para poder seguir jugando(no se deberia llamar nunca)
	if (rect.x < 0 || rect.y < 0) {
		c = true;
		pierdeVida();
	}

	//Colisiones con muros
	if (rect.y - WALL_WIDTH < 5) {//Muro de arriba
		c = true;
		collVector = { 0, -1 };
	}
	else if (rect.y > WIN_HEIGHT - 20) { //game over (Parte inferior)
		c = true;
		pierdeVida();
	}
	else if ((rect.x + rect.w) - (WIN_WIDTH - WALL_WIDTH) < 5) { //Parte der
		c = true;
		collVector = { -1, 0 };
	}
	else if (rect.x - WALL_WIDTH < 5) { //Parte izq
		c = true;
		collVector = { 1, 0 };
	}

	//Colisiones con Bloques
	Block* block = nullptr;
	block = static_cast<BlockMap*>(*mapIt)->collides(rect, vel, collVector);
	if (block != nullptr) {
		if (block->getActive()) {
			static_cast<BlockMap*>(*mapIt)->ballHitsBlock(block);
			c = true;
			app->addScore();
			createReward(block->getRect());
		}
	}

	//Colisiones con paddle
	if (static_cast<Paddle*>(*paddleIt)->collidesBall(rect, collVector)) c = true;

	return c;
}

bool PlayState::collidesReward(const SDL_Rect &rect) {
	bool b = static_cast<Paddle*>(*paddleIt)->collidesReward(rect);
	return b;
}

//----------------------------------------------Diversos-----------------------------------------
//Siguiente nivel
void PlayState::nextLevel() {
	if (level < 2) {
		nivel = false;
		level++;

		//Eliminamos el mapa que sino se queda basura, no se como hacerlo mejor jeje
		delete *mapIt;
		objects.pop_front();
		initMap();

		// Reespauneamos la bola y el paddle
		static_cast<Ball*>(*ballIt)->respawn();
		static_cast<Paddle*>(*paddleIt)->respawn();

		// Eliminamos los premios sobrantes
		auto it = ++lastIt;
		while (it != objects.end()) {
			auto next = it;
			++next;
			killObjects.push_back(*it);
			objects.remove(*it);
			it = next;
		}

		// Actualizamos el ultimo iterador de nuevo para que apunte al ultimo objeto del juego que no sea un reward
		lastIt = --(objects.end());
	} 
	else win = true;
}

void PlayState::pierdeVida() {
	vidas--;
	static_cast<Ball*>(*ballIt)->respawn();
	if (vidas <= 0) {
		lose = true;
	}
}

void PlayState::powerUp(int type) {
	static_cast<Paddle*>(*paddleIt)->powerUp(type);
}

//----------------------------Cargar--------------------------------
void PlayState::load() {
	cout << "Introduce codigo de partida: ";
	cin >> tempCode;

	if (tempCode == -1) lose = true;

	while (tempCode != -1 && !searchGame(tempCode)) {
		cout << "No existe la partida solicitada, por favor introduzca otro codigo o '-1' para salir." << endl;
		cout << "Codigo: ";
		cin >> tempCode;
		if (tempCode == -1) lose = true;
	}

	ifstream f;
	f.open(SAVEFILE);

	f >> code;
	f >> numLin;
	initObjectsFromFile(f);

	f.close();
}

void PlayState::initObjectsFromFile(ifstream& f) {
	//Cargamos la vida, puntuacion y nivel
	int tPuntos = 0;
	f >> vidas >> tPuntos >> nivel;

	app->setScore(tPuntos);

	//Iniciamos los objetos
	blockMap = new BlockMap(rend, app->getText(Game::TBrick));
	objects.push_front(blockMap);
	mapIt = objects.begin();
	objects.push_back(new Ball(rend, app->getText(Game::TBall), this));
	ballIt = --(objects.end());
	objects.push_back(new Paddle(rend, app->getText(Game::TPaddle), this));
	paddleIt = --(objects.end());
	objects.push_back(new Wall(rend, app->getText(Game::TSide), POS_WALL_L_ROOF, false));
	objects.push_back(new Wall(rend, app->getText(Game::TSide), POS_WALL_R, false));
	objects.push_back(new Wall(rend, app->getText(Game::TTopSide), POS_WALL_L_ROOF, true));
	lastIt = --(objects.end());

	//Cargamos los valores de los objetos del fichero
	for (auto it = objects.begin(); it != objects.end(); it++) {
		static_cast<ArkanoidObject*>(*it)->loadFromFile(f);
	}

	//Calculamos y añadimos los posibles rewards
	numRewards = numLin - 7 - blockMap->numRow();
	for (int i = 0; i < numRewards; i++) {
		objects.push_back(new Reward(rend, app->getText(Game::TReward), 0, 0, this));
		auto it = --objects.end();
		static_cast<ArkanoidObject*>(*it)->loadFromFile(f);
	}
}

//Busqueda de codigo en el archivo de guardados
bool PlayState::searchGame(int c) {
	ifstream f;
	f.open(SAVEFILE);

	bool end = false;
	bool found = false;

	while (!end) {
		f >> code;
		if (f.fail()) {
			end = true;
		}
		f >> numLin;
		if (c != code) {
			for (int i = 0; i < numLin + 1; i++) {
				f.ignore(INT_MAX, '\n');
			}
		}
		else { //Lo encuentra!
			end = true;
			found = true;
		}
	}

	f.close();
	return found;
}

//--------------------------Guardar---------------------------
void PlayState::save() {
	cout << "Introduce codigo de partida: ";
	cin >> tempCode;

	while (searchGame(tempCode)) {
		cout << "Ya existe una partida guardada con ese codigo, por favor introduce un codigo diferente." << endl;
		cout << "Codigo: ";
		cin >> tempCode;
	}

	//Añadir comprobacion de codigo en caso de que ya exista una partida guardada con ese codigo.
	fstream f;
	f.open(SAVEFILE, fstream::out | fstream::in | fstream::app);

	int tPuntos = app->getScore();

	int nRow = static_cast<BlockMap*>(*mapIt)->numRow();
	nRow++;

	for (auto it = objects.begin(); it != objects.end(); it++) {
		if (static_cast<ArkanoidObject*>(*it)->getActive()) {
			nRow++;
		}
	}

	f << tempCode << " " << nRow << endl;							//Codigo y numero_de_filas
	f << vidas << " " << tPuntos << " " << nivel << endl;		//Vidas, puntuacion y nivel

	for (auto it = objects.begin(); it != objects.end(); it++) {
		if (static_cast<ArkanoidObject*>(*it)->getActive()) {
			static_cast<ArkanoidObject*>(*it)->saveToFile(f);
			nRow++;
		}
	}

	f.close();

	saveBool(false);
}

//---------------------------------------------Destructoras------------------------------------------
PlayState::~PlayState() {
	deleteObjects();
}

void PlayState::deleteObjects() {
	/*for (auto o : objects) {
		delete o;
		o = nullptr;
	}*/
	for (auto i : killObjects) {
		delete i;
		i = nullptr;
	}
}