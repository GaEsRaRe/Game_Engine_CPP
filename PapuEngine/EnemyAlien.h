#pragma once
#include "Player.h"
#include <random>
class EnemyAlien : public Player
{
private:
	float _elapsed;
	float _speed = 5;
	float score = 10;
	
	glm::vec2 _collider;
public:
	int _state = 1;
	EnemyAlien(float agent_width, float agent_height, glm::vec2 position,std::string texture,int type,int _uid);
	void update(float deltaTime);
	glm::vec2 get_collider();
	~EnemyAlien();
};

