#pragma once
#include<string>
#include<ctype.h>
#include<iostream>
#include<vector>
using namespace std;
class Form
{
private:

public:
	string word,name;
	vector<string> output;
	void SetInputWord(string inputWord);//�]�wInput
	void ProcessInputWord();//�B�z Input ����T
	void SetFileName(string fileName);//�]�w�ɮצW��
	void Load_CompareWord();//Ū�ɨåB���
	void PrintFoundWords();//�L�X�ŦX���r
};
