#pragma once

#include "../fisier.h"

#include <iostream>
#include "rand.h"

using namespace std;

class Zona : public Fisier {
private:
	string denumire;
	int numarRanduri;
	int numarRanduriLibere;
	Rand* randuri;

public:
	static int nrZone;

	Zona();
	Zona(int, int);
	Zona(string, int, int);
	Zona(const Zona&);
	~Zona();

	static int getNrZone();

	int getNumarRanduri();
	int getNumarRanduriLibere();
	Rand* getRanduriCuScauneLibere();
	string getDenumire();
	int getCapacitate();
	int getNumarLocuriLibere();
	int getCodificareScaun(int, int);
	Rand getRand(int);
	int getIndexRand(Rand&);

	void setDenumire(string);
	void setLoc(int, int, bool);
	void setNumarRanduriScaune(int, int);

	void scriereInFisierText(fstream&) override;
	void citireDinFisierText(fstream&) override;

	void scriereInFisierBinar(fstream&) override;
	void citireDinFisierBinar(fstream&) override;

	Zona& operator=(const Zona&);
	Rand operator[](int);
	bool operator>(Zona);

	friend istream& operator>>(istream&, Zona&);
	friend ostream& operator<<(ostream&, Zona&);
};