#pragma once
using namespace std;
class Creature;
class Monster;
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
	~Creature();//�Ȯɤ���virtual
	Card* card = nullptr;//��ܥd�P
	string name="";
	Card& find_card(int);//int �ǤJ�s��number�A�^�Ǹ�Card reference
	//virtual void move() = 0;
	//virtual void attack() = 0;
	void heal(int);//�W�[��q(���W�L�̤j)
	void discard_to_hand();//��P��Ҧ��P���^��P�A�����]�t�w�Q�������P(availible == false)
	void check_card();//�L�X�d�P�s��(��P�P��P)�A�s���Ѥp��j
	int card_available_amount();//�����d�P��(��P��+��P)
	int card_hand_amount();//�i�Υd�P��
	int card_throw_amount();//��P���
	virtual void print() {}//�Ƨǫ᪺�C�L
	virtual void action() {}//���
	Card use_card[2];//�Y���Ǫ��h�u���@�i�d
	int life_value=0;//�ثe��q
	int max_life_value = 0;//�̤j��q
	int card_amount=0;//�i��d�P�ƶq
	int card_total =0;//�`�d�P�ƶq
	char code=0;//�N��
	//int TmpAgility=0;//�ӽ��ӱ��ȡA�w�Q�W�誺��ܥd�P���N
	//int TmpShield = 0;//�ӽ��@�ҭ�
	Coord position = {-1,-1};
	int team_num = 0;//����s���A���⬰0�A�Ǫ���1

};


