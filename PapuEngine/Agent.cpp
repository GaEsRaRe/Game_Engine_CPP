#include "Agent.h"
#include "ResourceManager.h"
#include <algorithm>

Agent::Agent(float agent_width, float agent_height, glm::vec2 position, std::string texture):
	_agent_width(agent_width), _agent_height(agent_height), 
	_agent_radius(agent_width/2),
	_position(position),
	_texturePath(texture)
{
	collider.set_position(getPosition());
}


void Agent::draw(SpriteBacth& spritebatch) {
	_texture_id = ResourceManager::getTexture(_texturePath).id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 255, 255);
	glm::vec4 destRect(_position.x, _position.y, _agent_width, _agent_height);
	spritebatch.draw(destRect, uvRect, _texture_id, 0.0f, color);

}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePosition;
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x + _agent_width, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y + _agent_width);
	checkTilePosition(levelData, collideTilePosition, _position.x + _agent_width, _position.y + _agent_width);

	if (collideTilePosition.size() == 0) return false;

	for (size_t i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}

	return true;
}

bool Agent::collideWithAgent(Agent* agent) {

	const float MIN_DISTANCE = _agent_radius * 2.0f;

	glm::vec2 centerPosA = _position + glm::vec2(_agent_radius);

	glm::vec2 centerPosB = 
				agent->getPosition() + glm::vec2(_agent_radius);

	glm::vec2 distVec = centerPosA - centerPosB;
	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec =
			glm::normalize(distVec) * collisionDepth;
		
		_position += collisionDepth / 2.0f;
		agent->_position -= collisionDepth / 2.0f;
		return true;
	}

	return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePosition, float x, float y) {
	/*glm::vec2 cornesPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	if (cornesPos.x < 0 || cornesPos.x >= levelData[0].size() || cornesPos.y < 0 || cornesPos.y >= levelData.size()) {
		return;
	}
	if (levelData[cornesPos.y][cornesPos.x] != '.') {
		collideTilePosition.push_back(cornesPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}*/
}

void Agent::collideWithTile(glm::vec2 tilePos) {

	/*const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosition - tilePos;
	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);

	if (xdepth > 0 || ydepth > 0) {
		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f)) {
			if (distVec.x < 0) {
				_position.x -= xdepth;
			}
			else {
				_position.x += xdepth;
			}
		}
		else {
			if (distVec.y < 0) {
				_position.y -= ydepth;
			}
			else {
				_position.y += ydepth;
			}
		}
	}*/
}



void Agent::move_to(glm::vec2 direction) {
	_position.x = _position.x + direction.x;
	_position.y = _position.y + direction.y;

}
Agent::~Agent()
{
}