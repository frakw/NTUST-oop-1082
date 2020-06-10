#include "Gloom_Haven.h"
#include "Input.h"
using namespace std;

int character_amount_input() {
	cout << "�п�J�X������ƶq:" << endl;//���n
	string input;
	regex reg(R"(^[+]?\d+$)");
	int result = 2;
check:
	mygetline(cin, input);
	while (!regex_match(input, reg)) {
		cout << err << endl;
		mygetline(cin, input);
	}
	result = stoi(input);
	if (result > 4 || result < 2) {
		cout << "character amount should be 2~4 , input again!" << endl;
		goto check;
	}
	return result;
}
void character_data_input(Character& life, Character* db, int total_chr, char code) {//brute 0 1 2 3 4 5
	prompt_input("�п�J" << code << "���������O�P�_�l��P�s��(��:brute 0 1 2 3 4 5)");
	string number;
	int db_index = -1;
	string input;
name_input:
	db_index = -1;
	mygetline(cin, input);
	stringstream ss(input);
	ss >> life.name;
	for (int i = 0;i < total_chr;i++) {
		if (db[i].name == life.name) {
			db_index = i;
			break;
		}
	}
	if (db_index == -1) {
		cout << "can't find this name in character database" << endl;
		goto name_input;
	}
	int count = 0;
	while (!ss.eof()) {
		ss >> number;
		if (is_num(number)) {
			count++;
		}
		else {
			cout << err << endl;
			goto name_input;
		}
	}
	if (count != db[db_index].card_amount) {
		cout << err << endl;
		goto name_input;
	}
	//�����ˬd�A�}�l�s�J
	stringstream final(input);//�ѤFŪ�W�r
	final >> life.name;//�ѤFŪ�W�r
	life = db[db_index];
	life.code = code;
	for (int i = 0;i < life.card_amount;i++) {
		int num;
		final >> num;

		int m;
		for (m = 0; m < db[db_index].card_total;m++) {
			if (num == db[db_index].card[m].number) {
				life.card[i] = db[db_index].card[m];
				break;
			}
		}
		int j;
		for (j = 0;j < i;j++) {//�ˬd�P���e�d�P�O�_����
			if (num == life.card[j].number) {
				break;
			}				
		}
		if (m == db[db_index].card_total || j!=i) {
			cout << err << endl;
			goto name_input;
		}
	}
}

bool is_num(string input) {
	regex reg(R"([+-]?\d+$)");
	return regex_match(input,reg);
}

void open_file(fstream& file, string filename) {//map1.txt
	file.open(filename, ios::in);
	while(!file.is_open()) {
		cout <<'"'<<filename<<'"'<<" file open error please input file path again:";
#ifdef command_line
		exit(1);
#endif
		mygetline(cin, filename);
		file.open(filename, ios::in);
	}
}

string wasd() {
	prompt_input("�п�Jwasd�զ������ʫ��O��e");
	regex reg(R"(^[wasd]+$)");
	string input;
	mygetline(cin, input);
	while(!regex_match(input, reg) && input != "e") {
		cout << err << endl;
		mygetline(cin, input);
	}
	return input;
}
string character_card_choose() {//A 0 3 B -1�Abool�^��false�N��check�ο�J���~�A���s��J
	prompt_input("�п�J����N���P��ܥd�P(2�i)�s���A�����J-1(��:A -1)�A��Jcheck��ܤ�P�P��P��");
	regex reg(R"(^[A-Z] [+-]?[0-9]+ [+-]?[0-9]+$)");
	regex sleep(R"(^[A-Z] -1)");
	regex check(R"(^[A-Z] check$)");
	string input;
	mygetline(cin, input);
	while (!regex_match(input, reg) && !regex_match(input,sleep) && !regex_match(input, check)) {
		cout << err << endl;
		mygetline(cin, input);
	}
	return input;
}
string character_card_first_ud() {//�����J�Ĥ@�i�ϥΪ��P�P�W�b���ΤU�b��(2u)
	prompt_input("��J�Ĥ@�i�ϥΪ��P���s���P�W�b���ΤU�b��(��:2u)");
	regex reg(R"(^[+-]?\d+[ud]$)");
	string input;
	mygetline(cin, input);
	while (!regex_match(input, reg) && input!="check") {
		cout << err << endl;
		mygetline(cin, input);
	}
	return input;
}

int getline_int() {
	regex int_check(R"([+-]?[0-9]*)");
	string in;
	mygetline(cin, in);
	while (!regex_match(in, int_check)) {
		cout << err << endl;
		mygetline(cin, in);
	}
	return stoi(in);
}

char getline_char() {
	string ch;
	mygetline(cin, ch);
	while (ch.length() != 1 ) {
		cout << err << endl;
		mygetline(cin, ch);
	}
	return ch[0];
}