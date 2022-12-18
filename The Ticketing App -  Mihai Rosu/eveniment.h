#pragma once

#include <iostream>

using namespace std;

class Eveniment {
private:
	string denumire;
	string data;
	string ora;

public:
	static int sumaBani;
	static int numarBilete;

	Eveniment();
	Eveniment(string, int, int, int, int, int);

	string getDenumire();
	string getData();
	string getOra();

	void setDenumire(string);
	void setData(int, int, int);
	void setOra(int, int);

	friend istream& operator>>(istream&, Eveniment&);
	friend ostream& operator<<(ostream&, const Eveniment&);
};