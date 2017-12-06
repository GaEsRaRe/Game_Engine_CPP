#include "SideEnemy.h"
#include <random>


SideEnemy::SideEnemy(float agent_width, float agent_height, glm::vec2 position, std::string texture, int type, int _uid)
	:Player(agent_width, agent_height, position, texture), _elapsed(0)
{
	_state = type;
	_collider.x = agent_width / 2;
	_collider.y = agent_height / 2;
	collider.set_size(_collider.x, _collider.y);
	id_group = 2;
	uid = _uid;



}

void SideEnemy::update(float deltaTime) {
	collider.set_position(getPosition());
	_elapsed += deltaTime;
	move_to(glm::vec2(5, 0));

}
glm::vec2 SideEnemy::get_collider() {
	return _collider;
}

SideEnemy::~SideEnemy()
{
}

