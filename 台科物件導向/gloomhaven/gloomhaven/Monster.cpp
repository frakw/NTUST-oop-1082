#include "Gloom_Haven.h"

Monster::Monster() :Creature() {
	team_num = Team_num::monster;
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
	this->team_num = input.team_num;
	this->show_in_room = input.show_in_room;
	this->map = input.map;
	this->finished_show = input.finished_show;
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
	case monster_status::disappear:show = false;break;//���X�{
	case monster_status::normal:break;//���q��
	case monster_status::elite: {//�׭^��
		elite = true;
		damage = elite_damage;
		max_life_value = elite_max_life_value;
		life_value = elite_max_life_value;
		range = elite_range;
	}break;
	default:break;
	}
}

void Monster::choose_card() {
	if (life_value <= 0 || !show_in_room || !show) {
		return;
	}
	//�ӺرکǪ����Ĥ@��(���ۥB�X�{)
	use_card[0] = find_card(race_card_number[name]);

}

void Monster::print(){
	if(life_value  <= 0 || !show_in_room || finished_show || !show){
		return;
	}
	cout << name << ' ' << setw(2) << setfill('0') << use_card[0].agility;
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch (use_card[0].skill_up[i].type)
		{
		case skill_type::move: {
			cout << " move " << use_card[0].skill_up[i].move_step;
		}break;
		case skill_type::attack: {
			cout << " attack " << use_card[0].skill_up[i].value;
			if (range != 0) {//���{�ǻݦLrange
				cout << " range " << use_card[0].skill_up[i].range;
			}
		}break;
		case skill_type::heal: {
			cout << " heal " << use_card[0].skill_up[i].value;
		}break;
		case skill_type::shield: {
			cout << " shield " << use_card[0].skill_up[i].value;
		}break;
		default:
			break;
		}
	}
	cout << endl;
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster + i == this || map->monster[i].name != name) continue;
		if (map->monster[i].life_value > 0 && map->monster[i].show_in_room) {
			map->monster[i].finished_show = true;
		}
	}
}
void Monster::action() {
	if (life_value <= 0 || !show_in_room) {
		return;
	}
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch(use_card[0].skill_up[i].type) {
		case skill_type::move: {//move
			this->move(use_card[0].skill_up[i].move_step,0);//0�i���N���(���v�T)
		}break;
		case skill_type::attack: {//attack
			this->attack(use_card[0].skill_up[i]);
		}break;
		case skill_type::heal: {//heal
			this->heal(use_card[0].skill_up[i].value);
		}break;
		case skill_type::shield: {//shield
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

void Monster::attack(const Skill const& skill) {
	int min = map->row * map->col;//�̤j�i�઺�B��
	int index = -1;//�S���N�O-1(�i�ਤ�⦺���F)
	for (int i = 0;i < map->character_amount;i++) {
		int tmpstep = map->a_star_path_step(this, map->character + i);
		if (tmpstep == no_path_found) {//�L�k������
			continue;
		}
		if (!map->in_vision(position, map->character[i].position)) {//�S������
			continue;
		}
		if (tmpstep < min) {//��X�Z���̤p������
			index = i;
			min = tmpstep;
		}
		else if (tmpstep == min) {//�Z���@�ˤ�Ĥ@�i�ӱ���
			if (creature_order_compare(map->character + i, map->character + index)) {
				index = i;
			}
		}
	}

	if (index == -1) {
		cout << "no one lock" << endl;
		return;
	}
	if (range != 0 && (range + skill.range) >= 1) {//���{
		if (min > (range + skill.range)) {//�ۤv��range�[�W�d�P��range
			cout << "no one lock" << endl;
			return;
		}
	}
	else {//���
		if (min > 1) {
			cout << "no one lock" << endl;
			return;
		}
	}

	cout << code << " lock " << map->character[index].code << " in distance " << min << endl;
	map->character[index].be_attack(code,skill.value + damage);//�[�W�ۤv�������O

}

void Monster::round_end() {//�Ӧ^�X�����᪺����(���]�ƭ�)
	//���~�аO
	TmpShield = 0;
	finished_choose = false;
	finished_show = false;
	if (life_value <= 0) {
		show = false;
		show_in_room = false;
		position.to_null();
	}
}

void Monster::to_discard() {
	if (life_value <= 0 || !show) {
		return;
	}
	find_card(race_card_number[name]).discard = true;
	if (find_card(race_card_number[name]).rewash_mark) {
		this->discard_to_hand();
	}
}

void Monster::set_debug() {
	if (race_card_number.find(name) == race_card_number.end()) {
		race_card_number.insert(make_pair(name,-1));
	}
}