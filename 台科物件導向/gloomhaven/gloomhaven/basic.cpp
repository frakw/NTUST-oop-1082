#include "Gloom_Haven.h"
Skill::Skill():type(-1), value(-1) {
	
}

Skill::Skill(string name, int val) : value(val) {
	this->set(name, val);
}

Skill::Skill(int in_type, int val) : value(val) {
	if (in_type < 0 || in_type > 3) {
		this->type = -1;//skill type error!
	}
	else {
		this->type = in_type;
	}
}
void Skill::set(string name, int val) {
	if (name == "move") {
		this->type = 0;
	}
	else if (name == "attack") {
		this->type = 1;
	}
	else if (name == "heal") {
		this->type = 2;
	}
	else if (name == "shield") {
		this->type = 3;
	}
	else {
		this->type = -1;//skill type error!
	}
	this->value = val;
}

//============================================================
Card::Card() {
	skill_up = nullptr;
	skill_down = nullptr;
}
Card::Card(const Card& input) {
	*this = input;
}
Card::Card(int in_agility, bool mark, Skill* a) : agility(in_agility), rewash_mark(mark), skill_up(a) {}
Card::Card(int in_agility, bool mark, Skill* a, Skill* b) : agility(in_agility), rewash_mark(mark), skill_up(a), skill_down(b) {}
Card::~Card() {
	if (skill_up != nullptr) {
		delete[] skill_up;
		skill_up = nullptr;
		skill_up_amount = 0;
	}
	if (skill_down != nullptr) {
		delete[] skill_down;
		skill_down = nullptr;
		skill_down_amount = 0;
	}
}
Card& Card::operator=(const Card& input) {
	this->~Card();
	if (input.skill_up_amount > 0 && input.skill_up!=nullptr) {
		this->skill_up_amount = input.skill_up_amount;
		skill_up = new Skill[skill_up_amount];
		for (int i = 0;i < skill_up_amount;i++) {
			skill_up[i] = input.skill_up[i];
		}
	}
	if (input.skill_down_amount > 0 && input.skill_down!= nullptr) {
		this->skill_down_amount = input.skill_down_amount;
		skill_down = new Skill[skill_down_amount];
		for (int i = 0;i < skill_down_amount;i++) {
			skill_down[i] = input.skill_down[i];
		}
	}
	available = input.available;
	discard = input.discard;
	number = input.number;
	agility = input.agility;
	rewash_mark = input.rewash_mark;
	return *this;
}

//==================================================================
Creature::Creature() {}
Creature::Creature(string in_name, int val, int in_card_amount) :name(in_name), life_value(val), card_amount(in_card_amount) {

}
Creature::~Creature() {
	if (card != nullptr) {
		delete[] card;
		card = nullptr;
	} 
}

int Creature::card_available_amount() {//�����d�P��(��P��+��P)
	int count = 0;
	for (int i = 0;i < card_amount;i++) {
		if (card[i].available) {
			count++;
		}
	}
	return count;
}
int Creature::card_hand_amount() {//�i�Υd�P��
	int count = 0;
	for (int i = 0;i < card_amount;i++) {
		if (!card[i].discard) {
			count++;
		}
	}
	return count;
}
int Creature::card_throw_amount() {//��P���
	int count = 0;
	for (int i = 0;i < card_amount;i++) {
		if (card[i].discard) {
			count++;
		}
	}
	return count;
}

Card& Creature::find_card(int number) {//int �ǤJ�s��number�A�^�Ǹ�Card reference
	for (int i = 0;i < card_amount;i++) {
		if (card[i].number == number) {
			return card[i];
		}
	}
}

void Creature::heal(int add) {
	if (add > 0) {
		life_value += add;
		if (life_value > max_life_value) {
			life_value = max_life_value;
		}
	}
}

void Creature::discard_to_hand() {//��P��Ҧ��P���^��P�A�����]�t�w�Q�������P(availible == false)
	for (int i = 0;i < card_amount;i++) {
		if (card[i].available && card[i].discard) {
			card[i].discard = false;
		}
	}
}

void Creature::check_card() {//�L�X�d�P�s��(��P�P��P)�A�s���Ѥp��j
	int max_number=-1;//�̤j�s��
	for (int i = 0;i < card_amount;i++) {
		if (card[i].number > max_number) {
			max_number = card[i].number;
		}
	}
	int min_number = max_number;//�̤p�s��
	for (int i = 0;i < card_amount;i++) {
		if (card[i].number < min_number) {
			min_number = card[i].number;
		}
	}
	int count = 0;
	cout << "hand:";
	for (int i = min_number;i <= max_number;i++) {//�q0�}�l�]�j��
		for (int j = 0;j < card_amount;j++) {
			if (card[j].number == i) {
				if (card[j].available && !card[j].discard) {
					cout << (count != 0?", ":" ")<< card[j].number;
					count++;
					break;
				}
			}
		}
	}
	count = 0;
	cout << "; discard:";
	for (int i = min_number;i <= max_number;i++) {//�q0�}�l�]�j��
		for (int j = 0;j < card_amount;j++) {
			if (card[j].number == i) {
				if (card[j].available && card[j].discard) {
					cout << (count != 0 ? ", " : " ") << card[j].number;
					count++;
					break;
				}
			}
		}
	}
	cout << endl;
}
