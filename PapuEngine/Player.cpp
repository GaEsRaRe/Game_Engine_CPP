#include "Player.h"
#include <SDL\SDL.h>
#include <iostream>



using namespace std;

glm::vec2 direction = glm::vec2(9.0f, 0);
glm::vec2 arriba = glm::vec2(0.0f, 5);



Player::Player(float agent_width, float agent_height, glm::vec2 position,
			std::string texture):
				Agent(agent_width,agent_height, position,texture)
{
	_collider.x = agent_width;
	_collider.y = agent_height;
	collider.set_size(_collider.x, _collider.y);
	id_group = 1; //Player = 1
	uid = 1; //player = 1
	//collider.set_position(pposition);
}

Player::Player(float agent_width, float agent_height, glm::vec2 position,
	std::string texture, InputManager* inputManager) :
	Agent(agent_width, agent_height, position, texture)
{
	_inputManager = inputManager;
	id_group = 1;
	uid = 1;
}


void Player::movement() {
	//cout << collider.get_positionx();
	if (_inputManager->isKeyDown(SDLK_a)) {
		move_to(direction * -1.0f);
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		move_to(direction);
	}
	if (_inputManager->isKeyDown(SDLK_SPACE)){
		if (!is_jumping) {
			//cout << "saltar";
			jump_timer.set_duration(0.4f);
			jump_timer.start();
			is_jumping = true;
		}	
	}
	if (is_jumping) {
		move_to(arriba);

		jump_timer.run();
		if (jump_timer.is_finished()) {
			is_jumping = false;
			is_falling = true;
		}

	}
	if (is_falling) {
		move_to(arriba * -1.0f);
	}
}

void Player::update(float deltaTime) {
	collider.set_position(getPosition());
	
	movement();
	if (_inputManager->isKeyDown(SDLK_c)) {
		_state = 1;
	} else {
		_state = 0;
	}
	
}


Player::~Player()
{
}

glm::vec2 Player::get_collider() {
	return _collider;
}
