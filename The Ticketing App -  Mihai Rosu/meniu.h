#pragma once

#include "bilet.h"

#include <vector>

class Meniu : public Bilet{
private:
	vector<Eveniment> evenimente;
	Locatie* locatii;
	Bilet* bilete;
	int numarLocatii;
	int numarBilete;

	const string detinatorAplicatie;

public:
	Meniu();
	~Meniu();

	int getNumarBilete();
	int getNumarLocatii();
	int getNumarEvenimente();
	Bilet* initializareBilete(string);

	void meniuNavigareConsola(string);
	void afiseazaBilet(Bilet*, int nrBilet);
};