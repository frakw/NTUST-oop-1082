#include "Gloom_Haven.h"

using namespace std;

Gloom_Haven::Gloom_Haven(tuple<Character*, int, Monster*, int, Map*>input, bool mode) :DEBUG_MODE(mode) {
	this->set(input, mode);
}

void Gloom_Haven::set(tuple<Character*, int, Monster*, int, Map*> input, bool mode) {
	this->DEBUG_MODE = mode;
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
	}
}

void Gloom_Haven::start() {
	this->map->check_room();
	this->map->set_choosing_environment();//��ܦ�m�ɱM�ΡAchoose_pos�̤]�|�I�s��
	for (int i = 0;i < character_amount;i++) {
		this->map->show_choosing_room();//��X��ܮɪ��a�ϡA��X�e�nset_choosing_environment
		this->map->choose_pos(i,wasd());//��ܦ�m�D�{��
	}
	this->map->show_room();//�Ĥ@����X�a��(�D��ܪ��A)
	int round_count = 1;
	string choose;
	while ((character_remain() != 0 && monster_remain() != 0) || this->map->door_amount()!=0) {
		cout << "round " << round_count <<':'<< endl;
		bool card_too_little = false;
		for (int i = 0;i < character_amount;i++) {//�ˬd���L����L�k����ΥX�P
			if (character[i].card_hand_amount() < 2 && character[i].card_discard_amount() < 2 && character[i].life_value>0/*�Ө���]�����s��*/) {
				character[i].life_value = 0;
				card_too_little = true;
			}
		}
		if (card_too_little) {
			this->map->show_room();//�����⦺�`���X�̲צa��
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
		for (int i = 0;i < monster_amount;i++) {//�Ǫ���P
			monster[i].choose_card(DEBUG_MODE);
		}
		sort(all, all + character_amount + monster_amount,
			[](Creature* const& a, Creature* const& b) -> bool {
				if (a->use_card[0].agility == b->use_card[0].agility) {
					if (a->team_num == b->team_num) {//����P�ӱ��ۦP
						if (a->team_num == 0) {//����P����ӱ��ۦP
							if (a->use_card[1].agility == b->use_card[1].agility) {
								return a->code < b->code;
							}
							return a->use_card[1].agility < b->use_card[1].agility;
						}
						else if (a->team_num == 1) {//�Ǫ��P�Ǫ��ӱ��ۦP
							return a->code < b->code;
						}
					}
					else {//����P�Ǫ��ӱ��ۦP
						return a->team_num == 0;
					}
				}
				return a->use_card[0].agility < b->use_card[0].agility;
			});

		for (int i = 0;i < character_amount + monster_amount;i++) {//�L�X���� ����L�ӱ��ȻP��P�s�� �Ǫ��L�d�P���e
			all[i]->print();//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//��ʮɶ�
			all[i]->action(DEBUG_MODE);//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//�Ӧ^�X�����᪺����(���]�ƭ�)
			all[i]->round_end(DEBUG_MODE);//virtual
		}

		if (this->map->check_room()) {//���s�ˬd�ж������A�ñN�}�Ҫ����]���a�O�A���}���N���s��X�a��
			this->map->show_room();//���}���~�ݭn��X�a��
		}
		round_count++;
	}
	if (!monster_remain()) {
		cout << "character win~" << endl;
	}
	else {
		cout << "monster win~" << endl;
	}
}

Gloom_Haven::Gloom_Haven() {

}

Gloom_Haven::~Gloom_Haven() {
	//if (map != nullptr) { map �n�bclass txt ������O����(�]���a�Ϸ|���s���J)�A�_�h�|��������O����
	//	delete map;//���i��delete[]
	//	map = nullptr;
	//}
	if (character != nullptr) {
		delete[] character;
	}
	if (monster != nullptr) {
		delete[] monster;
	}
	if (all != nullptr) {
		delete[] all;
	}
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