#pragma once
#include <fstream>
#include <string>
using namespace std;
class Gloom_Haven;
class Map;
class Character;
#define err "input error,please input again!"
int character_amount_input();
void character_data_input(Character& life, Character* db, int total_chr,char);//brute 0 1 2 3 4 5
void open_file(fstream&,string);//map1.txt
string wasd();
string character_card_choose();//A 0 3 B -1�Abool�^��false�N��check�ο�J���~�A���s��J
string character_card_first_ud();//�����J�Ĥ@�i�ϥΪ��P�P�W�b���ΤU�b��(2u)

int getline_int();
char getline_char();
bool is_num(string);