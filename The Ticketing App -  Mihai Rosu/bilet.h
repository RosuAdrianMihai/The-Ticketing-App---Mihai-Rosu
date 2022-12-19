#pragma once

#include "locatie/locatie.h"

#include "eveniment.h"

class Bilet {
private:
	const string unique_id;
	int pretBilet;
	string nume_participant;
	Locatie locatie;
	Eveniment eveniment;

public:
	Bilet(int, string, Locatie&, Eveniment&, int, int, int);

	int getPretBilet();
	string getNumeParticipant();
	Locatie getLocatie();
	Eveniment getEveniment();

	void setPretBilet(int);
	void setNumeParticipant(string);

	friend ostream& operator<<(ostream&, const Bilet&);
};