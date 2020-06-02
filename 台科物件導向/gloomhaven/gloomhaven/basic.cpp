#include "Gloom_Haven.h"
Skill::Skill():type(-1), value(-1) {}
Skill::Skill(string name, int val) : value(val) {
	this->set(name, val);
}
Skill::Skill(int in_type, int val) : type(in_type),value(val) {}
void Skill::set(string name, int val) {
	this->value = val;
	string sk_name[4] = { "move" ,"attack" ,"heal" ,"shield" };
	for (int i = 0;i < 4;i++) {
		if (name == sk_name[i]) {
			this->type = i;
			break;
		}
	}
}
Skill::Skill(const Skill& input) {
	*this = input;
}
Skill& Skill::operator=(const Skill& input) {
	this->type = input.type;
	this->value = input.value;
	this->range = input.range;
	this->move_step = input.move_step;
	return *this;
}

//============================================================
Card::Card():skill_up(nullptr),skill_down(nullptr){}
Card::Card(const Card& input) {
	*this = input;
}
Card::Card(int in_agility, bool mark, Skill* a) : agility(in_agility), rewash_mark(mark), skill_up(a) {}
Card::Card(int in_agility, bool mark, Skill* a, Skill* b) : agility(in_agility), rewash_mark(mark), skill_up(a), skill_down(b) {}
Card::~Card() {
	mydelete(skill_up);
	skill_up_amount = 0;
	mydelete(skill_down);
	skill_down_amount = 0;
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
Creature::Creature(string in_name, int val, int in_card_amount) :name(in_name), life_value(val), card_amount(in_card_amount) {}
Creature::~Creature() {
	mydelete(card);
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
int Creature::card_discard_amount() {//��P���
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
	if (add < 0) {
		add = 0;
	}
	life_value += add;
	if (life_value > max_life_value) {
		life_value = max_life_value;
	}
	cout << code << " heal " << add << ", now hp is " << life_value << endl;
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
	cout << "hand: ";
	for (int i = min_number;i <= max_number;i++) {//�q0�}�l�]��̤j
		for (int j = 0;j < card_amount;j++) {
			if (card[j].number == i) {
				if (card[j].available && !card[j].discard) {
					cout << (count != 0?", ":"")<< card[j].number;
					count++;
					break;
				}
			}
		}
	}
	count = 0;
	cout << "; discard: ";
	for (int i = min_number;i <= max_number;i++) {//�q0�}�l�]��̤j
		for (int j = 0;j < card_amount;j++) {
			if (card[j].number == i) {
				if (card[j].available && card[j].discard) {
					cout << (count != 0 ? ", " : "") << card[j].number;
					count++;
					break;
				}
			}
		}
	}
	cout << endl;
}


void Creature::shield(int add) {
	if (add < 0) {
		add = 0;
	}
	cout << code << " shield " << add << " this turn"<<endl;
	TmpShield += add;
}

void Creature::be_attack(char attacker_code,int attack_val) {
	if (attack_val < 0) {
		attack_val = 0;
	}
	cout << attacker_code << " attack " << code << ' ' << attack_val << " damage, ";
	cout << code << " shield " << TmpShield << ", "<<code << " remain ";
	if (TmpShield < attack_val) {
		life_value -= (attack_val - TmpShield);
	}
	cout << life_value << " hp" <<endl;
	if (life_value <= 0) {
		cout << code << " is killed!!" << endl;
		prompt_input(code << " ���`�᪺�a��:");
		position.to_null();
		this->map->show_room();
	}
}

void Creature::move(string step,int step_count) {
	if (step.length() > step_count && team_num == 0) {//���⤣�i�W�L�̤j�B�ơA���s��J
		cout << "error move!!!" << endl;
		this->move(wasd(), step_count);
		return;
	}
	Coord latest_allow = position;
	Coord now = position;
	for (int i = 0;i < step.length();i++) {
		Coord direction[4] = { {now.x,now.y - 1},{now.x - 1,now.y},{now.x,now.y + 1},{now.x + 1,now.y} };
		int dir_index;
		switch (step[i])
		{
		case'w':dir_index = 0;break;
		case'a':dir_index = 1;break;
		case's':dir_index = 2;break;
		case'd':dir_index = 3;break;
		case'e':continue;
		default:break;
		}
		char now_char = map->coord_in_body(direction[dir_index]);
		Creature* now_life = map->creature_in(direction[dir_index]);

		if (now_char == '1' || (team_num != 1 && now_char == '3')) {
			latest_allow = direction[dir_index];
			now = direction[dir_index];

		}
		else if (now_life != nullptr) {
			if (now_life->team_num == team_num) {
				now = direction[dir_index];

			}
			else if (now_life->team_num != team_num && team_num == 0) {//���⤣�i��L��ê���μĤH
				cout << "error move!!!" << endl;
				this->move(wasd(),step_count);
				return;
			}
		}
		else {//�Ѿl���O��ê���P���
			if (team_num == 0) {//���⤣�i��L��ê������A�Ǫ��h�|�Q�צ�
				cout << "error move!!!" << endl;
				this->move(wasd(), step_count);
				return;
			}
		}

	}
	position = latest_allow;
	map->show_room();
}

void Creature::check() {//�����ʫe�A��Jcheck�A�n�C�X�Ҧ�����P�Ǫ���hp�P���m��
	cout << code << "-hp: " << life_value << ", shield: " << TmpShield << endl;
}

bool Creature::card_in_hand(int number) {//�ǤJ�s���A�^�ǸӵP�O���O��P�Aerror handling��
	for (int i = 0;i < card_amount;i++) {
		if (card[i].number == number && card[i].available && !card[i].discard) {
			return true;
		}
	}
	return false;
}

bool Creature::card_in_discard(int number) {
	for (int i = 0;i < card_amount;i++) {
		if (card[i].number == number && card[i].available && card[i].discard) {//�ǤJ�s���A�^�ǸӵP�b���b��P��Aerror handling��
			return true;
		}
	}
	return false;
}