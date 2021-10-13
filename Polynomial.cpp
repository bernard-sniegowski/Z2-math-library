// Bernard Śniegowski

#include <string>
#include <sstream>
#include "Z2.h"
#include "Polynomial.h"
using namespace std;


Polynomial::Polynomial() : deg(0), t(new Z2[deg+1]) { t[0] = 0; }
Polynomial::Polynomial(unsigned int deg, Z2* t) : deg(0) {
	for(int i=0; i<=deg; i++) {
		if(t[i]) this->deg = i;
	}
	this->t = new Z2[this->deg+1];
	for(int i=0; i<=this->deg; i++) {
		this->t[i] = t[i];
	}
}
Polynomial::Polynomial(const Polynomial& p) {
	deg = p.degree();
	t = new Z2[deg+1];
	for(int i=0; i<=deg; i++) t[i] = p[i];
}

void Polynomial::operator=(const Polynomial& p) {
	deg = p.degree();
	delete[] t;
	t = new Z2[deg+1];
	for(int i=0; i<=deg; i++) t[i] = p[i];
}
Polynomial::~Polynomial() {
	delete[] t;
}
Z2 Polynomial::operator[](unsigned int i) const {
	if(i > deg) {
		cout << "Niepoprawny indeks wielomianu\n";
		return t[0];
	} else return t[i];
}
Polynomial& Polynomial::operator+=(const Polynomial& p) {
	if(p.is_zero()) return *this;
	if(!p.degree()) {
		t[0] += p[0];
		return *this;
	}
	if(p.degree() > deg) {
		Z2* temp = new Z2[p.degree()+1];
		for(int i=0; i<=p.degree(); i++) temp[i] = p[i];
		for(int i=0; i<=deg; i++) temp[i] += t[i];
		delete[] t;
		deg = p.degree();
		t = temp;
	} else if(deg > p.degree()) {
		for(int i=0; i<=p.degree(); i++) t[i] += p[i];
	} else {
		deg = 0;
		for(int i=0; i<=p.degree(); i++) {
			t[i] += p[i];
			if(t[i]) deg = i;
		}
	}
	return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& p) {
	if(this->is_zero() or p.is_zero()) {
		this->clear();
		return *this;
	}
	if(!p.degree() and p[0]==1) return *this;
	unsigned int new_deg = deg + p.degree();
	Z2* temp = new Z2[new_deg+1];
	for(int i=0; i<=new_deg; i++) temp[i] = Z2(0);
	for(int i=0; i<=p.degree(); i++) {
		if(p[i]) {
			for(int j=0; j<=deg; j++) {
				if(t[j]) temp[i+j] += (t[j] * p[i]);
			}
		}
	}
	delete[] t;
	t = temp;
	deg = new_deg;
	return *this;
}
unsigned int Polynomial::degree() const {
	return deg;
}
string Polynomial::toString(string xVar) {
	string s;
	if(!deg) {
		s.append(to_stringg(t[0]));
	}
	else {
		if(t[0]) {
			s.append(to_stringg(t[0]));
			s.append("+");
		}
		for(int i=1; i<deg; i++) {
			if(t[i]) {
				s.append(xVar);
				s.append("^");
				s.append(to_stringg(i));
				s.append("+");
			}
		}
		s.append(xVar);
		s.append("^");
		s.append(to_stringg(deg));
	}
	return s;
}
bool Polynomial::is_zero() const {
	if(!deg && !t[0]) return true;
	else return false;
}
void Polynomial::clear() {
	deg = 0;
	delete[] t;
	t = new Z2[deg+1];
	t[deg] = 0;
}

void Polynomial::update_deg_mod() {
	unsigned int new_deg = 0;
	for(int i=0; i<=deg; i++) {
		if(t[i]) {
			new_deg = i;
		}
	}
	deg = new_deg;
}

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
	Polynomial p = a;
	p += b;
	return p;
}

Polynomial operator*(const Polynomial& a, const Polynomial& b) {
	Polynomial p = a;
	p *= b;
	return p;
}

void mod(const Polynomial& u, const Polynomial& v, Polynomial& q, Polynomial& r) {
	if(!v.degree()) {
		if(!v[0]) cout << "Dzielenie przez zero\n";
		else {
			q = u;
			r.clear();
		}
	} else if(v.degree() > u.degree()) {
		q.clear();
		r = u;
	} else if(v.degree() == u.degree()) {
		r = u;
		r += v;
		Z2* t = new Z2[1];
		t[0] = 1;
		q = Polynomial(0, t);
	}
	else {
		r = u;
		q.clear();
		Z2* q_t = new Z2[u.degree() - v.degree()];
		unsigned int deg = r.degree() - v.degree();
		for(int i=0; i<deg; i++) q_t[i] = Z2(0);
		while(r.degree() < v.degree()) {
			for(int i=0; i<deg; i++) {
				r.t[r.degree()-i] += v[v.degree()-i];
			}
			p.t = t;
			q += p;
			p *= v;
			r += p;
		}
	}
}

Polynomial operator/(const Polynomial& u, const Polynomial& v) {
	if(!v.degree()) {
		if(!v[0]) cout << "Dzielenie przez zero\n";
		return u;
	}
	if(v.degree() > u.degree()) return Polynomial();
	Polynomial q, r;
	mod(u, v, q, r);
	return q;
}

Polynomial operator%(const Polynomial& u, const Polynomial& v) {
	if(!v.degree()) {
		Polynomial r;
		if(!v[0]) cout << "Dzielenie przez zero\n";
		return r;
	}
	if(v.degree() > u.degree()) return u;
	if(v.degree() == u.degree()) {
		Polynomial r;
		r += u;
		r += v;
		return r;
	}
	Polynomial r = u;
	int counter = 0;
	unsigned int deg = v.degree();
	while(r.degree() >= v.degree()) {
		for(int i=0; i<=deg; i++) {
			r.t[r.degree()-i] += v.t[deg-i];
		}
		r.update_deg_mod();
	}
	return r;
}

ostream& operator<<(ostream& out, const Polynomial& p) {
	out << "{";
	for(int i=0; i<p.degree(); i++) out << p[i] << ",";
	out << p[p.degree()] << "}";
	return out;
}

istream& operator>>(istream& in, Polynomial& p) {
	char c;
	in >> c;
	while(c != '{') in >> c;
	unsigned int deg = 0;
	unsigned int size = 4;
	Z2* t = new Z2[2];
	int j = 0;
	while(c != '}') {
		if(j == size) {
			size *= 2;
			Z2* temp = new Z2[size];
			for(int i=0; i<j; i++) temp[i] = t[i];
			delete[] t;
			t = temp;
		}
		in >> c;
		t[j] = (short int)(c);
		if(t[j]) deg = j;
		in >> c;
		j++;
	}
	delete[] p.t;
	p.t = t;
	p.deg = deg;
	return in;
}

string to_stringg(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}