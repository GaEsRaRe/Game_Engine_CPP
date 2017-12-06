#include "physics.h"
#include <iostream>

using namespace std;

Physics::Physics()
{
	//std::vector<CollisionBody> all_colliders = new std::vector<CollisionBody>();
}

Physics::~Physics()
{
}

void Physics::add_body(Player *Player, int a,int uid) {
	
	Player->id_group = a;
	Player->uid = uid;
	cout << Player->id_group << " " << Player->uid << endl;
	all_colliders.push_back(Player);
}

void Physics::run() {
	if (all_colliders.size() > 0) {
		//cout << all_colliders.size();
		for (size_t i = 0; i < all_colliders.size(); i++) {
			for (size_t j = 0; j < all_colliders.size();j++) {
				if (i != j) {
					if (abs(all_colliders.at(i)->collider.get_position().x - all_colliders.at(j)->collider.get_position().x) < (all_colliders.at(i)->collider.get_size().x + all_colliders.at(j)->collider.get_size().x)/2) {
						if (abs(all_colliders.at(i)->collider.get_position().y - all_colliders.at(j)->collider.get_position().y) < (all_colliders.at(i)->collider.get_size().y + all_colliders.at(j)->collider.get_size().y)/2) {
							cout << "something is colling " << all_colliders.at(i)->id_group << all_colliders.at(j)->id_group << endl;
						}
					}
				}
			}
		}
	}
	
}

bool Physics::is_colliding(int id, int id2) {
	if (all_colliders.size() > 0) {
		//cout << all_colliders.size();
		for (size_t i = 0; i < all_colliders.size(); i++) {
			for (size_t j = 0; j < all_colliders.size(); j++) {
				//cout << all_colliders.at(i)->id_group << endl;
				if (i != j && all_colliders.at(i)->id_group == id && all_colliders.at(j)->id_group == id2) {

					if (abs(all_colliders.at(i)->collider.get_position().x - all_colliders.at(j)->collider.get_position().x) < (all_colliders.at(i)->collider.get_size().x + all_colliders.at(j)->collider.get_size().x) * 2) {
						if (abs(all_colliders.at(i)->collider.get_position().y - all_colliders.at(j)->collider.get_position().y) < (all_colliders.at(i)->collider.get_size().y + all_colliders.at(j)->collider.get_size().y) * 2) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int Physics::get_collider(int body, int collider) {
	if (all_colliders.size() > 0) {
		//cout << all_colliders.size();
		for (size_t i = 0; i < all_colliders.size(); i++) {
			for (size_t j = 0; j < all_colliders.size(); j++) {
				//cout << all_colliders.at(j)->id_group << all_colliders.at(j)->uid << endl;
				if (i != j && all_colliders.at(i)->id_group == body && all_colliders.at(j)->id_group == collider) {
					if (abs(all_colliders.at(i)->collider.get_position().x - all_colliders.at(j)->collider.get_position().x) < (all_colliders.at(i)->collider.get_size().x + all_colliders.at(j)->collider.get_size().x) * 2) {
						if (abs(all_colliders.at(i)->collider.get_position().y - all_colliders.at(j)->collider.get_position().y) < (all_colliders.at(i)->collider.get_size().y + all_colliders.at(j)->collider.get_size().y) * 2) {
							//all_colliders.erase(all_colliders.begin() + j);
							//cout << all_colliders.at(j)->uid << endl;
							return all_colliders.at(j)->uid;
						}
					}
				}
			}
		}
	}
	return -1;
}



void Physics::delete_with_uid(int uid) {
	for (size_t i = 0; i < all_colliders.size(); i++) {
		if (all_colliders.at(i)->uid == uid) {
			all_colliders.erase(all_colliders.begin() + i);
		}
	}
}

void Physics::clear() {
	for (size_t i = 0; i < all_colliders.size(); i++) {
		if (all_colliders.at(i) == nullptr) {
			all_colliders.erase(all_colliders.begin() + i);
		}

	}

}
void Physics::debug() {
	std::cout << all_colliders.at(0)->collider.get_positionx() << endl;
}