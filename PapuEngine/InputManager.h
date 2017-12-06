#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

class InputManager
{
private:
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previusKeyMap;
	glm::vec2 _mouseCoords;
	bool wasKeyDown(unsigned int);

public:
	InputManager();
	~InputManager();
	glm::vec2 getMouseCoords() const {
		return _mouseCoords;
	}
	void update();
	void setMouseCoords(float x, float y);
	void pressKey(unsigned int keyCode);
	void releaseKey(unsigned int keyCode);
	//is if held down
	bool isKeyDown(unsigned int keyCode);
	//just pressed
	bool isKeyPressed(unsigned int keyCode);
};

