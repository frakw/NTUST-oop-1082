#pragma once
#include "Coord.h"
#include <utility>
#include <string>
class Character;//���iinclude ���Y�ɡA�|�X�{��|�����W�d-���]��int
class Monster;//���iinclude ���Y�ɡA�|�X�{��|�����W�d-���]��int
using namespace std;

class Map {
public:
	Map();
	Map(int in_row, int in_col);
	~Map();
	void set(string input);
	int row=0, col=0;
	char** body = nullptr;
	Coord start_pos[4];//�i���m
	Character* player = nullptr;
	Monster* enemy = nullptr;
};