#pragma once
#include "Human.h"
#include "InputManager.h"
#include <vector>
#include "Camera2D.h"
#include "Bullet.h"

class Player: public Human
{
private:
	InputManager* _inputManager;
	int _currentGun;
	Camera2D* _camera;
	//Retrasar la animación
	int _timer = 0;
	//Ver dirección 0 idel, -1 izquirda, 1 derecha
	int _spriteDirection = 0;
	//Contador de sprite
	int _spriteCount = 3;
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera);
	virtual void draw(SpriteBacth& spritebatch) override;
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	//std::vector<Bullet*> getBullets() { return _bullets; }
	//void setBullets(std::vector<Bullet*> bullets) { _bullets = bullets; }
};

