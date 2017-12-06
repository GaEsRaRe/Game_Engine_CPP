#pragma once
#include "SpriteBacth.h"
#include <glm\glm.hpp>
#include "GLTexture.h"
#include <string>
class Button
{
private:
	std::string _texture;
	glm::vec2 _position;
public:
	void draw(SpriteBacth& spritebatch);
	Button(std::string texture);
	~Button();
	bool clicked(glm::vec2 position);
};

