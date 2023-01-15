#include "eveniment.h"

#include <string>

Eveniment::Eveniment() {
	this->denumire = "Nespecificat";
	this->data = "Nespecificat";
	this->ora = "Nespecificat";
}

Eveniment::Eveniment(string denumire, int zi, int luna, int an, int ora, int minute) {
	this->denumire = denumire;

	if (zi >= 1 && zi <= 31 && luna >= 1 && luna <= 12 && an >= 2022) {
		this->data = to_string(zi) + "/" + to_string(luna) + "/" + to_string(an);
	}
	else {
		this->data = "Nespecificat";
		cout << "Data invalida" << endl;
	}

	if (ora >= 0 && ora < 24 && minute >= 0 && minute < 60) {
		
		string ora_string;
		string minute_string;

		if (ora > 7 && ora < 10) {
			ora_string = "0" + to_string(ora);
		}
		else {
			ora_string = to_string(ora);
		}

		if (minute >= 0 && minute < 10) {
			minute_string = "0" + to_string(minute);
		}
		else {
			minute_string = to_string(minute);
		}


		this->ora = ora_string + ":" + minute_string;
	}
	else {
		this->ora = "Nespecificat";
		cout << "Ora invalida" << endl;
	}
}

string Eveniment::getDenumire() {
	return this->denumire;
}

string Eveniment::getData() {
	return this->data;
}

string Eveniment::getOra() {
	return this->ora;
}

int Eveniment::getSumaBani() {
	return this->sumaBani;
}

int Eveniment::getNumarBilete() {
	return this->numarBilete;
}

void Eveniment::setDenumire(string denumire) {
	this->denumire = denumire;
}

void Eveniment::setData(int zi, int luna, int an) {
	if (zi >= 1 && zi <= 31 && luna >= 1 && luna <= 12 && an >= 2022) {
		this->data = to_string(zi) + "/" + to_string(luna) + "/" + to_string(an);
	}
	else {
		cout << "Data invalida" << endl;
	}
}

void Eveniment::setOra(int ora, int minute) {
	if (ora >= 0 && ora < 24 && minute >= 0 && minute < 60) {

		string ora_string;
		string minute_string;

		if (ora > 7 && ora < 10) {
			ora_string = "0" + to_string(ora);
		}
		else {
			ora_string = to_string(ora);
		}

		if (minute >= 0 && minute < 10) {
			minute_string = "0" + to_string(minute);
		}
		else {
			minute_string = to_string(minute);
		}


		this->ora = ora_string + ":" + minute_string;
	}
	else {
		cout << "Ora invalida" << endl;
	}
}

void Eveniment::setSumaBani(int pretBilet) {
	this->sumaBani += pretBilet;
}

void Eveniment::setNumarBilete() {
	this->numarBilete += 1;
}
void Eveniment::scriereInFisierText(fstream& fisier) {
	fisier << this->denumire << endl;
	fisier << this->data << endl;
	fisier << this->ora << endl;
	fisier << this->sumaBani << endl;
	fisier << this->numarBilete << endl;
}

void Eveniment::citireDinFisierText(fstream& fisier) {
	fisier >> this->denumire;
	fisier >> this->data;
	fisier >> this->ora;
	fisier >> this->sumaBani;
	fisier >> this->numarBilete;
}

void Eveniment::scriereInFisierBinar(fstream& fisier) {
	int nrCaractereDenumire = this->denumire.length();

	fisier.write((char*)&nrCaractereDenumire, sizeof(nrCaractereDenumire));
	fisier.write(denumire.c_str(), nrCaractereDenumire + 1);

	int nrCaractereData = this->data.length();

	fisier.write((char*)&nrCaractereData, sizeof(nrCaractereData));
	fisier.write(data.c_str(), nrCaractereData + 1);

	int nrCaractereOra = this->ora.length();

	fisier.write((char*)&nrCaractereOra, sizeof(nrCaractereOra));
	fisier.write(ora.c_str(), nrCaractereOra + 1);

	fisier.write((char*)&sumaBani, sizeof(sumaBani));
	fisier.write((char*)&numarBilete, sizeof(numarBilete));
}

void Eveniment::citireDinFisierBinar(fstream& fisier) {
	int nrCaractereDenumire = 0;

	fisier.read((char*)&nrCaractereDenumire, sizeof(nrCaractereDenumire));
	char* sirDenumire = new char[nrCaractereDenumire + 1];

	fisier.read(sirDenumire, nrCaractereDenumire + 1);
	this->denumire = sirDenumire;

	delete[] sirDenumire;

	int nrCaractereData = 0;

	fisier.read((char*)&nrCaractereData, sizeof(nrCaractereData));
	char* sirData = new char[nrCaractereData + 1];

	fisier.read(sirData, nrCaractereData + 1);
	this->data = sirData;

	delete[] sirData;

	int nrCaractereOra = 0;

	fisier.read((char*)&nrCaractereOra, sizeof(nrCaractereOra));
	char* sirOra = new char[nrCaractereOra + 1];

	fisier.read(sirOra, nrCaractereOra + 1);
	this->ora = sirOra;

	delete[] sirOra;

	fisier.read((char*)&sumaBani, sizeof(sumaBani));
	fisier.read((char*)&numarBilete, sizeof(numarBilete));
}

istream& operator>>(istream& in, Eveniment& ev) {
	ev.sumaBani = 0;
	ev.numarBilete = 0;

	cout << "Introduce denumirea evenimentului:\n";

	in >> ws;

	getline(in, ev.denumire);

	int ziTest = 0, lunaTest = 0, anTest = 0;

	while (ziTest < 1 || ziTest > 31) {
		cout << "Introduce ziua in care evenimentul va avea loc:\n";
		in >> ziTest;

		if (ziTest < 1 || ziTest > 31) {
			cout << "Zi invalida, introduceti din nou" << endl;

			cout << "---------------------------------" << endl;
		}
	}

	while (lunaTest < 1 || lunaTest > 31) {
		cout << "Introduce luna in care evenimentul va avea loc:  (1 - Ianuarie  12 - Decembrie)\n";
		in >> lunaTest;

		if (lunaTest < 1 || lunaTest > 12) {
			cout << "Luna invalida, introduceti din nou" << endl;

			cout << "---------------------------------" << endl;
		}
	}

	while (anTest < 2022) {
		cout << "Introduce anul in care evenimentul va avea loc:\n";
		in >> anTest;

		if (anTest < 2022) {
			cout << "An invalid, introduceti din nou" << endl;

			cout << "---------------------------------" << endl;
		}
	}
	
	ev.data = to_string(ziTest) + "/" + to_string(lunaTest) + "/" + to_string(anTest);

	int oraTest = -1, minuteTest = -1;

	while (oraTest < 0 || oraTest > 24) {
		cout << "Introduceti ora la care evenimentul va incepe:\n";
		in >> oraTest;

		if (oraTest < 0 || oraTest > 24) {
			cout << "Ora invalida, introduceti din nou" << endl;

			cout << "---------------------------------" << endl;
		}
	}

	while (minuteTest < 0 || minuteTest > 59) {
		cout << "Introduceti minutele la care evenimentul va incepe:\n";
		in >> minuteTest;

		if (minuteTest < 0 || minuteTest > 59) {
			cout << "Minute invalide, introduceti din nou" << endl;

			cout << "---------------------------------" << endl;
		}
	}

	string ora_string;
	string minute_string;

	if (oraTest > 7 && oraTest < 10) {
		ora_string = "0" + to_string(oraTest);
	}
	else {
		ora_string = to_string(oraTest);
	}

	if (minuteTest >= 0 && minuteTest < 10) {
		minute_string = "0" + to_string(minuteTest);
	}
	else {
		minute_string = to_string(minuteTest);
	}


	ev.ora = ora_string + ":" + minute_string;

	return in;
}

ostream& operator<<(ostream& out, const Eveniment& ev) {
	out << "INFROMATII EVENIMENT" << endl;
	out << "---------------------------------" << endl;

	out << "Denumire: " << ev.denumire << endl;
	out << "Data desfasurarii:  " << ev.data << endl;
	out << "Ora desfasurarii:   " << ev.ora << endl;

	out << "---------------------------------" << endl;

	return out;
}