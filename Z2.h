// Bernard Śniegowski

#ifndef Z2_H
#define Z2_H

#include <iostream>
using namespace std;


class Z2 {
public:
	Z2();
	Z2(short int n);
	Z2(const Z2& a);
	operator short int() const;
	void operator=(const Z2& b);
	Z2& operator+=(const Z2& b);
	Z2& operator*=(const Z2& b);
	Z2& operator/=(const Z2& b);

	/* FRIENDS */
	friend Z2 operator+(const Z2& a, const Z2& b);
	friend Z2 operator*(const Z2& a, const Z2& b);
	friend Z2 operator/(const Z2& a, const Z2& b);
	friend ostream& operator<<(ostream& out, const Z2& a);
	
private:
	short int n;
};

#endif