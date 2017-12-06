#pragma once
enum class ScreenState {
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};
class Game;
class IGameScreen
{
protected:
	int _screenIndex = 1;
	ScreenState _currentState = ScreenState::NONE;
	Game* _game = nullptr;
public:
	friend class ScreenList;
	virtual void checkInput() = 0;
	virtual void initSystem() = 0;
	virtual void build() = 0;
	virtual void destroy() = 0;
	virtual void onExit() = 0;
	virtual void onEntry() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void initGUI() = 0;
	virtual int getNextScreen() const = 0;
	virtual int getPreviousScreen() const = 0;
	ScreenState getState() const {
		return _currentState;
	}
	int getIndex() const {
		return _screenIndex;
	}

	void setRunning() {
		_currentState = ScreenState::RUNNING;
	}
	void setParent(Game* game) {
		_game = game;
	}
	
};


