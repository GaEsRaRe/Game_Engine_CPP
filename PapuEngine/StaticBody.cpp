#include "StaticBody.h"

#include <SDL\SDL.h>
#include <iostream>



using namespace std;




StaticBody::StaticBody(float agent_width, float agent_height, glm::vec2 position, std::string texture, int type, int _uid)
	:Player(agent_width, agent_height, position, texture)
{
	_state = type;
	_collider.x = agent_width/2.0f;
	_collider.y = agent_height;
	collider.set_position(getPosition());
	collider.set_size(_collider.x, _collider.y);
	id_group = 3;
	uid = _uid;

}




void StaticBody::update(float deltaTime) {
	collider.set_position(getPosition());
	id_group = 3; //Player = 1
	uid = 5000; //player = 1
}


StaticBody::~StaticBody()
{
}

glm::vec2 StaticBody::get_collider() {
	return _collider;
}
