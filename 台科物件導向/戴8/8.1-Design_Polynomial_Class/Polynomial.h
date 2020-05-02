#pragma once
class Polynomial {
private:
	double* coefficient = nullptr;
	int size = 0;
public:
	Polynomial();
	~Polynomial();
	Polynomial(const Polynomial&);//copy
	Polynomial(double*, int);
	Polynomial operator+(const Polynomial&);
	Polynomial operator-(const Polynomial&);
	Polynomial operator*(const Polynomial&);
	Polynomial& operator=(const Polynomial&);
	double& operator[](int);
	friend double evaluate(const Polynomial&, const double&);
	int mySize() {
		return size;
	}

	Polynomial operator+(const double&);
	Polynomial operator-(const double&);
	Polynomial operator*(const double&);

	friend Polynomial operator+(const double&,Polynomial&);
	friend Polynomial operator-(const double&,Polynomial&);
	friend Polynomial operator*(const double&, const Polynomial&);
	void clear_zero() {
		for (int i = size - 1;!coefficient[i];i--, size--);//�q�̰������}�l�ˬd�A�Y��0 size-1�A����0 ����
	}
};

