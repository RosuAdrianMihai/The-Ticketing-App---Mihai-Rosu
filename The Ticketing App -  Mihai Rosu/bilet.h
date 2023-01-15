#pragma once

#include "fisier.h"

#include "locatie/locatie.h"
#include "eveniment.h"

class Bilet : public Fisier {
private:
	string unique_id;
	int pretBilet;
	string nume_participant;
	Locatie locatie;
	string denumireZona;
	int numarRand;
	int codificareScaun;
	Eveniment eveniment;

public:
	Bilet();
	Bilet(int, string, Locatie&, Eveniment&, string, int, int);
	Bilet(int, string, Locatie&, Eveniment&, int, int, int);

	int getPretBilet();
	string getNumeParticipant();
	Locatie getLocatie();
	Eveniment getEveniment();

	void setPretBilet(int);
	void setNumeParticipant(string);

	void scriereInFisierText(fstream&) override;
	void citireDinFisierText(fstream&) override;

	void scriereInFisierBinar(fstream&) override;
	void citireDinFisierBinar(fstream&) override;

	friend ostream& operator<<(ostream&, const Bilet&);
};