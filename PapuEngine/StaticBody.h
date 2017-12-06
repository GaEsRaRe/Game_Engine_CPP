#pragma once
#include "Player.h"
#include "Colliders.h"

class StaticBody :public Player
{
private:
	glm::vec2 _collider;
	bool is_jumping = false;
	glm::vec2 *pposition;
public:
	bool is_falling = false;
	int id_group = 3;
	int uid = 5000;
	int _state = 0;
	int score = 10;
	StaticBody(float agent_width, float agent_height, glm::vec2 position, std::string texture, int type, int _uid);
	void update(float deltaTime);
	glm::vec2 get_collider();
	~StaticBody();
};


