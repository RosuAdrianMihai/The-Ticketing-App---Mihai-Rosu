#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class Fisier {
public:
	virtual void scriereInFisierText(fstream&)=0;
	virtual void citireDinFisierText(fstream&)=0;

	virtual void scriereInFisierBinar(fstream&)=0;
	virtual void citireDinFisierBinar(fstream&)=0;
};