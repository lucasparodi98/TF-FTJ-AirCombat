#include "Button.h"
#include "ResourceManager.h"
#include <iostream>

Button::Button(std::string _path) :path(_path)
{
	_textureID = ResourceManager::getTexture(path).id;
}

Button::~Button()
{
}

void Button::draw(SpriteBacth& spriteBatch, glm::vec4 positionB)
{
	Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	_buttonPosition = positionB;
	//glm::vec4 destRect(-160, 0, 330, 100);
	spriteBatch.draw(_buttonPosition, uvRect, _textureID, 0.0f, color);
}

bool Button::click(glm::vec2 position)
{
	if (position.x >= _buttonPosition.x && position.x <= _buttonPosition.x + _buttonPosition.z) {
		std::cout << "Las x son iguales" << std::endl;
		if (position.y >= _buttonPosition.y && position.y <= _buttonPosition.y + _buttonPosition.w) {
			std::cout << "Las y son iguales" << std::endl;
			return true;
		}
	}
	return false;
}
