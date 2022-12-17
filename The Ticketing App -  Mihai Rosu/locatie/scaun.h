#pragma once

#include <iostream>

using namespace std;

class Scaun {
private:
	int codificare;
	bool ocupat;

public:
	Scaun();
	Scaun(bool);

	bool getOcupat();
	int getCodificare();

	void setOcupat(bool);
	void setCodificare(int);

	Scaun& operator=(const Scaun&);
	Scaun operator!();
	operator bool();

	friend istream& operator>>(istream&, Scaun&);
	friend ostream& operator<<(ostream&, Scaun&);
};