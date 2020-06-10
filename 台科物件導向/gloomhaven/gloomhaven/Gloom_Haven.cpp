#define DEBUG
#include "Gloom_Haven.h"
#undef DEBUG
using namespace std;


Gloom_Haven::Gloom_Haven(tuple<Character*, int, Monster*, int, Map*>input){
	this->set(input);
}

void Gloom_Haven::set(tuple<Character*, int, Monster*, int, Map*> input) {
	this->map = get<4>(input);

	this->character = get<0>(input);
	this->map->character = get<0>(input);

	this->character_amount = get<1>(input);
	this->map->character_amount = get<1>(input);

	this->monster = get<2>(input);
	this->map->monster = get<2>(input);

	this->monster_amount = get<3>(input);
	this->map->monster_amount = get<3>(input);

	this->all = new Creature * [this->character_amount + this->monster_amount];//�Ҧ�����P�Ǫ��Ƨǫ�s��ϡA������A�Ǫ�
	for (int i = 0;i < this->character_amount;i++) {
		this->all[i] = this->character + i;
	}
	for (int i = 0;i < this->monster_amount;i++) {
		this->all[i+ this->character_amount] = this->monster + i;
		this->add_to_group(this->monster + i);
	}
}

void Gloom_Haven::start() {
	this->map->check_room();
	this->map->set_choosing_environment();//��ܦ�m�ɱM�ΡAchoose_pos�̤]�|�I�s��
	for (int i = 0;i < character_amount;i++) {
		prompt_input("�п�ܨ��� "<<character[i].code<<" ����m:");
		this->map->show_choosing_room();//��X��ܮɪ��a�ϡA��X�e�nset_choosing_environment
		this->map->choose_pos(i,wasd());//��ܦ�m�D�{��
	}
	prompt_input("�_�l�a��:");
	this->map->show_room();//�Ĥ@����X�a��(�D��ܪ��A)
	prompt_input("�}�l�C��");
	int round_count = 1;
	string choose;
	while (1){
		if (monster_remain() == 0 && map->door_amount() == 0) {
			cout << "character win~" << endl;
			break;
		}
		else if (character_remain() == 0) {
			cout << "monster win~" << endl;
			break;
		}
		cout << "round " << round_count <<':'<< endl;
		for (int i = 0;i < character_amount;i++) {//�ˬd���L����L�k����ΥX�P
			if (character[i].card_hand_amount() < 2 && character[i].card_discard_amount() < 2 && character[i].life_value > 0/*�Ө���]�����s��*/) {
				character[i].life_value = 0;
				cout << character[i].code << " is killed!!" << endl;
				this->map->show_room();
			}
		}
		while(choose_remain()) {//�����P(�o�Ӥ����virtual�A�]���|check�åB���Ǥ��@�w)
			choose = character_card_choose();
			int i;
			for (i = 0;i < character_amount;i++) {
				if (character[i].code == choose[0] && character[i].life_value > 0) {
					character[i].choose_card(choose.substr(2));
					break;
				}
			}
			if (i == character_amount) {
				cout << "character not found,please input again!" << endl;
			}
		}
		for (int i = 0;i < all_group.size();i++) {
			if (!monster_race_amount(all_group[i].name)) continue;
			if (!debug_mode) {
				do {
					all_group[i].card_number = rand() % all_group[i].member[i]->card_amount;
				} while (monster_race_in_discard(all_group[i].name, all_group[i].card_number));
			}
			else {
				all_group[i].card_number++;
			}
			all_group[i].choose_card();
		}
		sort(all, all + character_amount + monster_amount, creature_order_compare);
		prompt_input("����P�Ǫ���ʶ��Ǧp�U:");
		for (int i = 0;i < character_amount + monster_amount;i++) {//�L�X���� ����L�ӱ��ȻP��P�s�� �Ǫ��L�d�P���e
			all[i]->print();//virtual
		}
		prompt_input("��ʶ��q:");
		for (int i = 0;i < character_amount + monster_amount;i++) {//��ʮɶ�
			all[i]->action();//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//�Ӧ^�X�����᪺����(���]�ƭ�)
			all[i]->round_end();//virtual
		}


		if (this->map->check_room()) {//���s�ˬd�ж������A�ñN�}�Ҫ����]���a�O�A���}���N���s��X�a��
			this->map->show_room();//���}���~�ݭn��X�a��
		}
		
		for (int i = 0;i < all_group.size();i++) {
			if (!monster_race_amount(all_group[i].name)) continue;
			all_group[i].round_end();
		}
		round_count++;
	}
}

Gloom_Haven::Gloom_Haven() {}

Gloom_Haven::~Gloom_Haven() {
	//if (map != nullptr) { map �n�bclass txt ������O����(�]���a�Ϸ|���s���J)�A�_�h�|��������O����
	//	delete map;//���i��delete[]
	//	map = nullptr;
	//}
	mydelete(character);
	mydelete(monster);
	mydelete(all);
}

int Gloom_Haven::character_remain() {//����Ѿl��
	int count = 0;
	for (int i = 0;i < character_amount;i++) {
		if (character[i].life_value > 0) {
			count++;
		}
	}
	return count;
}

int Gloom_Haven::monster_remain() {//�Ǫ��Ѿl��
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0 && monster[i].show) {
			count++;
		}
	}
	return count;
}

int Gloom_Haven::choose_remain() {//�Ѿl�X�Ө��⥼��P�Ϊ���
	int count = 0;
	for (int i = 0;i < character_amount;i++) {
		if (!character[i].finished_choose && character[i].life_value > 0) {//����P�B����
			count++;
		}
	}
	return count;
}

bool creature_order_compare(const Creature* const& a,const Creature* const& b) {
	if (a->use_card[0].agility == b->use_card[0].agility) {
		if (a->team_num == b->team_num) {//����P�ӱ��ۦP
			if (a->team_num == Team_num::character) {//����P����ӱ��ۦP
				if (a->use_card[1].agility == b->use_card[1].agility) {
					return a->code < b->code;
				}
				return a->use_card[1].agility < b->use_card[1].agility;
			}
			else if (a->team_num == Team_num::monster) {//�Ǫ��P�Ǫ��ӱ��ۦP
				return a->code < b->code;
			}
		}
		else {//����P�Ǫ��ӱ��ۦP
			return a->team_num == Team_num::character;
		}
	}
	return a->use_card[0].agility < b->use_card[0].agility;
}

int Gloom_Haven::monster_race_amount(string name) {
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].name == name && monster[i].show_in_room && monster[i].show && monster[i].life_value > 0) {
			count++;
		}
	}
	return count;
}

bool Gloom_Haven::monster_race_in_discard(string name, int card_num) {
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].name == name && monster[i].show_in_room && monster[i].show && monster[i].life_value > 0) {
			return monster[i].in_discard(card_num);
		}
	}
	return false;
}


void Gloom_Haven::add_to_group(Monster* add) {
	for (int i = 0;i < all_group.size();i++) {
		if (all_group[i].name == add->name) {
			all_group[i].member.push_back(add);
			return;
		}
	}
	Race new_group;
	new_group.name = add->name;
	all_group.push_back(new_group);
	all_group.back().member.push_back(add);
}

void Race::choose_card() {
	for (int i = 0;i < member.size();i++) {
		member[i]->use_card[0] = member[i]->find_card(card_number);
		member[i]->find_card(card_number).discard = true;
	}
}

void Race::round_end() {
	if (member[0]->find_card(card_number).rewash_mark) {
		for (int i = 0;i < member.size();i++) {
			member[i]->discard_to_hand();
			card_number = -1;
		}
	}
}