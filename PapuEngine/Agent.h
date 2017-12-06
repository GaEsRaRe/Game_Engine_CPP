#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "Colliders.h"

class Zombie;
class Human;

/*const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;*/

class Agent
{
protected:

	glm::vec2 _position;
	float _agent_width;
	float _agent_height;
	int _texture_id;
	float _agent_radius;
	std::string _texturePath;
	float _speed;
	ColorRGBA color;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition,float x, float y );
	void collideWithTile(glm::vec2 tilePos);
	void move_to(glm::vec2 direction);

public:
	int id_group;
	int uid;
	CollisionBody collider;
	Agent(float agent_width,float agent_height,glm::vec2 position, std::string texturePath);
	glm::vec2 getPosition()const { return _position; };
	virtual void update(float deltaTime) = 0;
	void draw(SpriteBacth& spritebatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

