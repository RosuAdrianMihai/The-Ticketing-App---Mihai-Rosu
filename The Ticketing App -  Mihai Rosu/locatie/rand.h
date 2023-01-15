#pragma once

#include "../fisier.h"

#include <iostream>
#include "scaun.h"

using namespace std;

class Rand : public Fisier {
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
	void setNumarRand(int);

	void scriereInFisierText(fstream&) override;
	void citireDinFisierText(fstream&) override;

	void scriereInFisierBinar(fstream&) override;
	void citireDinFisierBinar(fstream&) override;

	Rand& operator=(const Rand&);
	Scaun operator[](int index);
	Scaun* operator!();

	friend istream& operator>>(istream&, Rand&);
	friend ostream& operator<<(ostream&, Rand&);
};