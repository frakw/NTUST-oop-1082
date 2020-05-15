#pragma once
#include <string>
using namespace std;
class Creature;
class Monster : public Creature{
public:
	Monster();
	Monster(string in_name, int val, int in_damage, int in_range, bool in_elite);
	Monster& operator=(const Monster& input);
	void switch_status(int num);

	int damage=0;
	int range=0;//0����ԩ�
	bool elite = false; //�O(true)�_(false)���׭^
	bool show = true;//�O(true)�_(false)�X�{�b���W
	int elite_life_value=-1;//�׭^�Ǧ�q
	int elite_damage=-1;//�׭^�ǧ���
	int elite_range=-1;//�׭^�Ǯg�{
	
};