#include "Gloom_Haven.h"
#include "a_star_path.h"
Map::Map() {}
Map::Map(int in_row, int in_col) :row(in_row), col(in_col) {
	body = new char* [row] {};
	show = new bool* [row] {};
	for (int i = 0;i < row;i++) {
		body[i] = new char[col] {};
		show[i] = new bool[col] {};
	}
}
Map::~Map() {
	delete_2d(body, row);
	delete_2d(show, row);
	mydelete(door_pos);
}
void Map::set(string input) {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			body[i][j] = input[i * col + j];
			if (body[i][j] == map_obj::door) {
				door_total_amount++;
			}
		}
	}
	door_pos = new Coord[door_total_amount];
	int index = 0;
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (body[i][j] == map_obj::door) {
				door_pos[index] = Coord( j,i );
				index++;
			}
		}
	}
}

bool Map::check_room() {
	bool open = false;
	if (!now_monster_amount()) {//�Y���W�S���Ǫ��A�ˬd���O�_�}��
		for (int i = 0;i < door_total_amount;i++) {//�ˬd�����S�������ۡA�}�ҫ�]��-1,-1
			if (door_pos[i].not_null()) {
				if (coord_in_body(door_pos[i]) != map_obj::door) {
					door_pos[i].to_null();
					open = true;//���}��
				}
			}
		}
	}
	for (int i = 0;i < row;i++) {//���]�Ҧ��ϰ�A�i�g��reset funtion
		for (int j = 0;j < col;j++) {
			show[i][j] = false;
		}
	}
	this->fill_room(fill_start);//���ͷs��show
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].show && monster[i].position.not_null() && monster[i].life_value > 0) {
			if (coord_in(show,monster[i].position)) {
				monster[i].show_in_room = true;
			}
			else {
				monster[i].show_in_room = false;
			}
		}
		else {
			monster[i].show_in_room = false;
		}
	}
	return open;
}

void Map::fill_room(Coord pos) {
	if (!coord_legal(pos)) {
		return;
	}
	if (coord_in(body,pos) == map_obj::wall || coord_in(show, pos)) {
		return;
	}
	else if (coord_in(body, pos) == map_obj::door) {
		coord_in(show, pos) = true;
		return;
	}
	else if(coord_in(body, pos) != map_obj::m_floor && coord_in(body, pos) != map_obj::barrier){//����ΩǪ�
		for (int i = 0;i < door_total_amount;i++) {
			if (door_pos[i] == pos) {//�Y�Ӧa�謰���A���������W�h
				coord_in(show, pos) = true;
				return;
			}
		}
		coord_in(show, pos) = true;
	}
	else {//�a�O�λ�ê
		coord_in(show, pos) = true;
	}
	Coord direction[4] = {UP(pos),DOWN(pos),LEFT(pos),RIGHT(pos)};
	for (int i = 0;i < 4;i++) {
		this->fill_room(direction[i]);
	}
}

void Map::show_room() {
	this->update_all_creature();
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				cout << ((body[i][j] == map_obj::wall) ? ' ' : body[i][j]);
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

void Map::show_choosing_room() {
	for (int i = 0;i < monster_amount;i++) {//copy from update
		if (!monster[i].show || monster[i].position.is_null()) continue;
		if (monster[i].life_value > 0) {
			coord_in(body, monster[i].position) = monster[i].code;
		}
		else {
			coord_in(body, monster[i].position) = map_obj::m_floor;
		}
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.is_null()) continue;
		if (character[i].life_value > 0) {
			coord_in(body, character[i].position) = character[i].code;
		}
		else {
			coord_in(body, character[i].position) = map_obj::m_floor;
		}
	}
	for (int i = 0;i < row;i++) {//do not call show_room function�Ano need to update
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				cout << ((body[i][j] == map_obj::wall) ? ' ' : body[i][j]);
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

void Map::set_choosing_environment() {
	int miny = row;
	int start_index = 0;
	for (int i = 0;i < 4;i++) {
		if (start_pos[i].is_null()) continue;
		if (start_pos[i].y < miny) {
			start_index = i;
			miny = start_pos[i].y;
		}
		else if (start_pos[i].y == miny) {
			if (start_pos[i].x < start_pos[start_index].x) {
				start_index = i;
			}
		}
	}
	for (int i = 0;i < 4;i++) {//�i���m�]��_ *
		if (start_pos[i].not_null()) {
			coord_in(body, start_pos[i]) = start_index != i ? (char)map_obj::select_pos : (char)map_obj::star_pos;
		}
	}
	star_pos = start_pos[start_index];
}

Coord& Map::find_pos(Coord* check,int max,Coord pos) {
	for (int i = 0;i < max;i++) {
		if (check[i] == pos) {
			return check[i];
		}
	}
}

void Map::choose_pos(int index, string step) {
	this->set_choosing_environment();//�]�m���u�P��ܬP�P��m
	Coord now = star_pos;
	coord_in(body, now) = map_obj::select_pos;//�Ȯɳ]�����u�A��Kwasd
	for (int i = 0;i < step.length();i++) {
		switch (step[i]) {
		case dir::up: {
			if (now.y - 1 >= 0) {
				if (coord_in(body, now.up()) == map_obj::select_pos) {
					now = now.up();
				}
			}
		}break;
		case dir::left: {
			if (now.x - 1 >= 0) {
				if (coord_in(body, now.left()) == map_obj::select_pos) {
					now = now.left();
				}
			}
		}break;
		case dir::down: {
			if (star_pos.y + 1 < row) {
				if (coord_in(body, now.down()) == map_obj::select_pos) {
					now = now.down();
				}
			}
		}break;;
		case dir::right: {
			if (star_pos.x + 1 < col) {
				if (coord_in(body, now.right()) == map_obj::select_pos) {
					now = now.right();
				}
			}
		}break;
		case dir::stay:
		default:break;
		}
	}
	character[index].position = now;
	find_pos(start_pos, 4, now).to_null();
	if (index == character_amount - 1) {//�̫�@�Ө����ܧ���A�N�Ҧ����u��^�a�O
		for (int i = 0;i < 4;i++) {
			if (start_pos[i].not_null()) {
				coord_in(body, start_pos[i]) = map_obj::m_floor;
			}
		}
	}
	else {
		this->set_choosing_environment();//�]�m���u�P��ܬP�P��m
	}
}

void Map::update_all_creature() {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				if (body[i][j] != map_obj::wall && 
					body[i][j] != map_obj::m_floor &&
					body[i][j] != map_obj::barrier && 
					body[i][j] != map_obj::door) 
				{

					body[i][j] = map_obj::m_floor;//����Ҧ��ͪ���m�]���a�O
				}
			}
		}
	}
	for (int i = 0;i < door_total_amount;i++) {//��
		if (door_pos[i].not_null()) {
			coord_in(body,door_pos[i]) = map_obj::door;
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (!monster[i].show || monster[i].position.is_null() || monster[i].life_value <= 0) continue;
		coord_in(body, monster[i].position) = monster[i].code;
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.is_null() || character[i].life_value <= 0) continue;
		coord_in(body, character[i].position) = character[i].code;
	}
}

int Map::now_monster_amount() {
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0 && monster[i].show_in_room && monster[i].show) {
			count++;
		}
	}
	return count;
}

int Map::door_amount() {
	int count = 0;
	for (int i = 0;i < door_total_amount;i++) {
		if (door_pos[i].not_null()) {
			count++;
		}
	}
	return count;
}

Creature* Map::creature_in(Coord pos) {
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position == pos && character[i].life_value > 0) {
			return character + i;
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].position == pos && monster[i].life_value>0 && monster[i].show && monster[i].show_in_room) {
			return monster + i;
		}
	}
	return nullptr;
}

char& Map::coord_in_body(Coord pos) {
	if (!coord_legal(pos)) {
		cout << "coord ilegal!!" << endl;
		return body[0][0];
	}
	return body[pos.y][pos.x];
}


bool Map::in_vision(Coord a, Coord b) {//�u�ʮt�Ȫk
	Coord check;
	if (b.x < a.x) {
		swap(a, b);//�p��x�ba�A�j��x�bb
	}
	else if (b.x == a.x) {//�����ײv�L���j�A��y��
		if (b.y < a.y) {
			swap(a, b);
		}
		check.x = a.x;
		for (int i = a.y;i < b.y;i++) {
			check.y = i;
			if (coord_in_body(check) == map_obj::wall) {
				return false;
			}
		}
		return true;
	}
	//��x��
	double slope = ((double)b.y- (double)a.y) / ((double)b.x- (double)a.x);//m�ײv
	double bb = (double)a.y - slope * (double)a.x;//y=mx+b
	for (int i = a.x;i < b.x;i++) {
		check.x = i;
		check.y = ceil((double)i* slope + bb);
		if (coord_in_body(check) == map_obj::wall) {
			return false;
		}
	}
	return true;
}


void Map::check() {//�����ʫe�A��Jcheck�A�n�C�X�Ҧ�����P�Ǫ���hp�P���m��
	for (int i = 0;i < character_amount;i++) {
		if (character[i].life_value > 0) {
			character[i].check();
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0 && monster[i].show_in_room && monster[i].show) {
			monster[i].check();
		}
	}
}

bool Map::coord_legal(Coord a) {
	return (a.x < col) && (a.x >= 0) && (a.y < row) && (a.y >= 0);
}