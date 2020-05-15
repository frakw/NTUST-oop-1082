#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <utility>
#include "Coord.h"//���ᶶ�ǭn��
#include "basic.h"//���ᶶ�ǭn��
#include "Character.h"//���ᶶ�ǭn��
#include "Monster.h"//���ᶶ�ǭn��
#include "Map.h"//���ᶶ�ǭn��
#include "read_file.h"//���ᶶ�ǭn��

using namespace std;

//���O: �Ǫ��C���X�@�i�P�A����C���X�G�i�P�A��@�i��ӱ���
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(bool mode);
	Gloom_Haven(tuple<Character*, Monster*, Map*> input, bool mode);
	~Gloom_Haven();
	void seiting(tuple<Character*, Monster*, Map*> input, bool mode);
	void start();//main process
	void stop();
private:
	bool DEBUG_MODE = false;
	Map* map = nullptr;
	Character* player = nullptr;
	int character_amount;
	Monster* enemy = nullptr;
	int enemy_amount;
};
