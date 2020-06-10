#pragma once

class Skill;
class Character;
class Monster;
class Map;
class Card;
using namespace std;


class TXT {//Ū�ɳB�zclass
public:
	TXT() {}
	~TXT();
	void input_character_data();
	void read_character(string filename);//�ʺA�t�m�����d�P��A�s�Jdatabase
	void read_monster(string filename);//�ʺA�t�m�����d�P��A�s�Jdatabase
	void read_map(string filename);
	tuple<Character*, int, Monster*, int, Map*> return_tuple();//�ʺA�t�m�O����A�M��ƻsdatabase���e��A�Ǩ�gloom_haven����A����O����浹gloom_haven   (PPT 40��)
private:
	Character* character_db = nullptr;//database�A�����Ʈw
	int chr_db_amount = 0;//database total�A�����Ʈw�ƶq
	Monster* monster_db = nullptr;//database�A�Ǫ���Ʈw
	int mon_db_amount = 0;//database total�A�Ǫ���Ʈw�ƶq

	Character* character_output = nullptr;//�̾ڿ�J�q��Ʈw�ƻs������X��gloomhaven
	int character_amount = 0;//�����X��gloomhaven���ƶq
	Monster* monster_output = nullptr;//�̾�txt�q��Ʈw�ƻs�Ǫ����X��gloomhaven
	int monster_amount = 0;//�Ǫ���X��gloomhaven���ƶq
	Map* map = nullptr;

};