#pragma once
using namespace std;
class Creature;
class Character : public Creature {
public:
	Character();
	Character(string in_name, int val, int in_card_amount);
	Character& operator=(const Character& input);
	bool choose_card();//���2�i�d�Ϊ����check�Abool�^�ǬO�_��ܦ��\
	Card use_card[2];//�ӽ���ܪ�2�i�d
	bool sleep = false;//�O�_����
};