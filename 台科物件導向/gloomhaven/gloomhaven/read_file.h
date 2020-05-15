#pragma once
#include <string>
#include <iostream>
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include <vector>
#include <string>
#include "basic.h"
using namespace std;


class TXT {
public:
	TXT() {}
	TXT(string in_filename) :filename(in_filename){}
	~TXT() {//�P����Ʈw
		if (character != nullptr) {
			delete[] character;
		}
		if (monster != nullptr) {
			delete[] monster;
		}
	}
	void set_filename(string in) {
		filename = in;
	}
	void read_character();//�ʺA�t�m�����d�P��A�s�Jdatabase
	bool check_character();
	void read_monster();//�ʺA�t�m�����d�P��A�s�Jdatabase
	bool check_monster();
	Map* read_map();
	bool check_map();
	tuple<Character*, Monster*, Map*> return_tuple();//�ʺA�t�m�O����A�M��ƻsdatabase���e��A�Ǩ�gloom_haven����A����O����浹gloom_haven   (PPT 40��)
private:
	Character* character = nullptr;//database
	int total_chr;
	Monster* monster = nullptr;//database
	Monster* monput = nullptr;//monster output
	int total_mon;
	string filename;
	int database_total=0;
};