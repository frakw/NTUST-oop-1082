#pragma once

class Skill;
class Character;
class Monster;
class Map;
class Card;
using namespace std;


class TXT {
public:
	TXT() {}
	~TXT();
	void input_character_data();
	void read_character(string filename);//�ʺA�t�m�����d�P��A�s�Jdatabase
	void read_monster(string filename);//�ʺA�t�m�����d�P��A�s�Jdatabase
	void read_map(string filename);
	tuple<Character*, int, Monster*, int, Map*> return_tuple();//�ʺA�t�m�O����A�M��ƻsdatabase���e��A�Ǩ�gloom_haven����A����O����浹gloom_haven   (PPT 40��)
private:
	Character* character_db = nullptr;//database
	int chr_db_amount = 0;//database total
	Monster* monster_db = nullptr;//database
	int mon_db_amount = 0;//database total

	Character* character_output = nullptr;//character output
	int character_amount = 0;
	Monster* monster_output = nullptr;//monster output
	int monster_amount = 0;
	Map* map = nullptr;

};