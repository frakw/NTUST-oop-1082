#pragma once
using namespace std;
class Creature;
class Map;
class Character : public Creature {
public:
	Character();
	Character(string in_name, int val, int in_card_amount);
	Character& operator=(const Character& input);
	void choose_card(string);//���2�i�d�Ϊ����check�Abool�^�ǬO�_��ܦ��\�Astring�ǤJ"0 3"
	void print() override;//�Ƨǫ᪺�C�L
	void action(bool) override;//��ʡAbool�S�@��(�t�X�Ǫ�����)
	void round_end(bool)override;//�Ӧ^�X�����᪺����(���]�ƭ�)
	void run_skill(Skill);//����ޯ�
	void attack(Skill);//����P�Ǫ���attck�U�ۤ��}
	//Card use_card[2];//�ӽ���ܪ�2�i�d�A�w�ಾ��basic
	bool sleep = false;//�O�_����
	bool finished_choose = false;//�Ӧ^�X�O�_������P�ο�ܪ���
};