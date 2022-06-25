#include "Player.h"
#include "ResourceManager.h"
#include <SDL\SDL.h>
#include <iostream>

void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera) {
	_speed = speed;
	_position = position;
	_camera = camera;
	_inputManager = inputManager;
	color.set(255, 255, 255, 255);
}

void Player::draw(SpriteBacth& spritebatch)
{
	//Animaciones Idle
	static int textureID1Idle = ResourceManager::getTexture("Textures/Player_Idle_1.png").id;
	static int textureID2Idle = ResourceManager::getTexture("Textures/Player_Idle_2.png").id;
	static int textureID3Idle = ResourceManager::getTexture("Textures/Player_Idle_3.png").id;
	//Animaciones Left
	static int textureID1Left = ResourceManager::getTexture("Textures/Player_Left_1.png").id;
	static int textureID2Left = ResourceManager::getTexture("Textures/Player_Left_2.png").id;
	static int textureID3Left = ResourceManager::getTexture("Textures/Player_Left_3.png").id;
	//Animaciones Right
	static int textureID1Right = ResourceManager::getTexture("Textures/Player_Right_1.png").id;
	static int textureID2Right = ResourceManager::getTexture("Textures/Player_Right_2.png").id;
	static int textureID3Right = ResourceManager::getTexture("Textures/Player_Right_3.png").id;

	//Cambiar de sprite
	if (_timer < 200) {
		_timer++;
	} else if (_spriteCount < 4 && _timer == 200) {
		_spriteCount++;
		_timer = 0;
	}
	else {
		_spriteCount = 1;
		_timer = 0;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	switch (_spriteCount)
	{
	case 1:
		if (_spriteDirection == -1)
			spritebatch.draw(destRect, uvRect, textureID1Left, 0.0f, color);
		else if (_spriteDirection == 1)
			spritebatch.draw(destRect, uvRect, textureID1Right, 0.0f, color);
		else
			spritebatch.draw(destRect, uvRect, textureID1Idle, 0.0f, color);
		break;
	case 2:
		if (_spriteDirection == -1)
			spritebatch.draw(destRect, uvRect, textureID2Left, 0.0f, color);
		else if (_spriteDirection == 1)
			spritebatch.draw(destRect, uvRect, textureID2Right, 0.0f, color);
		else
			spritebatch.draw(destRect, uvRect, textureID2Idle, 0.0f, color);
		break;
	case 3:
		if (_spriteDirection == -1)
			spritebatch.draw(destRect, uvRect, textureID3Left, 0.0f, color);
		else if (_spriteDirection == 1)
			spritebatch.draw(destRect, uvRect, textureID3Right, 0.0f, color);
		else
			spritebatch.draw(destRect, uvRect, textureID3Idle, 0.0f, color);
		break;
	case 4:
		if (_spriteDirection == -1)
			spritebatch.draw(destRect, uvRect, textureID2Left, 0.0f, color);
		else if (_spriteDirection == 1)
			spritebatch.draw(destRect, uvRect, textureID2Right, 0.0f, color);
		else
			spritebatch.draw(destRect, uvRect, textureID2Idle, 0.0f, color);
		break;
	}
	//spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies
	) {
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed / 2;
	}

	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed;
	}

	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed;
		_spriteDirection = -1;
	}
	else if (_spriteDirection == -1) {
		_spriteDirection = 0;
	}

	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed;
		_spriteDirection = 1;
	}
	else if (_spriteDirection == 1) {
		_spriteDirection = 0;
	}

	//Poner sprite en Idel si ambas direcciones a la vez presionadas
	if (_inputManager->isKeyDown(SDLK_d) && _inputManager->isKeyDown(SDLK_a)) {
		_spriteDirection = 0;
	}

	collideWithLevel(levelData);
}


Player::Player():_currentGun(-1)
{
}


Player::~Player()
{
}
