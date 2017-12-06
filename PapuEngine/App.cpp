#include "App.h"
#include "ScreenList.h"


using namespace std;

App::App()
{
}


void App::onInit() {

}


void App::addScreens() {
	_gamePlayScreen =
		make_unique<GamePlayScreen>(&_window);

	_menu = 
		make_unique<Menu>(&_window);
	_death =
		make_unique<Death>(&_window);

	_screenList->addScreen(_menu.get());
	_screenList->addScreen(_gamePlayScreen.get());
	_screenList->addScreen(_death.get());
	_screenList->setScreen(
		_menu->getIndex());
}

void App::onExit() {
}


App::~App()
{
}
