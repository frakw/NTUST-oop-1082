#pragma once
using namespace std;
class Creature;
class Map;
class Character : public Creature {
public:
	Character();
	Character(string in_name, int val, int in_card_amount);
	Character& operator=(const Character& input);
	bool choose_card();//���2�i�d�Ϊ����check�Abool�^�ǬO�_��ܦ��\
	void print() override;//�Ƨǫ᪺�C�L
	void action() override;//���
	void run_skill(Skill);//����ޯ�
	void attack();//����P�Ǫ���attck�U�ۤ��}
	//Card use_card[2];//�ӽ���ܪ�2�i�d�A�w�ಾ��basic
	bool sleep = false;//�O�_����
};