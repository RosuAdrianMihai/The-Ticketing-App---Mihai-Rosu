#include "scaun.h"

int id = 1;

Scaun::Scaun(){
	this->codificare = id;
	this->ocupat = false;
	id += 1;
}

Scaun::Scaun(bool ocupat) {
	this->codificare = id;
	this->ocupat = ocupat;
	id += 1;
}

bool Scaun::getOcupat() {
	return this->ocupat;
}

int Scaun::getCodificare() {
	return this->codificare;
}

void Scaun::setOcupat(bool ocupat) {
	this->ocupat = ocupat;
}

void Scaun::setCodificare(int codificare) {
	this->codificare = codificare;
}

Scaun& Scaun::operator=(const Scaun& s) {
	if (this != &s) {
		this->codificare = s.codificare;
		this->ocupat = s.ocupat;

		return *this;
	}
}

Scaun Scaun::operator!() {
	if (this->ocupat == true) {
		this->ocupat = false;
	}
	else {
		this->ocupat = true;
	}

	return *this;
}

Scaun::operator bool() {
	return this->ocupat;
}

istream& operator>>(istream& in, Scaun& s) {
	cout << "Este scaunul ocupat: (0 = NU, 1 = DA)\n";
	in >> s.ocupat;

	cout << endl << "----------------------------------------------" << endl << endl;

	return in;
}

ostream& operator<<(ostream& out, Scaun& s) {
	out << "Codificarea scaunului este: " << s.getCodificare() << endl;
	out << "Scaun ocupat: " << s.getOcupat() << "       (0 = NU, 1 = DA)" << endl;

	return out;
}