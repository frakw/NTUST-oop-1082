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
#include <iomanip>
#include "Coord.h"//���ᶶ�ǭn��
#include "basic.h"//���ᶶ�ǭn��
#include "Character.h"//���ᶶ�ǭn��
#include "Monster.h"//���ᶶ�ǭn��
#include "Map.h"//���ᶶ�ǭn��
#include "a_star_path.h"
#include "read_file.h"//���ᶶ�ǭn��
#include "Input.h"
//���ܿ�J�A���ѱ��N�S������
//#define prompt

#ifdef prompt
#define prompt_input(output) cout<< output <<endl
#else
#define prompt_input(output)
#endif

#define mygetline(cin,input)  if(cin.eof()){cin.clear();} getline(cin, input);
#define mydelete(ptr) do{if(ptr!=nullptr){delete[] ptr;ptr = nullptr;}}while(0)
#define mydelete_single(ptr) do{if(ptr!=nullptr){delete ptr;ptr = nullptr;}}while(0)
#define delete_2d(ptr,row) do{if(ptr!=nullptr){for(int __i=0;__i<row;__i++){delete[] ptr[__i];}delete[] ptr;ptr=nullptr;}}while(0)
#define self_assign_err_handle(input) do{if(this==&input)return;}while(0)
using namespace std;

//�ݰ�:�ĥ�macro coord_in���ɥiŪ��, regex
//�ĥ�nullcoord �P == coord creature die funtion
//macro�w�A�����޲z�C����X�T��
//cout�Ptxt�ɦP�ɿ�X
//input output �]�˦�class�i���N����J�ο�X�A�]�i�h�ӿ�X
//���ܿ�J�T��

//��ƫʸˡAself assign�A����
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
	Creature** all = nullptr;//�Ҧ�����P�Ǫ����бƧǫ�s��ϡA��l�ƮɡA������A�Ǫ�

	bool DEBUG_MODE = false;
	Map* map = nullptr;

	Character* character = nullptr;
	int character_amount=0;

	Monster* monster = nullptr;
	int monster_amount = 0;
};