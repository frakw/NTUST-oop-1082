#include "Gloom_Haven.h"
Monster::Monster() :Creature() {
}
Monster::Monster(string in_name, int val, int in_damage, int in_range, bool in_elite) : Creature(in_name, val, 6), damage(in_damage), range(in_range), elite(in_elite) {
}
Monster& Monster::operator=(const Monster& input) {
	this->name = input.name;
	this->damage = input.damage;
	this->range = input.range;
	this->life_value = input.life_value;
	this->max_life_value = input.max_life_value;
	this->card_amount = input.card_amount;
	this->card_total = input.card_total;
	this->code = input.code;
	this->position = input.position;
	this->TmpShield = input.TmpShield;
	//this->TmpAgility = input.TmpAgility;
	this->team_num = input.team_num;
	this->show_in_room = input.show_in_room;
	this->map = input.map;
	//elite�t�C---------------------------------
	this->elite = input.elite;
	this->elite_max_life_value = input.elite_max_life_value;
	this->elite_damage = input.elite_damage;
	this->elite_range = input.elite_range;
	//------------------------------------------
	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		card[i] = input.card[i];
	}
	return *this;
}
void Monster::switch_status(int num) {
	switch (num)
	{
	case 0:show = false;break;
	case 1:break;
	case 2: {
		elite = true;
		damage = elite_damage;
		max_life_value = elite_max_life_value;
		life_value = elite_max_life_value;
		range = elite_range;
	}break;
	default:break;
	}
}

void Monster::choose_card(bool debug_mode) {
	if (life_value <= 0 || !show_in_room) {
		return;
	}
	if (debug_mode) {
		use_card[0] = card[debug_mode_card_number];
		debug_mode_card_number++;
	}
	else {
		use_card[0] = card[rand() % card_amount];
	}
}

void Monster::print(){
	if(life_value  <= 0 || !show_in_room){
		return;
	}
	cout << name << ' ' << use_card[0].agility;
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch (use_card[0].skill_up[i].type)
		{
		case 0: {
			cout << " move " << use_card[0].skill_up[i].move_step;
		}break;
		case 1: {
			cout << " attack " << use_card[0].skill_up[i].value;
			if (use_card[0].skill_up[i].range != -1) {
				cout << " range " << use_card[0].skill_up[i].range;
			}
		}break;
		case 2: {
			cout << " heal " << use_card[0].skill_up[i].value;
		}break;
		case 3: {
			cout << " shield " << use_card[0].skill_up[i].move_step;
		}break;
		default:
			break;
		}
	}
	cout << endl;
}
void Monster::action(bool debug_mode) {
	if (life_value <= 0 || !show_in_room) {
		return;
	}
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch(use_card[0].skill_up[i].type) {
		case 0: {//move
			this->move(use_card[0].skill_up[i].move_step,0);//0�i���N���(���v�T)
		}break;
		case 1: {//attack
			this->attack(use_card[0].skill_up[i]);
		}break;
		case 2: {//heal
			this->heal(use_card[0].skill_up[i].value);
		}break;
		case 3: {//shield
			this->shield(use_card[0].skill_up[i].value);
		}break;
		default:break;
		}
	}
	if (!debug_mode) {
		cout << "�нT�{�Ǫ�����ʡA�����N��H�~��(getch):" << endl;
		_getch();
	}
}

void Monster::attack(Skill skill) {
	//cout << "monster attack" << endl;
	int min = map->row * map->col;//�̤j�i�઺�B��
	int index=-1;//�S���N�O-1(�i�ਤ�⦺���F)
	for (int i = 0;i < map->character_amount;i++) {
		int tmpstep = map->a_star_path_step(this, map->character + i);
		if (tmpstep == -87) {//�L�k������
			continue;
		}
		if (tmpstep < min) {//��X�Z���̤p������
			index = i;
			min = tmpstep;
		}
		else if (tmpstep == min) {//�Z���@�ˤ�Ĥ@�i�ӱ���
			if (map->character[i].use_card[0].agility < map->character[index].use_card[0].agility) {
				index = i;
			}
			else if (map->character[i].use_card[0].agility == map->character[index].use_card[0].agility) {
				if (map->character[i].use_card[1].agility < map->character[index].use_card[1].agility) {//��ĤG�i�ӱ���
					index = i;
				}
				else if (map->character[i].use_card[1].agility == map->character[index].use_card[1].agility) {
					if (map->character[i].code < map->character[index].code) {//��N��
						index = i;
					}
				}
			}
		}
	}
	if (min > (range + skill.range) || index==-1) {//�ۤv��range�[�W�d�P��range
		cout << "no one lock" << endl;
		return;
	}
	if (map->in_vision(position, map->character[index].position)) {//�ˬd����
		cout << code << " lock " << map->character[index].code << " in distance " << min << endl;
		map->character[index].be_attack(code,skill.value + damage);//�[�W�ۤv�������O
	}
}

void Monster::round_end(bool debug_mode) {//�Ӧ^�X�����᪺����(���]�ƭ�)
	//���~�аO
	TmpShield = 0;
	if (life_value > 0) {
		if (use_card[0].rewash_mark) {
			if (debug_mode) {
				debug_mode_card_number = 0;
			}
			this->discard_to_hand();
		}
	}
	else {
		show = false;
		show_in_room = false;
		position.to_null();
	}
}