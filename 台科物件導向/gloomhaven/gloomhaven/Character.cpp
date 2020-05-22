#include "Gloom_Haven.h"

Character::Character() :Creature() {
}
Character::Character(string in_name, int val, int in_card_amount) :Creature(in_name, val, in_card_amount) {
}
Character& Character::operator=(const Character& input) {
	this->name = input.name;
	this->life_value = input.life_value;
	this->max_life_value = input.max_life_value;
	this->card_amount = input.card_amount;
	this->card_total = input.card_total;
	this->code = input.code;
	this->position = input.position;
	this->use_card[0] = input.use_card[0];
	this->use_card[1] = input.use_card[1];
	this->sleep = input.sleep;
	//this->TmpAgility = input.TmpAgility;
	this->TmpShield = input.TmpShield;
	this->team_num = input.team_num;
	this->map = input.map;

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
		use_card[0].agility = 99;
		use_card[1].agility = 99;
//#ifdef prompt_input
//		cout << "�п�J�n�����d�P:" << endl;
//#endif
		//cin >> card_number2;//    ��ʶ��q�A��
		//find_card(card_number2).available = false;//    ��ʶ��q�A��
		//this->heal(2);//    ��ʶ��q�A��
		//TmpAgility = 99;//    ��ʶ��q�A��
		//this->discard_to_hand();//��P��Ҧ��P���^��P //    ��ʶ��q�A��
	}
	else {
		cin >> card_number2;
		sleep = false;//�n�O�o***
		use_card[0] = find_card(atoi(card_number1.c_str()));
		use_card[1] = find_card(card_number2);
		//err handle �Y��J�b��P��ΥH�����P not finished
		//TmpAgility = use_card[0].agility;//�Ĥ@�i�P�@���ӱ���
	}
	return true;
}

void Character::print(){
	if (life_value > 0) {//���⤣�P�_�O�_�X�{
		cout << code << ' ' << use_card[0].agility << ' ' << use_card[0].number << ' ' << use_card[1].number << endl;
	}
}

void Character::action(bool) {
	if (life_value <= 0) {
		return;
	}
	if (sleep) {//����
#ifdef prompt_input
		cout << "�п�J�n�����d�P:" << endl;
#endif
		int remove_card_number;
		cin >> remove_card_number;
		find_card(remove_card_number).available = false;
		this->heal(2);
		this->discard_to_hand();//��P��Ҧ��P���^��P
		return;
	}
	cout << code << "'s turn: card " << use_card[0].number << ' ' << use_card[1].number << endl;
	bool card_first_index;
	string number_up_down;
	cin >> number_up_down;
	card_first_index = use_card[0].number == (number_up_down[0] - '0')?false:true;
	if (number_up_down[1] == 'u') {//�W�b��
		for (int i = 0;i < card[card_first_index].skill_up_amount;i++) {//�Ĥ@�i
			run_skill(card[card_first_index].skill_up[i]);
		}
		for (int i = 0;i < card[!card_first_index].skill_down_amount;i++) {//�ĤG�i
			run_skill(card[!card_first_index].skill_down[i]);
		}
	}
	else {//�U�b��
		for (int i = 0;i < card[card_first_index].skill_down_amount;i++) {//�Ĥ@�i
			run_skill(card[card_first_index].skill_down[i]);
		}
		for (int i = 0;i < card[!card_first_index].skill_up_amount;i++) {//�ĤG�i
			run_skill(card[!card_first_index].skill_up[i]);
		}
	}
	this->round_end();
}

void Character::run_skill(Skill skill) {
	switch (skill.type) {
	case 0: {//move
		string step;
		cin >> step;
		this->move(step, skill.value);
	}break;
	case 1: {//attack
		this->attack(skill);
	}break;
	case 2: {//heal
		this->heal(skill.value);
	}break;
	case 3: {//shield
		this->shield(skill.value);
	}break;
	}
}

void Character::attack(Skill skill) {
	char code;
	int index =-1;
	cin >> code;
	if (code == '0') {
		return;
	}
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster[i].code == code) {
			index = i;
			break;
		}
	}
	if (index == -1) {//bad index
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
	if (map->a_star_path_step(this,map->monster + index) <= skill.value//�ˬd�g�{
		&& map->in_vision(position, map->monster[index].position)){//�ˬd����
		map->monster[index].be_attack(skill.value);
	}
	else {
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
	map->reset_in_range();
}

void Character::round_end() {//�Ӧ^�X�����᪺����(���]�ƭ�)
	sleep = false;
	TmpShield = 0;
	find_card(use_card[0].number).discard = true;
	find_card(use_card[1].number).discard = true;
}