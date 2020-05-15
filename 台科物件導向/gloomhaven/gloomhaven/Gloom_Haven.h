#pragma once
//total:
#include<string>
#include<tuple>
class Character;
class Monster;
class Map;
class TXT;
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
	Character* player=nullptr;
	int character_amount;
	Monster* enemy=nullptr;
	int enemy_amount;
};

