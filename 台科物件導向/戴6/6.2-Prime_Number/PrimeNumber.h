#pragma once
class PrimeNumber {
public:
	int value=1;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();//++�b�e��
	PrimeNumber operator++(int);//++�b�᭱�Aint�@�w�n�[�A�аO��
	PrimeNumber & operator--();//--�b�e��
	PrimeNumber operator--(int);//--�b�᭱�Aint�@�w�n�[�A�аO��
};