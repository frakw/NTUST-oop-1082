#pragma once
#include <string>
using namespace std;

class Skill {
public:
	Skill():type(-1), value(-1){}
	Skill(string name, int val) : value(val) {
		if (name == "Move") {
			type = 0;
		}
		else if (name == "Attack") {
			type = 1;
		}
		else if (name == "Heal") {
			type = 2;
		}
		else if (name == "Shield") {
			type = 3;
		}
		else {
			type = -1;//skill type error!
		}
	}
	Skill(int type, int val) : value(val) {
		if (type < 0 || type > 3) {
			type = -1;//skill type error!
		}
		else {
			type = type;
		}
	}	
	int type=-1;
	int value=-1;
	string move_step;//�u�b�Ǫ��d�ޯରmove�ɨϥΡA�swasd
};

class Card {//copy constructor
public:
	Card() {};
	Card(const Card& input) {
		*this = input;
	};
	Card(int in_agility, bool mark, Skill* a) : agility(in_agility), rewash_mark(mark), skill_up(a) {}
	Card(int in_agility,bool mark, Skill* a,Skill* b) : agility(in_agility), rewash_mark(mark), skill_up(a), skill_down(b){}
	~Card() {
		if (skill_up != nullptr) {
			delete[] skill_up;
			skill_up = nullptr;
			skill_up_total = 0;
		}
		if (skill_down != nullptr) {
			delete[] skill_down;
			skill_down = nullptr;
			skill_down_total = 0;
		}
	}
	Card& operator=(const Card& input) {
		this->~Card();
		if (input.skill_up_total > 0) {
			this->skill_up_total = input.skill_up_total;
			skill_up = new Skill[skill_up_total];
			for (int i = 0;i < skill_up_total;i++) {
				skill_up[i] = input.skill_up[i];
			}
		}
		if (input.skill_down_total > 0) {
			this->skill_down_total = input.skill_down_total;
			skill_down = new Skill[skill_down_total];
			for (int i = 0;i < skill_down_total;i++) {
				skill_down[i] = input.skill_down[i];
			}
		}
		discard = input.discard;
		number = input.number;
		agility = input.agility;
		rewash_mark = input.rewash_mark;
		return *this;
	}
	bool discard = false;//�O(true)�_(false)�b��P��
	Skill* skill_up = nullptr;
	int skill_up_total = 0;
	Skill* skill_down = nullptr;//�Ǫ��d�S�U�b���Anullptr
	int skill_down_total = 0;
	int number;//�s��
	int agility=0;//�ӱ���
	bool rewash_mark = false;//���~�аO�A����S�����~�аO(false)
};


class Creature {
public:
	Creature() {}
	Creature(string in_name, int val, int in_card_amount) :name(in_name), life_value(val), card_amount(in_card_amount) {
	
		// = new Card[card_amount];
	}
	~Creature() {
		if (card != nullptr) delete[] card;
	}
	Card* card = nullptr;//��ܥd�P
	string name="";
	int life_value=0;
	int card_amount=0;//�i��d�P�ƶq
	int card_total =0;//�`�d�P�ƶq
	char code;//�N��


};


