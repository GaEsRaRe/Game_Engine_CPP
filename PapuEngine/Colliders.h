#pragma once
#include <glm\glm.hpp>

class CollisionBody
{
public:
	CollisionBody();
	~CollisionBody();
	glm::vec2 _collider;
	void set_size(float x, float y);
	void set_position(glm::vec2 _position);
	float get_positionx();
	glm::vec2 get_position();
	glm::vec2 get_size();
private:
	glm::vec2 size;
	glm::vec2 position;
};

