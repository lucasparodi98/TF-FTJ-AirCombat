#include "MemberScreen.h"
#include "ScreenIndices.h"


MemberScreen::MemberScreen(Window* window) :_window(window)
{

}

MemberScreen::~MemberScreen()
{
}

void MemberScreen::build()
{
	background = new Background("Textures/Fondos/Member_Avion.png");
	_buttonVolver = new Button("Textures/btn_jugar.png");
}

void MemberScreen::destroy()
{
	_buttonVolver = nullptr;
	background = nullptr;
}

void MemberScreen::onExit()
{
}

void MemberScreen::onEntry()
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
	spriteFont2 = new SpriteFont("Fonts/Fuente3.ttf", 25);
}

void MemberScreen::draw()
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
	_buttonVolver->draw(_spriteBatch, glm::vec4(-160, -150, 330, 100));
	char buffer[256];
	sprintf_s(buffer, "INTEGRANTES");
	Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-240, 150), glm::vec2(1), 0.0f, color);
	color.r = 180;
	sprintf_s(buffer, "Lucas Parodi Roman - U201611720");
	spriteFont2->draw(_spriteBatch, buffer, glm::vec2(-290, 100), glm::vec2(1), 0.0f, color);
	sprintf_s(buffer, "Nander Emanuel Melendez Huamanchumo - U201922331");
	spriteFont2->draw(_spriteBatch, buffer, glm::vec2(-290, 50), glm::vec2(1), 0.0f, color);
	sprintf_s(buffer, "Renato Clotario Castillo Rengifo - U201511892");
	spriteFont2->draw(_spriteBatch, buffer, glm::vec2(-290, 0), glm::vec2(1), 0.0f, color);
	sprintf_s(buffer, "Alex Daniel Juep Sifuentes - U201718083");
	spriteFont2->draw(_spriteBatch, buffer, glm::vec2(-290, -50), glm::vec2(1), 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void MemberScreen::update()
{
	draw();
	_camera.update();
	inputManager.update();
	checkInput();
}

void MemberScreen::checkInput()
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
			if (_buttonVolver->click(mouseCoords)) {
				_currentState = ScreenState::CHANGE_PREVIOUS;
			}
		}
	}
}

int MemberScreen::getNextScreen() const
{
	return SCREEN_INDEX_GAMEPLAY;
}

int MemberScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_GAMEPLAY;
}
