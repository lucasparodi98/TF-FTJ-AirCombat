#pragma once
#include "Agent.h"

class Object_Background : public Agent
{
protected:
	glm::vec2 _direction;
	//Tiempo de vida del objeto
	float _size;
public:
	Object_Background();
	~Object_Background();
	void init(float speed, glm::vec2 position);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

