#pragma once
using namespace std;
class Skill {
public:
	Skill();
	Skill(string name, int val);
	Skill(int in_type, int val);
	void set(string name, int val);
	int type=-1;
	int value=-1;
	int range = -1;//attack�ɤ~�Ψ�
	string move_step;//�u�b�Ǫ��d�ޯରmove�ɨϥΡA�swasd
};

class Card {//copy constructor
public:
	Card();
	Card(const Card& input);
	Card(int in_agility, bool mark, Skill* a);
	Card(int in_agility, bool mark, Skill* a, Skill* b);
	~Card();
	Card& operator=(const Card& input);
	bool available=true;//���d�O�_�٥i�Q�ϥ�
	bool discard = false;//�O(true)�_(false)�b��P��
	Skill* skill_up = nullptr;
	int skill_up_amount = 0;
	Skill* skill_down = nullptr;//�Ǫ��d�S�U�b���Anullptr
	int skill_down_amount = 0;
	int number=0;//�s��
	int agility=0;//�ӱ���
	bool rewash_mark = false;//���~�аO�A����S�����~�аO(false)
};


class Creature {
public:
	Creature();
	Creature(string in_name, int val, int in_card_amount);
	~Creature();
	Card* card = nullptr;//��ܥd�P
	string name="";
	int life_value=0;
	int card_amount=0;//�i��d�P�ƶq
	int card_total =0;//�`�d�P�ƶq
	char code=0;//�N��
	Coord position = {-1,-1};

};


