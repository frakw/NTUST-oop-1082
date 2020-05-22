#pragma once
//class Gloom_Haven;
//class Creature;
//class Monster;
//class Character;
//class Map;
//class TXT;
//class Coord;
//class Card;
//class Skill;
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <memory.h>
#include <algorithm>
#include <conio.h>
#include "Coord.h"//���ᶶ�ǭn��
#include "basic.h"//���ᶶ�ǭn��
#include "Character.h"//���ᶶ�ǭn��
#include "Monster.h"//���ᶶ�ǭn��
#include "Map.h"//���ᶶ�ǭn��
#include "read_file.h"//���ᶶ�ǭn��

//���ܿ�J
#define prompt_input 

using namespace std;

//���O: �Ǫ��C���X�@�i�P�A����C���X�G�i�P�A��Ĥ@�i��ӱ���
//�����i��L��ê��
//�ݸѨM:�ӱ��ȱƧ�
//�ݰ�: discard��hand
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(bool mode);
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input, bool mode);
	~Gloom_Haven();
	void set(tuple<Character*, int, Monster*, int, Map*> input, bool mode);
	void start();//main process
	void stop();
	int character_remain();//����Ѿl��
	int monster_remain();//�Ǫ��Ѿl��
private:
	Creature** all = nullptr;//�Ҧ�����P�Ǫ��s���(��K�ӱ��ȱƧǥ�)�A������A�Ǫ�

	bool DEBUG_MODE = false;
	Map* map = nullptr;
	Character* character = nullptr;
	int character_amount=0;
	//int character_remain = 0;//����Ѿl��

	Monster* monster = nullptr;
	int monster_amount = 0;
	//int monster_remain =0;//�Ǫ��Ѿl��
};