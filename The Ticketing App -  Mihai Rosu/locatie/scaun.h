#pragma once

#include "../fisier.h"

#include <iostream>

using namespace std;

class Scaun : public Fisier {
private:
	int codificare;
	bool ocupat;

public:
	Scaun();
	Scaun(bool);
	~Scaun();

	bool getOcupat();
	int getCodificare();

	void setOcupat(bool);
	void setCodificare(int);

	void scriereInFisierText(fstream&) override;
	void citireDinFisierText(fstream&) override;

	void scriereInFisierBinar(fstream&) override;
	void citireDinFisierBinar(fstream&) override;

	Scaun operator!();
	operator bool();

	friend istream& operator>>(istream&, Scaun&);
	friend ostream& operator<<(ostream&, Scaun&);
};