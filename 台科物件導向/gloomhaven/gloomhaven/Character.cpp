#include "Gloom_Haven.h"

Character::Character() :Creature() {}
Character::Character(string in_name, int val, int in_card_amount) :Creature(in_name, val, in_card_amount) {
}
Character& Character::operator=(const Character& input) {
	this->name = input.name;
	this->life_value = input.life_value;
	max_life_value = input.max_life_value;
	this->card_amount = input.card_amount;
	this->card_total = input.card_total;
	this->code = input.code;
	this->position = input.position;
	this->use_card[0] = input.use_card[0];
	this->use_card[1] = input.use_card[1];
	this->sleep = input.sleep;
	this->TmpAgility = input.TmpAgility;

	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		this->card[i] = input.card[i];
	}
	return *this;
}

bool Character::choose_card() {
	if (life_value < 0) {
		return true;
	}
	string card_number1;//�]���i���Jcheck�A�U�ϥ�string
	int  card_number2;
	cin >> card_number1;
	if (card_number1 == "check") {
		//��T
		this->check_card();
		return false;
	}
	else if (card_number1 == "-1") {
		//����
		sleep = true;
//#ifdef prompt_input
//		cout << "�п�J�n�����d�P:" << endl;
//#endif
		//cin >> card_number2;
		//find_card(card_number2).available = false;
		//this->heal(2);
		//TmpAgility = 99;
		//this->discard_to_hand();//��P��Ҧ��P���^��P
	}
	else {
		cin >> card_number2;
		sleep = false;//�n�O�o***
		use_card[0] = find_card(atoi(card_number1.c_str()));
		use_card[1] = find_card(card_number2);
		//err handle �Y��J�b��P��ΥH�����P not finished
		TmpAgility = use_card[0].agility;//�Ĥ@�i�P�@���ӱ���
	}
	return true;
}