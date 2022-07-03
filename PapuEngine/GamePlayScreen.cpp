#include "GamePlayScreen.h"
#include "Game.h"
#include "ScreenIndices.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <random>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GamePlayScreen::GamePlayScreen(Window* window):
	_window(window)
{
}


GamePlayScreen::~GamePlayScreen()
{
}


void GamePlayScreen::build() {
	_levels.push_back(new Level("Levels/level0.txt"));

	//Crear Islas iniciales
	_objects.push_back(new Object_Background);
	_objects.back()->init(0.1f, glm::vec2(150.0f, 500.0f));
	_objects.push_back(new Object_Background);
	_objects.back()->init(0.1f, glm::vec2(400.0f, 350.0f));
	_objects.push_back(new Object_Background);
	_objects.back()->init(0.1f, glm::vec2(650.0f, 800.0f));


	_player = new Player();
	_currenLevel = 0;
	_player->init(1.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera);
	//_humans.push_back(_player);
	_spriteBatch.init();

	srand(time(NULL));
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, _levels[_currenLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(
		1, _levels[_currenLevel]->getHeight() - 2);

	/*for (int i = 0; i < _levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}*/

	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currenLevel]->getZombiesPosition();

	/*for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(1.3f, zombiePosition[i]);
	}*/
	background = new Background("Textures/Fondos/airPlanesBackground.png");
}
void GamePlayScreen::destroy() {

}
void GamePlayScreen::onExit() {
}
void GamePlayScreen::onEntry() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();

	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
}
void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);

	/*GLuint timeLocation =
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();
	//background->draw(_spriteBatch);

	//Dibujar Objetos de Fondo
	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->draw(_spriteBatch);
	}

	_player->draw(_spriteBatch);

	//Dibujar Balas
	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->draw(_spriteBatch);
	}

	
	//Dibujar Enemigos
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->draw(_spriteBatch);
	}
	//background->draw(_spriteBatch);
	_levels[_currenLevel]->draw();
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}
void GamePlayScreen::update() {
	lag++;
	if (lag == 5) {
		checkInput();
		draw();
		_camera.update();
		updateAgents();
		_inputManager.update();
		_camera.setPosition(_player->getPosition() + glm::vec2(0.0f, 200.0f));
		lag = 0;
	}

}


void GamePlayScreen::updateAgents() {

	//Jugador
	_player->update(_levels[_currenLevel]->getLevelData(),
		_humans, _zombies);
	if (cooldownBullet > 0) cooldownBullet--;

	//Balas
	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies);
		if (_bullets[i]->getTimer() == 2000) {
			delete _bullets[i];
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
	}

	//Crear objetos aleatoriamente
	int _generator = rand() % 500 + 1;
	int _position = rand() % 680 + 64;

	//std::cout << _enemyPosition << endl;

	if (_generator == 100 && _enemies.size() < 10) {
		_enemies.push_back(new Enemy);
		_enemies.back()->init(0.3f, glm::vec2(_position, 1000.0f));
	}

	_generator = rand() % 3000 + 1;

	//Agregar objeto de fondo
	if (_generator < 5 && _objects.size() < 30) {
		_objects.push_back(new Object_Background);
		_objects.back()->init(0.1f, glm::vec2(_position, 1000.0f));
	}

	//Update Enemigos
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);
		if (_enemies[i]->getPosition().y < -100.0f) {
			delete _enemies[i];
			_enemies[i] = _enemies.back();
			_enemies.pop_back();
		}
	}

	//Update Objeetos de fondo
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);
		if (_objects[i]->getPosition().y < -100.0f) {
			delete _objects[i];
			_objects[i] = _objects.back();
			_objects.pop_back();
		}
	}

	//Impactar enemigos
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);
		for (size_t j = 1; j < _bullets.size(); j++)
		{
			if (_enemies[i]->collideWithAgent(_bullets[j])) {
				delete _enemies[i];
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				delete _bullets[j];
				_bullets[j] = _bullets.back();
				_bullets.pop_back();
				break;
			}
		}
	}

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);

		if (_enemies[i]->collideWithAgent(_player)) {
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}

	
}

void GamePlayScreen::checkInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
		if (_inputManager.isKeyDown(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
	}
	//Disparar Balas
	if (_inputManager.isKeyDown(SDLK_SPACE) && cooldownBullet == 0) {
		_bullets.push_back(new Bullet);
		_bullets.back()->init(1.0f, glm::vec2(_player->getPosition().x + (AGENT_WIDTH / 2) - 3, _player->getPosition().y + (AGENT_WIDTH / 2)));
		cooldownBullet = 100;
	}
}

int GamePlayScreen::getNextScreen() const {
	return SCREEN_INDEX_GAMEOVER;
};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_GAMEOVER;
}
