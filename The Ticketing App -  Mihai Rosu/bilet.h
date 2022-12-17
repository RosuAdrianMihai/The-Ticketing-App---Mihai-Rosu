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
	static int sumaBani;
	static int numarBilete;

	Bilet();
	Bilet(int, string, const Locatie&, const Eveniment&, int, int, int);

	static int getSumaStransa();

	int getPretBilet();
	string getNumeParticipant();
	Locatie getLocatie();
	Eveniment getEveniment();

	void setPretBilet(int);
	void setNumeParticipant(string);

	friend ostream& operator<<(ostream&, const Bilet&);
};