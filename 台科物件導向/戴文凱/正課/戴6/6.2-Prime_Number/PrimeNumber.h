#pragma once
class PrimeNumber {
public:
	int value=1;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();//++�b�e���A�[���Ǧۤv
	PrimeNumber operator++(int);//++�b�᭱�Aint�@�w�n�[�A�аO�ΡA�[���ǥ��[���e���ƭ�
	PrimeNumber & operator--();//--�b�e���A��Ǧۤv
	PrimeNumber operator--(int);//--�b�᭱�Aint�@�w�n�[�A�аO�ΡA��ǥ���e���ƭ�
};