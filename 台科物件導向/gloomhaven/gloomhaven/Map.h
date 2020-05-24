#pragma once
class Creature;
class Character;//���iinclude ���Y�ɡA�|�X�{��|�����W�d-���]��int
class Monster;//���iinclude ���Y�ɡA�|�X�{��|�����W�d-���]��int
using namespace std;

class Map {
public:
	Map();
	Map(int in_row, int in_col);
	~Map();
	void set(string input);
	void choose_pos(int,string);//int���ĴX���}��Astring ��wasd
	void set_choosing_environment();//�ܧ��ܦ�m��char�P�Ǫ���m��char
	void show_choosing_room();//��ܮɱM�Ϊ���ܦa��
	void check_room();//�ˬd�i���d��A�i���y��show[y][x]�]��true
	void fill_room(Coord pos);//���j�禡�A��check_room�I�s
	void show_room();//�I�s�e�O�o��check��X�i���d��
	void update_all_creature();//��s�ͪ���m�A�Φ��`�R��
	Coord& find_pos(Coord*, int max, Coord pos);
	int now_monster_amount();//�ثe���W�Ǫ���(����)
	int door_amount();//���Ѿl���ƶq
	int now_door_amount();//�ثe�����ƶq
	Creature* creature_in(Coord);
	char& coord_in_body(Coord);


	int a_star_path_step(Creature*, Creature*);//A�P�t��k��M�̵u�B��


	bool in_vision(Coord, Coord);//�u�ʮt�Ȫk

	int row=0, col=0;
	char** body = nullptr;
	bool** show = nullptr;
	void copy_to(bool**,bool**);//�ƻs�W��G���}�C��
	Coord star_pos;//�P�P��m
	Coord start_pos[4] = {};//�i���m�A�]��-1,-1�N��w���
	Coord fill_start;//���j�_�l��m�A�w�]start_pos[0]
	Coord* door_pos = nullptr;//������m�A�}����O�o�]��-1,-1
	int door_total_amount=0;//�`�@�����ƶq(��J�a�Ϯɭp��)
	Character* character = nullptr;
	int character_amount = 0;
	Monster* monster = nullptr;
	int monster_amount = 0;

};