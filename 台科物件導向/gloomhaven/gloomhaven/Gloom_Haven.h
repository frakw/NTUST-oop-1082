#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <map>
#include <set>
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
#include "Coord.h"
#include "basic.h"
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include "a_star_path.h"
#include "read_file.h"
#include "Input.h"
#include "enum.h"
//���ܿ�J�A���ѱ��N�S������
//#define prompt

#ifdef prompt
#define prompt_input(output) cout<< output <<endl
#else
#define prompt_input(output)
#endif

//cmd��J�A���ѱ��אּ�µ�����J
#define command_line

#define mygetline(cin,input)  if(cin.eof()){cin.clear();} getline(cin, input);
#define mydelete(ptr) do{if(ptr!=nullptr){delete[] ptr;ptr = nullptr;}}while(0)
#define mydelete_single(ptr) do{if(ptr!=nullptr){delete ptr;ptr = nullptr;}}while(0)
#define delete_2d(ptr,row) do{if(ptr!=nullptr){for(int __i=0;__i<row;__i++){delete[] ptr[__i];}delete[] ptr;ptr=nullptr;}}while(0)
#define self_assign_err_handle(input) do{if(this==&input)return;}while(0)
#define no_path_found -87
#define member_assign(a,b,member) (((a).(member)) = ((b).(member)))

using namespace std;
bool creature_order_compare(const Creature * const&a,const Creature * const&b);//�ͪ��P�ͪ������ʥ���A�i�ǤJ�Ǫ��Ψ���

#ifdef DEBUG
#define AUTOEXT
#else
#define AUTOEXT  extern
#endif
AUTOEXT  int debug_mode;
#undef AUTOEXT

struct Race{//�Ǫ�����
	string name;
	vector<Monster*> member;
	int card_number = -1;
	void choose_card();
	void round_end();
};

class Gloom_Haven {//�C���D��class
public:
	Gloom_Haven();
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input);//tuple�̧Ǭ���������}�C���Y���СA����ƶq�A�����Ǫ��}�C���Y���СA�Ǫ��ƶq�A�a�ϫ���
	~Gloom_Haven();
	void set(tuple<Character*, int, Monster*, int, Map*> input);
	
	void start();//�D�n�y�{���b�o��
	
	int character_remain();//����Ѿl��
	int monster_remain();//�Ǫ��Ѿl��
	int choose_remain();//�Ѿl�X�Ө��⥼��P�Ϊ���

	void add_to_group(Monster*);//�s�W�ͪ����Ш� �Ҧ��Ǫ�������vector
	int monster_race_amount(string);//�^�ǸӺ����Ǫ����W�Ѿl�ơA�����h�Ӧ^�Xdebug mode�d�P�s�����[1
	bool monster_race_in_discard(string,int);//�Ӻ����Ǫ���int�s���d�P�O�_�b��P���
private:
	Creature** all = nullptr;//�Ҧ�����P�Ǫ����бƧǫ�s��ϡA��l�ƮɡA������A�Ǫ�

	Map* map = nullptr;//�a�ϫ���

	Character* character = nullptr;//����}�C�Y����
	int character_amount=0;//����}�C�ƶq

	Monster* monster = nullptr;//�Ǫ��}�C�Y����
	int monster_amount = 0;//�Ǫ��}�C�ƶq

	vector<Race> all_group;//�Ҧ��Ǫ�������vector
};