#pragma once
#include <algorithm>
#include "Game.h"
#include "GamePlayScreen.h"
#include "Menu.h"
#include "Death.h"

class App : public Game
{
public:
	App();
	~App();
	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;
private:
	std::unique_ptr<Menu> _menu = nullptr;
	std::unique_ptr<GamePlayScreen> _gamePlayScreen = nullptr;
	std::unique_ptr<Death> _death = nullptr;
};

