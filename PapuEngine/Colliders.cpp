#include "Colliders.h"

CollisionBody::CollisionBody()
{
	size.x = 0;
	size.y = 0;
}
CollisionBody::~CollisionBody()
{
}
void CollisionBody::set_size(float x, float y) {
	size.x = x;
	size.y = y;
}
void CollisionBody::set_position(glm::vec2 _position) {
	position.x = _position.x;
	position.y = _position.y;

}
float CollisionBody::get_positionx() {
	return position.x;
}

glm::vec2 CollisionBody::get_position() {
	return position;
}
glm::vec2 CollisionBody::get_size() {
	return size;
}

