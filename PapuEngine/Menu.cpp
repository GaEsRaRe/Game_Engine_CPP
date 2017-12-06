#include "Menu.h"
#include "ScreenIndices.h"
#include "Game.h"
#include <iostream>

Menu::Menu(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void Menu::initGUI() {

}

void Menu::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

Menu::~Menu()
{
}

void Menu::build()
{
}

void Menu::destroy() {
	delete _background;
	delete _button;
}

void Menu::onExit() {

}

void Menu::onEntry() {
	initSystem();
	_hudBatch.init();
	_camera2D.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(_window->getScreenWidth() / 2.0f, _window->getScreenHeight() / 2.0f));
	_spriteBacth.init();
	_background = new Background("assets/fondos/menu.png");
	_button = new Button("Textures/naves/menu_button.png");
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));

	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
}

void Menu::update() {
	_camera2D.update();
	_hudCamera.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (_button->clicked(_game->_inputManager.getMouseCoords()) && !btnGameClicked) {
			btnGameClicked = true;
			std::cout << "Button clicked" << std::endl;
			_currentState = ScreenState::CHANGE_NEXT;

		}
	}
	checkInput();
}

void Menu::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	_background->draw(_spriteBacth);
	_button->draw(_spriteBacth);

	_spriteBacth.end();
	_spriteBacth.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void  Menu::drawHUD() {
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];

	_hudBatch.begin();
	sprintf_s(buffer, "Alumno: Gabriel Ramirez Reategui");
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(250, 250),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	sprintf_s(buffer, "Trabajo Final de Fundamentos de T. de Juegos");
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(75, 200),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudBatch.end();
	_hudBatch.renderBatch();

}
int Menu::getNextScreen()const {
	return SCREEN_INDEX_GAMEPLAY;
}

int Menu::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void Menu::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}


