#pragma once
#include <string>
using namespace std;
class Creature;
class Monster : public Creature{
public:
	Monster();
	Monster(string in_name, int val, int in_damage, int in_range, bool in_elite);
	Monster& operator=(const Monster& input);
	void switch_status(int num);
	void choose_card(bool);//bool��debug mode
	void print()override;//�Ƨǫ᪺�C�L
	void action()override;//���
	void attack();//����P�Ǫ���attck�U�ۤ��}
	int damage=0;
	int range=0;//0����ԩ�
	bool show = true;//�O(true)�_(false)�X�{�b���W
	bool show_in_room = false;//�O�_�b�ж���
	//Card use_card;//�Ӧ^�X�ϥΪ��d�A�w�ಾ��basic
	int debug_mode_card_number=0;//debug_mode�A�����d���s���A�q0�}�l�X
	//elite�t�C------------------------------------
	bool elite = false; //�O(true)�_(false)���׭^
	int elite_max_life_value=-1;//�׭^�ǳ̤j��q
	int elite_damage=-1;//�׭^�ǧ���
	int elite_range=-1;//�׭^�Ǯg�{
	//---------------------------------------------
	
};