#include "bilet.h"

#include <string>

int Bilet::sumaBani = 0;
int Bilet::numarBilete = 0;

string generate_id(int nrSecvente, int counter, string nrStart){
	string id;

	int lungime_id = 0;
	
	int indexNrStart = 0;
	int lungimeNrStart = nrStart.length();

	while (lungime_id < nrSecvente) {
		string sir_cifre;

		if (indexNrStart == lungimeNrStart) {
			indexNrStart = 0;
		}

		sir_cifre = to_string(counter * 5 + 2) + nrStart[indexNrStart];

		id += sir_cifre;

		lungime_id = id.length();

		indexNrStart += 1;
	}

	return id;
}

int nrSecvente = 4;
int counter_bilete = 1;
string nrStart = "123456789";

Bilet::Bilet() : unique_id(generate_id(nrSecvente, counter_bilete, nrStart)) {
	counter_bilete += 1;

	this->nume_participant = "";
	this->pretBilet = 0;

	Bilet::numarBilete += 1;
}

Bilet::Bilet(int pretBilet, string nume_participant, const Locatie& l, const Eveniment& ev, int zonaAleasa, int randAles, int locAles) : unique_id(generate_id(nrSecvente, counter_bilete, nrStart)) {
	counter_bilete += 1;

	if (pretBilet > 0) {
		this->pretBilet = pretBilet;
	}
	else {
		this->pretBilet = 0;
	}
	
	this->nume_participant = nume_participant;

	this->locatie = l;
	this->eveniment = ev;

	Scaun* scauneLibere = (Scaun*)locatie;

	if (scauneLibere != nullptr && zonaAleasa > 0 && zonaAleasa <= this->locatie.getNumarZone()) {

		string denumireZona = this->locatie.getDenumireZona(zonaAleasa - 1);
		int nrLocuriLibere = this->locatie.getNumarLocuriDisponibile();

		if (locAles > 0 && locAles <= nrLocuriLibere) {
			int codificareScaun = scauneLibere[locAles - 1].getCodificare();

			this->locatie.setScaunOcupat(zonaAleasa - 1, randAles - 1, codificareScaun, true);


			Scaun scaunAles;

			for (int i = 0; i < nrLocuriLibere; i++) {
				if (scauneLibere[i].getCodificare() == locAles) {
					scaunAles = scauneLibere[i];
					scaunAles.setOcupat(true);
				}
			}

			if (scaunAles.getOcupat() == true) {
				cout << "---------------------------------" << endl;
				cout << "Bilet generat cu succes" << endl;
				cout << "---------------------------------" << endl;

				cout << "ID: " << this->unique_id << endl;

				cout << "---------------------------------" << endl;
				cout << "Eveniment: " << this->eveniment.getDenumire() << endl;
				cout << "Data: " << this->eveniment.getData() << endl;
				cout << "Ora: " << this->eveniment.getOra() << endl;
				cout << "---------------------------------" << endl;

				cout << "---------------------------------" << endl;
				cout << "Locatie: " << this->locatie.getDenumireLocatie() << endl;
				cout << "Zona: " << denumireZona << endl;
				cout << "Rand: " << randAles << endl;
				cout << "Codificare scaun: " << scaunAles.getCodificare() << endl;
				cout << "---------------------------------" << endl;

				Bilet::sumaBani += this->pretBilet;
				Bilet::numarBilete += 1;
			}
			else {
				cout << "Scaunul este deja ocupat sau randul ales este invalid" << endl;
			}
			
		}
		else {
			cout << "Locul ales nu exista" << endl;
		}
	}
	else {
		cout << "Nu exista locuri libere" << endl;
	}

	delete[] scauneLibere;
	scauneLibere = nullptr;
}

int Bilet::getSumaStransa() {
	return Bilet::sumaBani;
}

int Bilet::getPretBilet() {
	return this->pretBilet;
}

string Bilet::getNumeParticipant() {
	return this->nume_participant;
}

Locatie Bilet::getLocatie() {
	return this->locatie;
}

Eveniment Bilet::getEveniment() {
	return this->eveniment;
}

void Bilet::setPretBilet(int pretBilet) {
	if (pretBilet > 0) {
		this->pretBilet = pretBilet;
	}
}

void Bilet::setNumeParticipant(string nume_participant) {
	if (nume_participant.length() > 0) {
		this->nume_participant = nume_participant;
	}
}

ostream& operator<<(ostream& out, const Bilet& b) {
	cout << "---------------------------------" << endl;

	out << "ID: " << b.unique_id << endl;
	out << "Pret bilet: " << b.pretBilet << endl;
	out << "Nume participant:  " << b.nume_participant << endl;

	cout << "---------------------------------" << endl;
	out << "Locatie\n" << b.locatie << endl;
	cout << "---------------------------------" << endl;

	cout << "---------------------------------" << endl;
	out << "Eveniment\n" << b.eveniment << endl;
	cout << "---------------------------------" << endl;

	cout << "---------------------------------" << endl;

	return out;
}