#pragma once
#include "basic.h"
class Monster : public Creature{
public:
	Monster():Creature() {}
	Monster(string in_name, int val,int in_damage,int in_range,bool in_elite) :Creature(in_name, val,6),damage(in_damage),range(in_range),elite(in_elite){
	}
	Monster& operator=(const Monster& input) {
		this->name = input.name;
		this->life_value = input.life_value;
		this->card_amount = input.card_amount;
		this->card_total = input.card_total;
		this->code = input.code;
		this->position = input.position;
		this->card = new Card[card_amount];
		for (int i = 0;i < card_amount;i++) {
			this->card[i] = input.card[i];
		}
		return *this;
	}
	void switch_status(int num) {
		switch (num)
		{
		case 0:show = false;break;
		case 1:break;
		case 2: {
			elite = true;
			damage = elite_damage;
			life_value = elite_life_value;
			range = elite_range;
		}break;
		}
	}

	int damage;
	int range;//0����ԩ�
	bool elite = false; //�O(true)�_(false)���׭^
	bool show = true;//�O(true)�_(false)�X�{�b���W
	int elite_life_value=-1;//�׭^�Ǧ�q
	int elite_damage=-1;//�׭^�ǧ���
	int elite_range=-1;//�׭^�Ǯg�{
	
};