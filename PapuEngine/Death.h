#pragma once
#include "IGameScreen.h"
#include "Window.h"
#include "GLS_Program.h"
#include "SpriteFont.h"
#include "Background.h"
#include "Camera2D.h"
#include "Button.h"
#include "SpriteBacth.h"
#include "InputManager.h"
#include "timer.h"

class Death : public IGameScreen
{
private:
	Window* _window = nullptr;
	bool btnGameClicked;
	Timer reboot;
	GLS_Program _program;
	SpriteBacth _spriteBacth;
	Camera2D _camera2D;
	Background* _background;
	Button* _button;
	Camera2D _hudCamera;
	SpriteBacth _hudBatch;
	SpriteFont* _spriteFont;

	void drawHUD();

public:
	Death(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;

	virtual void initGUI()override;
	virtual void draw()override;
	virtual void update()override;
	virtual void initSystem() override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	~Death();
};

