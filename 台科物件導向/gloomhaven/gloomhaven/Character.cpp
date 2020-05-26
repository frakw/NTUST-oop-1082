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
	this->TmpShield = input.TmpShield;
	this->team_num = input.team_num;
	this->map = input.map;
	this->finished_choose = input.finished_choose;

	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		this->card[i] = input.card[i];
	}
	return *this;
}

void Character::choose_card(string input) {
	if (life_value <= 0) {
		cout << "this character already died! input again!" << endl;
		return;
	}

	stringstream ss(input);
	string card_number1;//�]���i���Jcheck�A�U�ϥ�string
	int  card_number2;
	ss >> card_number1;
	if (card_number1 == "check") {
		//��T
		this->check_card();
		return;
	}
	if (finished_choose) {//���g��J�L
		cout << "this character already choose card,Do you want to modify it(y/n)?" << endl;
		char ch = getline_char();
		while (ch != 'y' && ch != 'n') {
			cout << err << endl;
			ch = getline_char();
		}
		if (ch == 'n') {
			return;
		}
		sleep = false;//remember
	}
	if (card_number1 == "-1") {
		//����
		sleep = true;
		use_card[0].agility = 99;
		use_card[1].agility = 99;
		finished_choose = true;
	}
	else {
		ss >> card_number2;
		if (card_in_hand(atoi(card_number1.c_str())) && card_in_hand(card_number2)) {
			use_card[0] = find_card(atoi(card_number1.c_str()));
			use_card[1] = find_card(card_number2);
			finished_choose = true;
		}
		else {
			cout << "card number is not correct(not exist or discard or unavailable)! please input again!"<<endl;
		}
	}
}

void Character::print(){
	if (life_value > 0) {//���⤣�P�_�O�_�X�{
		cout << code << ' ' << use_card[0].agility << ' ';
		if (!sleep) {
			cout << use_card[0].number << ' ' << use_card[1].number;
		}
		else {
			cout << "-1";
		} 
		cout << endl;
	}
}

void Character::action(bool) {
	if (life_value <= 0) {
		return;
	}
	cout << code << "'s turn: card ";
	if (sleep) {//����A   ====== �|���ˬdIO err
		cout << "-1" << endl;
		this->heal(2);
#ifdef prompt_input
		cout << "�п�J�n�����d�P:" << endl;
#endif
		int remove_number = getline_int();
		while (!card_in_discard(remove_number)) {
			cout << "card number is not correct(not exist or in hand or unavailable)! please input again!" << endl;
			remove_number = getline_int();
		}
		find_card(remove_number).available = false;
		cout << "remove card: " << remove_number << endl;
		return;
	}
	else {
		cout << use_card[0].number << ' ' << use_card[1].number << endl;
	}
	bool card_first_index;
	string NumUD;
	int num;
num_err:
	NumUD = character_card_first_ud();
	while(NumUD == "check") {
		map->check();
		goto num_err;
	}
	num = atoi(NumUD.substr(0, NumUD.length() - 1).c_str());
	if (num != use_card[0].number && num != use_card[1].number) {
		cout << "card number error!,please choose one of the two selected cards" << endl;
		goto num_err;
	}
	card_first_index = (use_card[0].number == (NumUD[0] - '0'))?false:true;
	if (NumUD[1] == 'u') {//�W�b��
		for (int i = 0;i < use_card[card_first_index].skill_up_amount;i++) {//�Ĥ@�i
			run_skill(use_card[card_first_index].skill_up[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_down_amount;i++) {//�ĤG�i
			run_skill(use_card[!card_first_index].skill_down[i]);
		}
	}
	else {//�U�b��
		for (int i = 0;i < use_card[card_first_index].skill_down_amount;i++) {//�Ĥ@�i
			run_skill(use_card[card_first_index].skill_down[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_up_amount;i++) {//�ĤG�i
			run_skill(use_card[!card_first_index].skill_up[i]);
		}
	}
}

void Character::run_skill(Skill skill) {
	switch (skill.type) {
	case 0: {//move
		this->move(wasd(), skill.value);
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
	char mon_code;
	int index =-1;
	mon_code = getline_char();
	if (mon_code == '0') {
		return;
	}
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster[i].code == mon_code) {
			index = i;
			break;
		}
	}
	if (index == -1) {//bad index
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
	int tmprange = map->a_star_path_step(this, map->monster + index);
	if (tmprange <= skill.range/*�ˬd�g�{*/ &&
		tmprange!=-87 /*�i�H��F(�L�k��F�^��-87)*/ &&
		map->monster[index].show /*�өǪ����X�{*/ &&
		map->monster[index].life_value>0/*�өǪ��s��*/ &&
		map->in_vision(position, map->monster[index].position)){//��������(�u�ʮt�Ȫk)

		map->monster[index].be_attack(this->code,skill.value);
	}
	else {
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
}

void Character::round_end(bool debug_mode) {//�Ӧ^�X�����᪺����(���]�ƭ�)
	if (!sleep) {//�S����N�N�X��2�i�P���ܱ�P��
		find_card(use_card[0].number).discard = true;
		find_card(use_card[1].number).discard = true;
	}
	else {//����
		this->discard_to_hand();//��P��Ҧ��P���^��P(���]�t�w�������P)
	}
	finished_choose = life_value <= 0;
	sleep = false;
	TmpShield = 0;

}