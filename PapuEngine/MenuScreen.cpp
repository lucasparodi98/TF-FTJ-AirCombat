#include "MenuScreen.h"
#include "ScreenIndices.h"


MenuScreen::MenuScreen(Window* window):_window(window)
{
	
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::build()
{
	background = new Background("Textures/Fondos/Menu_Avion.png");
	//_buttonPlay = new Button("Textures/btn_jugar.png");
	_buttonMembers = new Button("Textures/btn_integrantes.png");
}

void MenuScreen::destroy()
{
	//_buttonPlay = nullptr;
	_buttonMembers = nullptr;
	background = nullptr;
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
	spriteFont = new SpriteFont("Fonts/Fuente2.ttf", 80);
	
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

	background->draw(_spriteBatch);
	//_buttonPlay->draw(_spriteBatch, glm::vec4(-160, 0, 330, 100));
	_buttonMembers->draw(_spriteBatch, glm::vec4(-160, -150, 330, 100));
	char buffer[256];
	sprintf_s(buffer, "AIRCOMBAT");
	Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-210, 150), glm::vec2(1), 0.0f, color);
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
	inputManager.update();
	checkInput();
}

void MenuScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(event.button.button);
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		}

		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			//presione click;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(inputManager.getMouseCoords());
			/*if (_buttonPlay->click(mouseCoords)) {
				_currentState = ScreenState::CHANGE_NEXT;
			}*/
			if (_buttonMembers->click(mouseCoords)) {
				_currentState = ScreenState::CHANGE_PREVIOUS;
			}
		}
	}
}

int MenuScreen::getNextScreen() const
{
	return SCREEN_INDEX_GAMEPLAY;
}

int MenuScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_MEMBERS;
}
