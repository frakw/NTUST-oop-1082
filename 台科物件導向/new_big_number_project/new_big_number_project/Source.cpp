#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctype.h>
//#define big_number_no_error_message//�������~�T�����~��B��
#define big_number_error_keep_going//�����~�T���A�L�X���~��B��
//�p�G�W����ӳ��S��define�A�N�|�L�X���~�T���A�òפ�L�X�C
#include "big_number.h"
using namespace std;
int main() {
	//big_number_add((string)"11.2222", (string)"3.32323").print();
	//return 0;
	string temp;
	system("title �j�ƭp��� �䴩�p�ơA���䴩���k  �榡:  1+1 1-1  1*1 �@���u��B�z��Ӽ�");
	while (/*cout << "a= ",*/getline(cin, temp)) {
		big_number a, b;
		//string_big_number_calculate(temp)[0].print();
		//a.input(temp);
		//cout << "b= ";
		//getline(cin, temp);
		//b.input(temp);
		//cout << "a+b = ";big_number_add(a, b).print();cout << '\n';
		//cout << "a-b = ";big_number_minus(a, b).print();cout << '\n';
		//cout << "a*b = ";big_number_multiply(a, b).print();cout <<"\n=========================\n";
		cout << "= ";big_number_formula(temp).print();cout << "\n=========================\n";
	}//231-321
	return 0;
}