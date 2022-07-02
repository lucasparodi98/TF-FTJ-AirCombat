#include "Enemy.h"
#include "Human.h"
#include "ResourceManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	_direction = glm::vec2(0.0f, -1.0f);
	_direction = glm::vec2(_direction);
	color.set(255, 255, 255, 255);
}

void Enemy::draw(SpriteBacth& spritebatch)
{
	static int textureID1 = ResourceManager::getTexture("Textures/Enemy_1_Down.png").id;
	static int textureID2 = ResourceManager::getTexture("Textures/Enemy_2_Down.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	//Cambiar de sprite
	if (_timer < 200) {
		_timer++;
	}
	else if (_spriteCount < 2 && _timer == 200) {
		_spriteCount++;
		_timer = 0;
	}
	else {
		_spriteCount = 1;
		_timer = 0;
	}
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	switch (_spriteCount)
	{
	case 1:
		spritebatch.draw(destRect, uvRect, textureID1, 0.0f, color);
		break;
	case 2:
		spritebatch.draw(destRect, uvRect, textureID2, 0.0f, color);
		break;
	}
}

void Enemy::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	_position.y += _direction.y * _speed;
	_position.x += sin(_timerExtra);

	_timerExtra += 0.01f;
}


