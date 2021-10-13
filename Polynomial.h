// Bernard Śniegowski

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
using namespace std;


class Polynomial {
public:
	unsigned int deg;
	Z2* t;
	Polynomial();
	Polynomial(unsigned int deg, Z2* t);
	Polynomial(const Polynomial& p);
	void operator=(const Polynomial& p);
	~Polynomial();
	Z2 operator[](unsigned int i) const;
	Polynomial& operator+=(const Polynomial& p);
	Polynomial& operator*=(const Polynomial& p);
	unsigned int degree() const;
	string toString(string xVar);
	bool is_zero() const;
	void clear();
	void update_deg_mod();
};

ostream& operator<<(ostream& out, const Polynomial& p);
Polynomial operator+(const Polynomial& a, const Polynomial&  b);
Polynomial operator*(const Polynomial& a, const Polynomial&  b);
void mod(const Polynomial& u, const Polynomial& v, Polynomial& q, Polynomial& r);
Polynomial operator/(const Polynomial& u, const Polynomial& v);
Polynomial operator%(const Polynomial& u, const Polynomial& v);
istream& operator>>(istream& in, Polynomial& p);
string to_stringg(int i);

#endif
