#pragma once
#include "Agent.h"
#include "InputManager.h"
#include "timer.h"


class Player :public Agent
{
private:
	InputManager* _inputManager;
	glm::vec2 _collider;
	
	Timer jump_timer;
	
	Timer falling_timer;
	glm::vec2 *pposition;
public:
	bool is_jumping = false;
	bool is_falling = false;
	bool is_grounded = false;
	int id_group;
	int _state = 0;
	int score = 10;
	Player(float agent_width, 
		float agent_height, 
		glm::vec2 position,
		std::string texture);
	Player(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture, 
		InputManager* inputManager);
	void update(float deltaTime);
	void movement();
	glm::vec2 get_collider();
	~Player();
};

