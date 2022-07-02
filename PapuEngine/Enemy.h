#pragma once
#include "Agent.h"

class Enemy : public Agent
{
private:
	glm::vec2 _direction;
	//Retrasar la animación
	int _timer = 0;
	float _timerExtra = 0.00f;
	//Contador de sprite
	int _spriteCount = 1;
	//Vidas
	int _healthPoints = 1;

public:
	Enemy();
	~Enemy();

	void init(float speed, glm::vec2 position);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	virtual void draw(SpriteBacth& spritebatch) override;

	int getHealthPoints() { return _healthPoints; }
};

