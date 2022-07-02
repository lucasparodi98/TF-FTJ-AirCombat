#pragma once
#include "Agent.h"
#include "Enemy.h"

class Enemy;
class Bullet : public Agent
{
protected:
	//Tiempo de vida de la bala
	int timer = 0;
	glm::vec2 _direction;
public:
	Bullet();
	~Bullet();
	void init(float speed, glm::vec2 position);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	int getTimer();
};