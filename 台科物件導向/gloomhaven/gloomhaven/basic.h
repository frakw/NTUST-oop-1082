#pragma once
using namespace std;
class Creature;
class Monster;
class Map;


class Skill {
public:
	Skill();
	Skill(string name, int val);
	Skill(int in_type, int val);
	Skill(const Skill&);
	Skill& operator=(const Skill&);
	void set(string name, int val);
	int type=-1;//0 move 1 attack 2 heal 3 shield
	int value=-1;//�ޯ�ƭ�
	int range = 0;//attack�ɤ~�Ψ�Arange 0 1�ĪG�ҬۦP�A��0�O���w����ԩǡA�Lprint�ɷ|���P�A����range�w�]��1(�����ݩ󻷵{)
	string move_step="";//�u�b�Ǫ��d�ޯରmove�ɨϥΡA�swasd
};

class Card {
public:
	Card();
	Card(const Card& input);//copy constructor�A�]��skill�|���ѼƶǨ�funtion��
	Card(int in_agility, bool mark, Skill* a);
	Card(int in_agility, bool mark, Skill* a, Skill* b);
	~Card();
	Card& operator=(const Card& input);

	bool available=true;//���d�O�_�٥i�Q�ϥ�(����)
	bool discard = false;//�O(true)�_(false)�b��P��

	Skill* skill_up = nullptr;//�d�P�W�b���ޯ�}�C�Y���СA�Ǫ��d����T���s�b�o
	int skill_up_amount = 0;//�d�P�W�b���ޯ��

	Skill* skill_down = nullptr;//�d�P�U�b���ޯ�}�C�Y���СA�Ǫ��d�S�U�b���Anullptr
	int skill_down_amount = 0;//�d�P�U�b���ޯ��

	int number=0;//�s��
	int agility=0;//�ӱ���
	bool rewash_mark = false;//���~�аO�A����S�����~�аO(false)
};


class Creature {
public:
	Creature();
	~Creature();
	Card* card = nullptr;//��ܥd�P
	string name="";
	Card& find_card(int);//int �ǤJ�s��number�A�^�Ǹ�Card reference
	void move(string,int);//int���̤j�B�ơAerror move���ˬd�A�u�A�Ω󨤦�(�Ǫ�move��int�i�H�K��J)
	void heal(int);//�W�[��q(���W�L�̤j)�A���n�baction�H�~���a��I�s
	void shield(int);//�W�[�@�ҭȡA���n�baction�H�~���a��I�s�Aint��������
	void be_attack(char,int);//�Q�����ɩI�s�Achar�������̥N���A��X�@�һP�Ѿl��q
	void discard_to_hand();//��P��Ҧ��P���^��P�A�����]�t�w�Q�������P(availible == false)
	void check_card();//�L�X�d�P�s��(��P�P��P)�A�s���Ѥp��j
	int card_available_amount();//�����d�P��(��P��+��P)
	int card_hand_amount();//�i�Υd�P��
	int card_discard_amount();//��P���
	bool card_in_hand(int);//�ǤJ�s���A�^�ǸӵP�O���O��P�Aerror handling��
	bool card_in_discard(int);//�ǤJ�s���A�^�ǸӵP�b���b��P��Aerror handling��
	virtual void print()/*�Ƨǫ᪺�C�L*/ { cout << "virtual error" << endl; }
	virtual void action(bool) /*��ʡAbool��debug_mode*/{ cout << "virtual error" << endl; }
	virtual void round_end(bool) /*�^�X���ⶥ�q�A�Ӧ^�X�����᪺����(���]�ƭ�)*/{ cout << "virtual error" << endl; }
	void check();//�����ʫe�A��Jcheck�A�n�C�X�Ҧ�����P�Ǫ���hp�P���m��
	Card use_card[2];//�Y���Ǫ��h�u���@�i�d�A�s�buse_card[0]
	int life_value=0;//�ثe��q
	int max_life_value = 0;//�̤j��q
	int card_amount=0;//�i��d�P�ƶq
	int card_total =0;//���`�d�P�ƶq(��Ʈw�ɨϥ�)�A�C���ɤ��v�T
	char code=0;//�N��
	int TmpShield = 0;//�ӽ��@�ҭ�
	Coord position = {-1,-1};
	int team_num = 0;//����s���A���⬰0�A�Ǫ���1
	Map* map = nullptr;
	bool finished_choose = false;//�Ӧ^�X�O�_������P�ο�ܪ���
};


