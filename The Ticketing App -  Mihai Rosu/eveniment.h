#pragma once

#include <iostream>

using namespace std;

class Eveniment {
private:
	string denumire;
	string data;
	string ora;
	int sumaBani = 0;
	int numarBilete = 0;

public:
	Eveniment();
	Eveniment(string, int, int, int, int, int);

	string getDenumire();
	string getData();
	string getOra();
	int getSumaBani();
	int getNumarBilete();

	void setDenumire(string);
	void setData(int, int, int);
	void setOra(int, int);
	void setSumaBani(int);
	void setNumarBilete();

	friend istream& operator>>(istream&, Eveniment&);
	friend ostream& operator<<(ostream&, const Eveniment&);
};