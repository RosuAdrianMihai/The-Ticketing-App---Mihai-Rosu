#include "zona.h"

#include <string>

int Zona::nrZone = 0;

string initializare = "A";
int counter = 1;

string den = initializare + to_string(counter);

Zona::Zona() {
	this->numarRanduri = 0;
	this->numarRanduriLibere = 0;
	this->randuri = nullptr;
	this->denumire = den;

	counter += 1;
	den = initializare + to_string(counter);

	Zona::nrZone += 1;
}

Zona::Zona(int numarRanduri, int numarScaune){
	if (numarRanduri > 0 && numarScaune > 0) {
		this->numarRanduri = numarRanduri;
		this->numarRanduriLibere = numarRanduri;
		this->randuri = new Rand[numarRanduri];

		for (int i = 0; i < numarRanduri; i++) {
			this->randuri[i].setNumarScaune(numarScaune);
		}
	}
	else {
		this->numarRanduri = 0;
		this->numarRanduriLibere = 0;
		this->randuri = nullptr;
	}

	this->denumire = den;

	counter += 1;
	den = initializare + to_string(counter);

	Zona::nrZone += 1;
}

Zona::Zona(string denumire, int numarRanduri, int numarScaune){
	if (numarRanduri > 0 && numarScaune > 0) {
		this->numarRanduri = numarRanduri;
		this->numarRanduriLibere = numarRanduri;
		this->randuri = new Rand[numarRanduri];

		for (int i = 0; i < numarRanduri; i++) {
			this->randuri[i].setNumarScaune(numarScaune);
		}
	}
	else {
		this->numarRanduri = 0;
		this->numarRanduriLibere = 0;
		this->randuri = nullptr;
	}

	this->denumire = denumire;

	Zona::nrZone += 1;
}

Zona::Zona(const Zona& z){
		if (z.numarRanduri > 0 && z.randuri != nullptr) {
			
			this->numarRanduri = z.numarRanduri;
			this->numarRanduriLibere = z.numarRanduriLibere;

			this->randuri = new Rand[numarRanduri];

			for (int i = 0; i < this->numarRanduri; i++) {
				this->randuri[i] = z.randuri[i];

				if (z.randuri[i].getNumarScauneLibere() < 0){
					this->numarRanduriLibere -= 1;
				}
			}
		}
		else {
			this->numarRanduri = 0;
			this->numarRanduriLibere = 0;
			this->randuri = nullptr;
		}

		this->denumire = den;

		counter += 1;
		den = initializare + to_string(counter);
}

Zona::~Zona() {
	if (this->randuri != nullptr) {
		delete[] this->randuri;
		this->randuri = nullptr;
	}
}


int Zona::getNrZone() {
	return Zona::nrZone;
}

int Zona::getNumarRanduri() {
	return this->numarRanduri;
}

int Zona::getNumarRanduriLibere() {
	return this->numarRanduriLibere;
}

string Zona::getDenumire() {
	return this->denumire;
}

Rand* Zona::getRanduriCuScauneLibere() {
	if (this->randuri != nullptr && this->numarRanduriLibere > 0){

		Rand* randuriCuScauneLibere = new Rand[numarRanduriLibere];

			int index = 0;
			for (int j = 0; j < this->numarRanduri; j++) {

				if (this->randuri[j].getNumarScauneLibere() > 0) {
					randuriCuScauneLibere[index] = this->randuri[j];
					index++;

					if (index == numarRanduriLibere) {
						break;
					}
				}
			}
		return randuriCuScauneLibere;
	}

	return nullptr;
}


int Zona::getCapacitate() {
	if (this->randuri != nullptr) {
		int capacitate = 0;

		for (int i = 0; i < this->numarRanduri; i++) {
			int nrScaunePeRand = randuri[i].getNumarScaune();
			capacitate += nrScaunePeRand;
		}

		return capacitate;
	}

	return 0;
}

int Zona::getNumarLocuriLibere() {
	if (this->randuri != nullptr) {

		int nrScauneLibere = 0;
		for (int i = 0; i < this->numarRanduri; i++) {
			if (this->randuri[i].getNumarScauneLibere() > 0) {
				nrScauneLibere += this->randuri[i].getNumarScauneLibere();
			}
		}

		return nrScauneLibere;
	}
	else {
		cout << "Nu exista randuri (randurile nu au fost generate)" << endl;
		return 0;
	}
}

int Zona::getCodificareScaun(int indexRand, int indexScaun) {
	if (indexRand >= 0 && indexRand < this->numarRanduri) {
		return this->randuri[indexRand].getCodificareScaun(indexScaun);
	}
	else {
		cout << "Nu a fost gasit randul" << endl;
		return 999999;
	}
}

void Zona::setDenumire(string denumire) {
	this->denumire = denumire;
}

void Zona::setLoc(int numarRand, int codificareScaun, bool ocupat){
	if(numarRand > 0 && numarRand <= this->numarRanduri){

		if (this->randuri != nullptr && this->numarRanduri > 0) {
			int nrScaunePeRand = this->randuri[numarRand - 1].getNumarScaune();

			for (int i = 0; i < nrScaunePeRand; i++) {

				if (this->randuri[numarRand - 1].getCodificareScaun(i) == codificareScaun) {
					this->randuri[numarRand - 1].setScaun(codificareScaun, ocupat);

					if (this->randuri[numarRand - 1].getNumarScauneLibere() == 0) {
						this->numarRanduriLibere -= 1;
					}
				}
			}
		}
	}
	else {
		cout << "Numarul de randuri introdus nu este valid" << endl;
	}
}

void Zona::setNumarRanduriScaune(int numarRanduri, int numarScaune) {
	if (numarRanduri > 0 && numarScaune > 0) {
		if (this->randuri != nullptr) {
			delete[] this->randuri;
			this->randuri;
		}

		this->numarRanduri = numarRanduri;

		this->randuri = new Rand[numarRanduri];

		for (int i = 0; i < numarRanduri; i++) {
			this->randuri[i].setNumarScaune(numarScaune);
		}
	}
}

Zona& Zona::operator=(const Zona& z) {
	if (this != &z) {
		if (z.numarRanduri > 0 && z.randuri != nullptr) {
			this->numarRanduri = z.numarRanduri;

			if (this->randuri != nullptr) {
				delete[] this->randuri;
				this->randuri = nullptr;
			}

			this->randuri = new Rand[z.numarRanduri];
			this->numarRanduriLibere = z.numarRanduriLibere;

			for (int i = 0; i < this->numarRanduri; i++) {
				this->randuri[i] = z.randuri[i];
			}
		}

		this->denumire = z.denumire;
	}

	return *this;
}

Rand Zona::operator[](int index) {
	if (index >= 0 && index < this->numarRanduri) {

		if (this->randuri != nullptr) {
			Rand copie = this->randuri[index];

			return copie;
		}
		
	}

	cout << "Nu exista randul de index " << index << "     (de numar = "  << index + 1 << ")" << endl;

	Rand r;
	return r;
}

bool Zona::operator>(Zona z) {
	int zonaCurentaLocuriLibere = this->getNumarLocuriLibere();
	int zonaDeComparatLocuriLibere = z.getNumarLocuriLibere();

	if (zonaCurentaLocuriLibere > zonaDeComparatLocuriLibere) {
		cout << "Exista mai multe locuri libere in zona " << this->denumire << " decat in zona " << z.denumire << endl;
		return true;
	}
	else {
		cout << "Exista mai multe locuri libere in zona " << z.denumire << " decat in zona " << this->denumire << endl;
		return false;
	}
}

istream& operator>>(istream& in, Zona& z){
	cout << "Introduce denumirea zonei:\n";

	in >> ws;

	getline(in, z.denumire);

	int nrRanduri = 0;	

	while (nrRanduri <= 0) {

		cout << "Introduce numarul de randuri\n";
		in >> nrRanduri;

		if (nrRanduri > 0) {
			z.numarRanduri = nrRanduri;
			z.numarRanduriLibere = nrRanduri;

			if (z.randuri != nullptr) {
				delete[] z.randuri;
				z.randuri = nullptr;
			}

			z.randuri = new Rand[z.numarRanduri];

			cout << "Introduce datele randurilor\n";

			cout << "----------------------------------------------------------------------" << endl;

			for (int i = 0; i < z.numarRanduri; i++) {
				cout << "Randul " << i + 1 << endl;
				in >> z.randuri[i];

				if (z.randuri[i].getNumarScauneLibere() == 0) {
					z.numarRanduriLibere -= 1;
				}
			}
		}
		else {
			cout << "Numarul de randuri trebuie sa fie mai mare decat 0" << endl;
			cout << "---------------------------------" << endl;
		}
	}
		
	return in;
}

ostream& operator<<(ostream& out, Zona& z) {
	out << "Denumire zona:  " << z.denumire << endl;
	out << "Numarul de randuri: " << z.numarRanduri << endl;

	if (z.numarRanduri > 0) {
		for (int i = 0; i < z.numarRanduri; i++) {
			out << "---------------------------------" << endl;
			out << z.randuri[i] << endl;
		}
	}

	return out;
}