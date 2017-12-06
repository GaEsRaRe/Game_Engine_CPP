#include "Button.h"
#include "ResourceManager.h"
#include <glm\glm.hpp>
#include <iostream>

Button::Button(std::string texture):_texture(texture)
{
	_position = glm::vec2(300, 100);
}

bool Button::clicked(glm::vec2 position) {
	return  ((position.x > _position.x -190)
				&& (position.x < _position.x + 190));
}

void Button::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture(_texture).id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 0, 255);
	
	glm::vec4 destRect(_position.x, _position.y, 190, 49);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Button::~Button()
{
}
