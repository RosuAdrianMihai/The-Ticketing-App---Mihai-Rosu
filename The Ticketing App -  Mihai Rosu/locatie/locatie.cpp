#include "locatie.h"

#include <string>

string nume = "Locatia ";
int counter_loc = 1;

string den_loc = nume + to_string(counter_loc);

Locatie::Locatie() {
	this->numarZone = 0;
	this->numarZoneCuScauneLibere = 0;
	this->zone = nullptr;

	this->denumire = den_loc;

	counter_loc += 1;
}

Locatie::Locatie(string denumire, int numarZone) {
	this->denumire = denumire;

	if (numarZone > 0) {
		this->numarZone = numarZone;
		this->numarZoneCuScauneLibere = numarZone;
		this->zone = new Zona[numarZone];

		for (int i = 0; i < numarZone; i++) {
			cin >> this->zone[i];

			if (this->zone[i].getNumarLocuriLibere() == 0) {
				this->numarZoneCuScauneLibere -= 1;
			}
		}
	}
	else {
		this->numarZone = numarZone = 0;
		this->zone = nullptr;
	}
	
}

Locatie::Locatie(const Locatie& l) {
	if (this->numarZone > 0) {
		this->numarZone = l.numarZone;
		this->numarZoneCuScauneLibere = l.numarZoneCuScauneLibere;

		this->zone = new Zona[l.numarZone];

		for (int i = 0; i < this->numarZone; i++) {
			cin >> this->zone[i];

			if (this->zone[i].getNumarLocuriLibere() == 0) {
				this->numarZoneCuScauneLibere -= 1;
			}
		}
	}
	else {
		this->numarZone = 0;
		this->numarZoneCuScauneLibere = 0;
		this->zone = nullptr;

		this->denumire = den_loc;

		counter_loc += 1;
	}
}

Locatie::~Locatie() {
	if (this->zone != nullptr) {
		delete[] this->zone;
		this->zone = nullptr;
	}
}

string Locatie::getDenumireLocatie() {
	return this->denumire;
}

int Locatie::getNumarZone() {
	return this->numarZone;
}

Zona* Locatie::getZoneCuScauneLibere() {
	int nrZoneCuScauneLibere = 0;

	for (int i = 0; i < numarZone; i++) {
		if (this->zone[i].getNumarLocuriLibere() > 0) {
			nrZoneCuScauneLibere += 1;
		}
		else {
			this->numarZoneCuScauneLibere -= 1;
		}
	}

	if (nrZoneCuScauneLibere > 0) {
		Zona* copie = new Zona[nrZoneCuScauneLibere];

		int j = 0;

		while (j < nrZoneCuScauneLibere) {
			for (int i = 0; i < this->numarZone; i++) {
				if (this->zone[i].getNumarLocuriLibere() > 0) {
					copie[j] = this->zone[i];
					j++;
				}
			}
		}

		return copie;
	}
	else {
		return nullptr;
	}
}

int Locatie::getCapacitate() {
	int capacitate = 0;

	if (this->zone != nullptr) {

		for (int i = 0; i < this->numarZone; i++) {
			capacitate += this->zone[i].getCapacitate();
		}
	}

	return capacitate;
}

int Locatie::getNumarLocuriDisponibile() {
	int locuriDisponibile = 0;

	if (this->zone != nullptr) {

		for (int i = 0; i < this->numarZone; i++) {
			int locDisponibileInZona = this->zone[i].getNumarLocuriLibere();

			locuriDisponibile += locDisponibileInZona;
		}
	}

	return locuriDisponibile;
}

int Locatie::getNumarLocuriDisponibileZona(int indexZona) {
	if (indexZona >= 0 && indexZona < this->numarZone) {
		int nrLocuriDisponibileInZona = this->zone[indexZona].getNumarLocuriLibere();

		return nrLocuriDisponibileInZona;
	}
	else return 0;
}

int Locatie::getNumarRanduriDisponibile(int indexZona) {
	int nrRanduriCuScauneDisponibile = 0;

	if (indexZona >= 0 && indexZona < this->numarZone) {
		nrRanduriCuScauneDisponibile = this->zone[indexZona].getNumarRanduriLibere();
	}
	else {
		cout << "Nu exista zona " << indexZona + 1 << "   (Introduce index valid pt zona, ex: index = 0 pt zona 1 din locatie)" << endl;
	}

	return nrRanduriCuScauneDisponibile;
}

Scaun* Locatie::getScauneDisponibileInZona(int indexZona) {
	if (indexZona >= 0 && indexZona < this->numarZone) {
		int nrRanduriCuScauneDisponibile = this->zone[indexZona].getNumarRanduriLibere();

		if (nrRanduriCuScauneDisponibile > 0) {
			Rand* randuriDisponibile = this->zone[indexZona].getRanduriCuScauneLibere();

			int nrScauneDisponibile = 0;
			for (int i = 0; i < nrRanduriCuScauneDisponibile; i++) {
				nrScauneDisponibile += randuriDisponibile[i].getNumarScauneLibere();
			}


			if (nrScauneDisponibile > 0) {
				Scaun* scauneDisponibile = new Scaun[nrScauneDisponibile];

				int index = 0;
				for (int i = 0; i < nrRanduriCuScauneDisponibile; i++) {

					Scaun* scauneDisponibilePeRand = randuriDisponibile[i].getScauneDisponibile();
					int nrScauneDisponibilePeRand = randuriDisponibile[i].getNumarScauneLibere();

					for (int j = 0; j < nrScauneDisponibilePeRand; j++) {
						scauneDisponibile[index] = scauneDisponibilePeRand[j];

						index++;

						if (index == nrScauneDisponibile) {
							break;
						}
					}

					delete[] scauneDisponibilePeRand;
					scauneDisponibilePeRand = nullptr;

					break;
				}

				return scauneDisponibile;
			}
			else {
				return nullptr;
			}
		
		}
		else {
			cout << "Nu exista scaune disponibile" << endl;
			return nullptr;
		}
	}
	else {
		cout << "Nu exista zona " << indexZona + 1 << "   (Introduce index valid pt zona, ex: index = 0 pt zona 1 din locatie)" << endl;
		return nullptr;
	}
}

Rand* Locatie::getRanduriDisponibileInZona(int indexZona) {
	Rand* randuriDisponibile = nullptr;

	if (indexZona >= 0 && indexZona < this->numarZone) {
		randuriDisponibile = this->zone[indexZona].getRanduriCuScauneLibere();
	}
	else {
		cout << "Nu exista zona " << indexZona + 1 << "   (Introduce index valid pt zona, ex: index = 0 pt zona 1 din locatie)" << endl;
	}

	return randuriDisponibile;
}

string Locatie::getDenumireZona(int index) {
	Zona copie;

	if (index >= 0 && index < this->numarZone) {
		copie = this->zone[index];
	}
	else {
		cout << "Nu exista zona cu indexul specificat" << endl;
	}

	return copie.getDenumire();
}

void Locatie::setDenumire(string denumire) {
	this->denumire = denumire;
}

void Locatie::setNumarZone(int numarZone) {
	if (numarZone > 0) {
		if (this->zone != nullptr) {
			delete[] this->zone;
			this->zone = nullptr;
		}

		this->numarZone = numarZone;
		this->zone = new Zona[numarZone];

		for (int i = 0; i < this->numarZone; i++) {
			cin >> zone[i];
		}
	}
	else {
		cout << "Numarul de zone trebuie sa fie mai mare decat 0" << endl;
	}
}

void Locatie::setScaunOcupat(int indexZona, int indexRand, int codificareScaun, bool ocupat) {
	if (indexZona >= 0 && indexZona < this->numarZone) {
		this->zone[indexZona].setLoc(indexRand + 1, codificareScaun, ocupat);

		if (this->zone[indexZona].getNumarLocuriLibere() == 0) {
			this->numarZoneCuScauneLibere -= 1;
		}
	}
	else {
		cout << "Nu a fost gasita zona" << endl;
	}
}

void Locatie::setLocatie(int numarZone){
	if (numarZone > 0) {
		if (this->zone != nullptr) {
			delete[] this->zone;
			this->zone = nullptr;
		}

		this->numarZone = numarZone;
		this->numarZoneCuScauneLibere = numarZone;
		this->zone = new Zona[numarZone];

		for (int i = 0; i < numarZone; i++) {
			cout << "----------------------------------------------" << endl;
			cout << "Zona " << i + 1 << endl;

			cin >> this->zone[i];

			if (this->zone[i].getNumarLocuriLibere() == 0) {
				this->numarZoneCuScauneLibere -= 1;
			}

			cout << endl;
		}
	}
	else {
		cout << "Numarul de zone trebuie sa fie mai mare decat 0" << endl;
	}
}

Locatie& Locatie::operator=(const Locatie& l) {
	if (this != &l) {
		if (l.numarZone > 0 && l.zone != nullptr) {

			if (this->zone != nullptr) {
				delete[] this->zone;
				this->zone = nullptr;
			}

			this->denumire = l.denumire;
			this->numarZone = l.numarZone;
			this->zone = new Zona[numarZone];
			this->numarZoneCuScauneLibere = l.numarZoneCuScauneLibere;

			for (int i = 0; i < numarZone; i++) {
				this->zone[i] = l.zone[i];
			}
		}
	}

	return *this;
}

Zona Locatie::operator[](int index) {
	if (index >= 0 && index < this->numarZone) {

		if (this->zone != nullptr) {
			Zona copie = this->zone[index];

			return copie;
		}
	
	}

	cout << "Nu exista zona de index " << index;

	Zona z;
	return z;
}

Locatie::operator Scaun*() {
	if (this->numarZone > 0 && this->zone != nullptr) {

		int nrScauneLibere = this->getNumarLocuriDisponibile();

		if (nrScauneLibere > 0) {
			Scaun* scauneLibere = new Scaun[nrScauneLibere];

			int index = 0;
			while (index < nrScauneLibere) {

				for (int i = 0; i < this->numarZone; i++) {

					int nrScauneLibereInZona = this->getNumarLocuriDisponibileZona(i);
					Scaun* scauneLibereInZona = this->getScauneDisponibileInZona(i);

					if (scauneLibereInZona != nullptr) {

						for (int j = 0; j < nrScauneLibereInZona; j++) {
							scauneLibere[index] = scauneLibereInZona[j];
							index++;
						}

						delete[] scauneLibereInZona;
						scauneLibereInZona = nullptr;
					}

				}
			}

			return scauneLibere;
		}
		
	}
	else {
		cout << "Nu exista scaune libere in locatie" << endl;
		return NULL;
	}
}

istream& operator>>(istream& in, Locatie& l) {
	cout << "Introduce denumirea locatie:\n";

	in >> ws;

	getline(in, l.denumire);

	int nrZone = 0;
	

	while (nrZone <= 0) {
		cout << "Introduce numarul de zone:\n";
		in >> nrZone;

		if (nrZone > 0) {
			l.numarZone = nrZone;
			l.numarZoneCuScauneLibere = nrZone;

			if (l.zone != nullptr) {
				delete[] l.zone;
				l.zone = nullptr;
			}

			l.zone = new Zona[nrZone];

			for (int i = 0; i < nrZone; i++) {
				in >> l.zone[i];
			}
		}
		else {
			cout << "Numarul de zone trebuie sa fie mai mare decat 0" << endl;
			cout << "---------------------------------" << endl;
		}
	}
	

	return in;
}

ostream& operator<<(ostream& out, const Locatie& l) {
	out << "Denumire locatie:  " << l.denumire << endl;
	out << "Numar zone:   " << l.numarZone << endl;
	out << "Numar zone cu locuri libere:   " << l.numarZoneCuScauneLibere << endl;

	for (int i = 0; i < l.numarZone; i++) {
		out << "---------------------------------" << endl;
		out << "Detalii zona " <<  l.zone[i].getDenumire() << endl;
		out << "---------------------------------" << endl;

		out << l.zone[i] << endl;
	}

	return out;
}