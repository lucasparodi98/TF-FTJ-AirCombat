#include "Bullet.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>
#include <iostream>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::init(float speed, glm::vec2 position)
{
	_speed = speed;
	color.set(255, 255, 255, 255);
	_position = position;
	_direction = glm::vec2(0.0f, 1.0f);
	_direction = glm::vec2(_direction);
}

void Bullet::draw(SpriteBacth& spritebatch)
{
	static int textureID = ResourceManager::getTexture("Textures/bullet_orange.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, 10, 26);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Bullet::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	_position += _direction * _speed;
	timer++;
}

int Bullet::getTimer()
{
	return timer;
}
