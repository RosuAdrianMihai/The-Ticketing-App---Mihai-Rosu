#pragma once

#include <iostream>

#include "scaun.h"

using namespace std;

class Rand {
private:
	int numarRand;
	int numarScaune;
	int numarScauneLibere;
	Scaun* scaune;

public:
	Rand();
	Rand(int);
	Rand(const Rand&);
	~Rand();

	int getNumarRand();
	int getNumarScaune();
	int getCodificareScaun(int);
	int getNumarScauneLibere();
	Scaun* getScauneDisponibile();

	void setNumarScaune(int);
	void setScaun(int, bool);

	Rand& operator=(const Rand&);
	Scaun operator[](int index);
	Scaun* operator!();

	friend istream& operator>>(istream&, Rand&);
	friend ostream& operator<<(ostream&, Rand&);
};