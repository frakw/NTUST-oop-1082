#ifndef _Big_Number_H_
#define _Big_Number_H_
#include <string>
#include <vector>
#include <iostream>
/*
�W�d:
1.integer�Pdecimal���u���Ʀr�զ����r��
2.sign�O���t���Atrue�����A0�i�����έt(���v�T�p��)
3.�Y���p�Ƴy���L�k�p��A�|�ǤJerro_message�A���G�|�H��ƭp��Aprint�|�����~�T���A�i�b���Y�ɫe�[�J#define big_number_no_error_message ������ĵ�i�A�Y�n�L�X���e�A�h�A�[�J#define big_number_error_keep_going
*/
class big_number {
public:
	big_number(std::string);//constructor�A�����O�ѩ��U��input������
	big_number();//�ƻ򳣤���
	void print(void) {//inline funtion �L�Xbig_number
#ifndef big_number_no_error_message
		if (error_message.length() > 0) {//�����~��T
			std::cout << error_message;
			error_message.clear();//�L�X�@����������~�T��
			error_message = "";
	#ifndef big_number_error_keep_going			
			return;//error��פ�
	#else
			std::cout << " �H�U�O�h�����i�p�ⳡ�������G:" << std::endl;
	#endif
		}
#endif
		if (integer.length() == 0) {//��Ƭ��Ŧr��ɡA�w�]��0
			std::cout << 0;
		}
		else {
			if (!sign && (integer.length()!=1 || integer[0]!='0')) {//���� -0 bug
				std::cout << "-";
			}
			std::cout << integer;
		}
		if (decimal.length())//�p�G�p�ƪ��׬��s�A����X�p���I
			std::cout << '.' << decimal;
	}
	void print(int);//�j���X�p���I�� int ��A������0
	void input(std::string);//��J�@��string �s�Jbig_number�A�榡:"-12345"�A�e�������t���i�H�K�[�h�ӡA�Ů�۰ʬٲ�
	void input_llint(long long int);//��Jlong long int�s�Jbig_number
	void input_ullint(long long int);//��Junsigned long long int�s�Jbig_number
	void input_ldouble(long double);//��Jdouble�s�Jbig_number
	long long int to_llint();//�^��int�ȡA���줣�B�z
	unsigned long long int to_ullint();//�^��int�ȡA���줣�B�z
	long double to_ldouble();//�^��double��
	void set(bool, std::string, std::string);//�]�wsign,integer,decimal�A�}�o��K��
	void create_fraction();//�Ыؤ��ơA�s�Jnumerator�Pdenominator
	std::vector<big_number> prime_factorization(bool);//�^�ǽ�]�Ƥ��Ѫ��}�C�Atrue�q�p��j �Ϥ�
	bool is_prime();//�ˬd�O�_����ơA�O��true
	void clear_zero();//�M����Ƴ̫e����0 �P�p���I�̫᪺0�A�`��
	void clear(void);//�M���Ҧ�string sign�]��true
	bool sign = true; // 1->���ƻP0 -1->�t��
	char pre_operator = '+';//�Ω��x�s�e�誺operator�A�Ȯɥ����갵
	std::string integer = "";//��Ƴ���
	std::string decimal = "";//�p�Ƴ���
	std::string error_message = "";//���~��T�A�Y�s�b�h���C�L�Ʀr
	std::string numerator = "";//���l�A�������k�|�ϥΨ�o����T�Aex: 1.0/3.0 * 3 = 1 �ӫD 0.9999...
	std::string denominator = "";//�����A�������k�|�ϥΨ�o����T
};

big_number big_number_formula(std::string);//�ǤJ�ƾǦ��A�B�z��J�A�B����y�ܦUfuntion�A�Y�����浲����J�p��A��l�r���P�ťշ|�Q����
big_number big_number_add(big_number,big_number);//�B�z���t���ۦP���B��A���P���y�ܴ�k
big_number big_number_minus(big_number, big_number);//�B�z���t�����P���B��A�ۦP���y�ܥ[�k
big_number big_number_multiply(big_number, big_number);//���k
big_number big_number_divide(big_number, big_number,int);//���k�Aint ���p���I��̤j��ơA�|����²���Ʀs�Jnumerator�Pdenominator
big_number big_number_remainder(big_number, big_number);//���l�ơA�u�A�Ω��ơA���p�Ʒ|�Q�����A�ÿ���J���~�T��
big_number big_number_factorial(big_number);//�����A���p�Ʒ|�ǤJerror message
big_number big_number_power(big_number, big_number);//����A�Y���p�ơA�|call���
big_number big_number_root(big_number,big_number);//���
big_number big_number_gcd(big_number, big_number);//�̤j���]��
big_number big_number_lcm(big_number, big_number);//�̤p������
big_number big_number_pi(int);//�^�ǣk��p���I�� int ��
big_number big_number_euler(int);//�^�Ǧ۵M���ƨ�p���I�� int ��
big_number big_number_sin(big_number,int);//�^��sin�Ȩ�p���I�� int ��
big_number big_number_cos(big_number, int);//�^��cos�Ȩ�p���I�� int ��
big_number big_number_tan(big_number, int);//�^��tan�Ȩ�p���I�� int ��A�Y���s�b�ǤJerror message
int big_number_compare(big_number, big_number);//�j�Ƥ���� a>b ->1   a==b ->0    a<b ->-1
int big_number_compare(std::string,std::string);//�j�Ƥ����(�r�ꪩ) a>b ->1   a==b ->0    a<b ->-1
bool clear_unknown(std::string*);
#endif
