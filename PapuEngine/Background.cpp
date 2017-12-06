#include "Background.h"
#include "ResourceManager.h"
#include <glm\glm.hpp>


Background::Background(std::string texture): _texture(texture)
{
	_textureID = ResourceManager::getTexture(_texture).id;
}

void Background::draw(SpriteBacth& spritebatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 255, 255);
	glm::vec4 destRect(0, 0, 800, 600);
	spritebatch.draw(destRect, uvRect, _textureID, 0.0f, color);
}


Background::~Background()
{
}
