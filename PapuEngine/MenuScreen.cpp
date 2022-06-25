#include "MenuScreen.h"



MenuScreen::MenuScreen(Window* window):_window(window)
{
	
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::build()
{
	background = new Background("Textures/Fondos/Menu.png");
}

void MenuScreen::destroy()
{
}

void MenuScreen::onExit()
{
}

void MenuScreen::onEntry()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
	_spriteBatch.init();
	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	spriteFont = new SpriteFont("Fonts/Fuente1.ttf", 40);
	
}

void MenuScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();

	//background->draw(_spriteBatch);
	char buffer[256];
	sprintf_s(buffer, "HOLA %d", 100);
	Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-100, 50), glm::vec2(1), 0.0f, color);

	sprintf_s(buffer, "HOLA 2 %d", 100);
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-200, 150), glm::vec2(1), 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void MenuScreen::update()
{
	draw();
	_camera.update();
	checkInput();
}

void MenuScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		default:
			break;
		}
	}
}

int MenuScreen::getNextScreen() const
{
	return 0;
}

int MenuScreen::getPreviousScreen() const
{
	return 0;
}
