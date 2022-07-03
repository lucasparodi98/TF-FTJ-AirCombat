#pragma once
#include "IGameScreen.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "Background.h"
#include "SpriteFont.h"
#include "Camera2D.h"
#include "Button.h"
#include "InputManager.h"


class MemberScreen : public IGameScreen
{
protected:
	int _screenIndex = 2;
private:
	GLS_Program _program;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	Background* background;
	Button* _buttonVolver;
	InputManager inputManager;
	Camera2D _camera;
	void checkInput();
	SpriteFont* spriteFont;
	SpriteFont* spriteFont2;
public:
	MemberScreen(Window* window);
	~MemberScreen();
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void draw()override;
	virtual void update()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;

};

