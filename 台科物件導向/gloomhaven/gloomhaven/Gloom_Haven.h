#pragma once
//total:
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include "log.h"
#include "basic.h"
#include "read_file.h"
#include <tuple>
#include <utility>
using namespace std;
//���O: �Ǫ��C���X�@�i�P�A����C���X�G�i�P�A��@�i��ӱ���



class Gloom_Haven {
public:
	Gloom_Haven(){}
	Gloom_Haven(bool mode) :DEBUG_MODE(mode) {}
	Gloom_Haven(tuple<Character*, Monster*, Map*> input, bool mode);
	~Gloom_Haven() {
		
	}
	void seiting(tuple<Character*, Monster*, Map*> input, bool mode);
	void start();//main process
	void stop();
private:
	bool DEBUG_MODE = false;
	Map* map = nullptr;
	Character* player=nullptr;
	Monster* enemy=nullptr;
};

