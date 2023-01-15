#pragma once

#include "../fisier.h"

#include <iostream>
#include "zona.h"

using namespace std;

class Locatie : public Fisier {
private:
	string denumire;
	int numarZone;
	int numarZoneCuScauneLibere;
	Zona* zone;

public:
	Locatie();
	Locatie(string, int);
	Locatie(const Locatie&);
	~Locatie();

	string getDenumireLocatie();
	int getNumarZone();
	Zona* getZoneCuScauneLibere();
	int getCapacitate();
	int getNumarLocuriDisponibile();
	int getNumarLocuriDisponibileZona(int);
	int getNumarRanduriDisponibile(int);
	Scaun* getScauneDisponibileInZona(int);
	Rand* getRanduriDisponibileInZona(int);
	string getDenumireZona(int);
	Zona getZona(int);
	int getNumarZoneLibere();
	int getIndexZona(Zona&);
	Zona* getZone();

	void setDenumire(string);
	void setNumarZone(int);
	void setScaunOcupat(int, int, int, bool);
	void setLocatie(int);

	void scriereInFisierText(fstream&) override;
	void citireDinFisierText(fstream&) override;

	void scriereInFisierBinar(fstream&) override;
	void citireDinFisierBinar(fstream&) override;

	Locatie& operator=(const Locatie&);
	Zona operator[](int);
	operator Scaun*();

	friend istream& operator>>(istream&, Locatie&);
	friend ostream& operator<<(ostream&, const Locatie&);
};