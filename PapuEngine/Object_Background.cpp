#include "Object_Background.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>
#include <iostream>

Object_Background::Object_Background()
{
}

Object_Background::~Object_Background()
{
}

void Object_Background::init(float speed, glm::vec2 position)
{
	_speed = speed;
	color.set(255, 255, 255, 255);
	_position = position;
	_direction = glm::vec2(0.0f, -1.0f);
	_direction = glm::vec2(_direction);
	_size = rand() % 7;
	_size = (_size / 10) + 1;
	std::cout << _size << std::endl;
}

void Object_Background::draw(SpriteBacth& spritebatch)
{
	static int textureID = ResourceManager::getTexture("Textures/GrassIsland.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, 64 * _size, 48 * _size);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Object_Background::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	_position += _direction * _speed;
}
