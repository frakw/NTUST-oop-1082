#pragma once
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
#include <regex>
#include "Coord.h"//���ᶶ�ǭn��
#include "basic.h"//���ᶶ�ǭn��
#include "Character.h"//���ᶶ�ǭn��
#include "Monster.h"//���ᶶ�ǭn��
#include "Map.h"//���ᶶ�ǭn��
#include "read_file.h"//���ᶶ�ǭn��
#include "Input.h"
//���ܿ�J
#define prompt_input 

using namespace std;

//���O: �Ǫ��C���X�@�i�P�A����C���X�G�i�P�A��Ĥ@�i��ӱ���
//�����i��L��ê��
//�ݸѨM:�ӱ��ȱƧ�
//�ݰ�: discard��hand,�ĥ�macro coord_in���ɥiŪ��, regex ,choose_card��virtual 
//�ĥ�nullcoord �P == coord creature die funtion
//macro�w�A�����޲z�C����X�T��
//cout�Ptxt�ɦP�ɿ�X
//input output �]�˦�class�i���N����J�ο�X�A�]�i�h�ӿ�X
//���ܿ�J�T��
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input, bool mode);//tuple�̧Ǭ���������}�C���Y���СA����ƶq�A�����Ǫ��}�C���Y���СA�Ǫ��ƶq�A�a�ϫ���
	~Gloom_Haven();
	void set(tuple<Character*, int, Monster*, int, Map*> input, bool mode);
	
	void start();//�D�n�y�{���b�o��
	
	int character_remain();//����Ѿl��
	int monster_remain();//�Ǫ��Ѿl��
	int choose_remain();//�Ѿl�X�Ө��⥼��P�Ϊ���
private:
	Creature** all = nullptr;//�Ҧ�����P�Ǫ��Ƨǫ�s��ϡA��l�ƮɡA������A�Ǫ�

	bool DEBUG_MODE = false;
	Map* map = nullptr;

	Character* character = nullptr;
	int character_amount=0;

	Monster* monster = nullptr;
	int monster_amount = 0;
};