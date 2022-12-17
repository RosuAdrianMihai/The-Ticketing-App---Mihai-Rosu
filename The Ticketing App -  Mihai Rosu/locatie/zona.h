#pragma once

#include <iostream>

#include "rand.h"

using namespace std;

class Zona {
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

	void setDenumire(string);
	void setLoc(int, int, bool);
	void setNumarRanduriScaune(int, int);

	Zona& operator=(const Zona&);
	Rand operator[](int);
	bool operator>(Zona);

	friend istream& operator>>(istream&, Zona&);
	friend ostream& operator<<(ostream&, Zona&);
};