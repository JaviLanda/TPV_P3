#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(Game* g) : GameState(g) {
	app = g;
	rend = g->getRend();

	vidas = 3;

	initObjects();
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
	//int aux = rand() % REWARD_CHANCE;
	int aux = 0;
	if (aux == 0) {
		int r = rand() % 4;
		switch (r) {
		case 0:
			objects.push_back(new RewardX1(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			//static_cast<RewardX1*>(objects.back())->setIt(--(objects.end()));
			break;
		case 1:
			objects.push_back(new RewardX2(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			//static_cast<RewardX2*>(objects.back())->setIt(--(objects.end()));
			break;
		case 2:
			objects.push_back(new RewardX3(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			//static_cast<RewardX3*>(objects.back())->setIt(--(objects.end()));
			break;
		case 3:
			objects.push_back(new RewardX4(rend, app->getText(Game::TReward), rect.x, rect.y, this));
			//static_cast<RewardX4*>(objects.back())->setIt(--(objects.end()));
			break;
		default:
			break;
		}
	}
}

//------------------UPDATE-----------
void PlayState::update() {

	GameState::update();

	//Comprobacion de no mas bloques
	if (static_cast<BlockMap*>(*mapIt)->getNumBlocks() == 0) nextLevel();

	if (win || lose) { 
		app->getStateMachine()->changeState(new EndState(app)); 
	}

	//if (nivel) nextLevel();
	//if (level > 2) win = true;

	/*
	auto it = objects.begin();
	while (it != objects.end()) {
		auto next = it;
		++next;
		if (static_cast<ArkanoidObject*>(*it)->getActive()) (*it)->update();
		else {
			killObjects.push_back(*it);
			objects.remove(*it);
		}
		it = next;
	}*/
	
}

/*
//--------------------RENDER---------------
void Game::render() const {
SDL_RenderClear(renderer); //Eliminamos lo que hay en pantalla
//Render de cada objeto
for (auto it = objects.begin(); it != objects.end(); it++) {
(*it)->render();
}

//Dibujado de la puntuacion
stringstream strm;
strm << "Score: " << puntuacion << "                " << "Vidas: " << vidas;
tScore->loadFont(renderer, font, strm.str().c_str(), red);

tScore->render(scoreRect);

SDL_RenderPresent(renderer);
}

*/

//--------------------HANDLE_EVENTS------------
void PlayState::handleEvents(SDL_Event& e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_p:
			app->getStateMachine()->pushState(new PauseState(app));
			break;
		case SDLK_o:
			nextLevel();
			break;
		default:
			break;
		}
	}

	GameState::handleEvents(e);
	//return true;
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
			puntuacion++;
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
	if (level < 3) {
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

/*
//----------------------------Cargar--------------------------------
void Game::load() {
ifstream f;
f.open(SAVEFILE);

bool end = false;
int tempCode = 0;
cout << "Introduce codigo de partida: ";
cin >> tempCode;

while (!end) {
f >> code;
if (f.fail()) {
cout << "No existe esa partida." << endl;
system("pause");
end = true;
}
f >> numLin;
if (tempCode != code) {
for (int i = 0; i < numLin; i++) {
f.ignore(INT_MAX, '\n');
}
}
else {
//cout << "Lo he encontrado pavo";
//Lectura
initObjectsFromFile(f);
end = true;
}
}

f.close();
}

void Game::initObjectsFromFile(ifstream& f) {
//Cargamos la vida y la puntuacion
f >> vidas >> puntuacion;

//Iniciamos los objetos
blockMap = new BlockMap(renderer, nTexturas[TBrick]);
objects.push_front(blockMap);
mapIt = objects.begin();
objects.push_back(new Ball(renderer, nTexturas[TBall], this));
ballIt = --(objects.end());
objects.push_back(new Paddle(renderer, nTexturas[TPaddle], this));
paddleIt = --(objects.end());
objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_L_ROOF, false));
objects.push_back(new Wall(renderer, nTexturas[TSide], POS_WALL_R, false));
objects.push_back(new Wall(renderer, nTexturas[TTopSide], POS_WALL_L_ROOF, true));
lastIt = --(objects.end());

//Cargamos los valores de los objetos del fichero
for (auto it = objects.begin(); it != objects.end(); it++) {
(*it)->loadFromFile(f);
}
//Fallan los objetos Wall
//
//

//Calculamos y añadimos los posibles rewards
numRewards = numLin - 7 - blockMap->numRow();
for (int i = 0; i < numRewards; i++) {
objects.push_back(new Reward(renderer, nTexturas[TReward], 0, 0, this));
auto it = --objects.end();
(*it)->loadFromFile(f);
}
}

//--------------------------Guardar---------------------------
void Game::save() {

//Añadir comprobacion de codigo en caso de que ya exista una partida guardada con ese codigo.

fstream f;
f.open(SAVEFILE, fstream::out | fstream::in | fstream::app);

int nRow = static_cast<BlockMap*>(*mapIt)->numRow();
nRow++;

for (auto it = objects.begin(); it != objects.end(); it++) {
nRow++;
}

cout << "Introduce codigo de partida: ";
cin >> code;
f << code << " " << nRow << endl;
f << vidas << " " << puntuacion << endl;

for (auto it = objects.begin(); it != objects.end(); it++) {
(*it)->saveToFile(f);
nRow++;
}

f.close();
}
*/

//---------------------------------------------Destructoras------------------------------------------
PlayState::~PlayState() {
	deleteObjects();
}

void PlayState::deleteObjects() {
	for (auto i : killObjects) {
		delete i;
		i = nullptr;
	}
}