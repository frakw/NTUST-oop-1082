#pragma once
#include "basic.h"

class Monster : public Creature{
	Monster(string in_name, int val,int in_damage,int in_range,bool in_elite) :Creature(in_name, val,6),damage(in_damage),range(in_range),elite(in_elite){
	}
	bool elite = false; //�O(true)�_(false)���׭^
	int damage;
	int range;//0����ԩ�
};