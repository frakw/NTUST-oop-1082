#pragma once
#include <string>
#include <map>
using namespace std;
class Creature;
class Skill;
class Monster : public Creature{
public:
	Monster();
	virtual ~Monster();
	Monster& operator=(const Monster& input);
	void switch_status(int num);
	virtual void print() override;//�Ƨǫ᪺�C�L
	virtual void action() override;//���
	virtual void round_end() override;//�Ӧ^�X�����᪺����(���]�ƭ�)
	void attack(const Skill const&);//����P�Ǫ���attck�U�ۤ��}
	int damage=0;
	int range=0;//0����ԩ�
	bool show = true;//�O(true)�_(false)�X�{�b���W
	bool show_in_room = false;//�O�_�b�ж���
	int card_number=0;//debug_mode�A�����d���s���A�q0�}�l�X
	//elite�t�C------------------------------------
	bool elite = false; //�O(true)�_(false)���׭^
	int elite_max_life_value=-1;//�׭^�ǳ̤j��q
	int elite_damage=-1;//�׭^�ǧ���
	int elite_range=-1;//�׭^�Ǯg�{
	//---------------------------------------------
	bool finished_show = false;//�өǪ����رڬO�_�w�����ӱ��ȱƧǿ�X
};