// Bernard Śniegowski

#include "Z2.h"
using namespace std;


Z2::Z2() : n(0) {}
Z2::Z2(short int n) : n(n%2) {
	if(this->n < 0) this->n += 2;
}
Z2::Z2(const Z2& a) {
	n = a.n;
}
Z2::operator short int() const {
	return n;
}
Z2& Z2::operator+=(const Z2& b) {
	if(b.n) n = !n;
	return *this;
}
Z2& Z2::operator*=(const Z2& b) {
	if(!b.n) n = 0;
	return *this;
}
Z2& Z2::operator/=(const Z2& b) {
	if(!b.n) cout << "Dzielenie przez zero\n";
	return *this;
}

void Z2::operator=(const Z2& b) { this->n = b.n; }

Z2 operator+(const Z2& a, const Z2& b) { return Z2(a.n+b.n); }
Z2 operator*(const Z2& a, const Z2& b) { return Z2(a.n*b.n); }
Z2 operator/(const Z2& a, const Z2& b) {
	if(!b.n) {
		cout << "Dzielenie przez zero\n";
		return a;
	}
	else return Z2(a.n/b.n);
}
ostream& operator<<(ostream& out, const Z2& a) {
	out << a.n;
	return out;
}