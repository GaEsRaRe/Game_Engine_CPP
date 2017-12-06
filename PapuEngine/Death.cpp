#include "Death.h"
#include "ScreenIndices.h"
#include "Game.h"
#include <iostream>



Death::Death(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_DEATH;
}

void Death::initGUI() {

}

void Death::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

Death::~Death()
{
}

void Death::build()
{
}

void Death::destroy() {
	delete _background;
}

void Death::onExit() {

}

void Death::onEntry() {
	initSystem();
	reboot.set_duration(5.0f);
	
	_hudBatch.init();
	_camera2D.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(_window->getScreenWidth() / 2.0f, _window->getScreenHeight() / 2.0f));
	_spriteBacth.init();
	_background = new Background("assets/fondos/gam-over.png");
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));

	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	reboot.start();
}

void Death::update() {
	_camera2D.update();
	_hudCamera.update();
	reboot.run();
	cout << reboot.is_finished() << endl;
	if (reboot.is_finished()) {
		cout << "Juego terminado";
	}
	

}

void Death::draw() {
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
	

	_spriteBacth.end();
	_spriteBacth.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void  Death::drawHUD() {
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];

	_hudBatch.begin();
	sprintf_s(buffer, "GAME OVER");
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(250, 250),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	sprintf_s(buffer, "GG WP");
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(250, 200),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudBatch.end();
	_hudBatch.renderBatch();

}
int Death::getNextScreen()const {
	return SCREEN_INDEX_GAMEPLAY;
}

int Death::getPreviousScreen() const {
	return SCREEN_INDEX_GAMEPLAY;
}

void Death::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}


