#pragma once
#include"Colliders.h"
#include "Player.h"
#include<vector>

class Physics
{
public:
	Physics();
	~Physics();
	void add_body(Player *Player,int id, int uid);
	void debug();
	void run();
	bool is_colliding(int id, int id2);
	void clear();
	int temp; //to save any value
	int get_collider(int body, int collider);
	void delete_with_uid(int uid);
private:
	std::vector<Player*> all_colliders;
};

