#include "Game.h"
#include "PapuEngine.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include "Timing.h"
#include <iostream>

Game::Game()
{
	_screenList = 
			std::make_unique<ScreenList>(this);
}

bool Game::init() {
	Papu::init();
	SDL_GL_SetAttribute(
			SDL_GL_ACCELERATED_VISUAL, 1);
	initSystems();
	onInit();
	addScreens();
	_currentScreen = _screenList->getCurrent();
	_currentScreen->onEntry();
	_currentScreen->setRunning();
	return true;
}

void Game::draw() {
	glViewport(0, 0, _window.getScreenWidth(),
					_window.getScreenHeight());
	if (_currentScreen 
			&& _currentScreen->getState()
				== ScreenState::RUNNING) {
		_currentScreen->draw();
	}
}
bool Game::initSystems() {
	_window.create("Plataformer", 760, 500, 0);
	return true;
}

void Game::onSDLEvent(SDL_Event& evnt) {
	switch (evnt.type) {
	case SDL_QUIT:
		break;
	case SDL_MOUSEMOTION:
		_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
		break;
	case SDL_KEYDOWN:
		_inputManager.pressKey(evnt.key.keysym.sym);
		break;
	case SDL_KEYUP:
		_inputManager.releaseKey(evnt.key.keysym.sym);
		break;
	case SDL_MOUSEBUTTONDOWN:
		_inputManager.pressKey(evnt.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		_inputManager.releaseKey(evnt.button.button);
		break;
	}
}

void Game::run() {
	if (!init()) return;
	_isRunning = true;
	FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);

	while (_isRunning) {
		fpsLimiter.begin();
		_inputManager.update();
		update();
		draw();
		_window.swapBuffer();
		_fps = fpsLimiter.end();
		
	}
}

void Game::exit() {
	_currentScreen->onExit();
	if (_screenList) {
		_screenList->destroy();
		_screenList.reset();
	}
	_isRunning = false;
}

void Game::update() {
	if (_currentScreen) {
		switch (_currentScreen->getState())
		{
			case ScreenState::RUNNING:
				_currentScreen->update();
				break;
			case ScreenState::CHANGE_NEXT:
				_currentScreen->onExit();
				_currentScreen = 
							_screenList->moveNext();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::CHANGE_PREVIOUS:
				_currentScreen->onExit();
				_currentScreen =
					_screenList->movePrevious();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exit();
				break;
			default:
				break;
		}
		
	}
}


Game::~Game()
{
}

