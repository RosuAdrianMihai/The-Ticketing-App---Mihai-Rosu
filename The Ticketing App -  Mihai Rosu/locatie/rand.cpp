#include "rand.h"

int nrRand = 1;

Rand::Rand(){
	this->numarRand = nrRand;
	this->numarScaune = 0;
	this->scaune = nullptr;
	this->numarScauneLibere = 0;

	nrRand += 1;
}

Rand::Rand(int numarScaune){
	this->numarRand = nrRand;

	if (numarScaune > 0) {
		this->numarScaune = numarScaune;
		this->scaune = new Scaun[numarScaune];
		this->numarScauneLibere = numarScaune;

		nrRand += 1;
	}
	else {
		cout << "Introduce un numar mai mare decat 0" << endl;

		this->numarScaune = 0;
		this->scaune = nullptr;
		this->numarScauneLibere = 0;
	}
}

Rand::Rand(const Rand& rand){
	this->numarRand = nrRand;

	if (rand.numarScaune > 0 && rand.scaune != nullptr) {

		this->numarScaune = rand.numarScaune;
		this->scaune = new Scaun[numarScaune];
		this->numarScauneLibere = numarScaune;
	}
	else {
		this->numarScaune = 0;
		this->scaune = nullptr;
		this->numarScauneLibere = 0;
	}
}

Rand::~Rand() {
	if (this->scaune != nullptr) {
		delete[] this->scaune;
		this->scaune = nullptr;
	}
}

int Rand::getNumarRand() {
	return this->numarRand;
}

int Rand::getNumarScaune() {
	return this->numarScaune;
}

int Rand::getCodificareScaun(int indexScaun) {
	if (indexScaun >= 0 && indexScaun < this->numarScaune) {
		return this->scaune[indexScaun].getCodificare();
	}
	else {
		cout << "Nu a fost gasit scaunul" << endl;
		return 0;
	}
}

int Rand::getNumarScauneLibere() {
	return this->numarScauneLibere;
}

Scaun* Rand::getScauneDisponibile() {
	int nrScauneDisponibile = 0;
	Scaun* scauneDisponibile = nullptr;

	for (int i = 0; i < this->numarScaune; i++) {
		if (this->scaune[i].getOcupat() == false) {
			nrScauneDisponibile++;
		}
	}

	if (nrScauneDisponibile > 0) {
		scauneDisponibile = new Scaun[nrScauneDisponibile];


		int index = 0;

		for (int j = 0; j < nrScauneDisponibile; j++) {

			for (int i = index; i < this->numarScaune; i++) {
				index++;

				if (this->scaune[i].getOcupat() == false) {
					int codScaun = this->scaune[i].getCodificare();
					scauneDisponibile[j].setCodificare(codScaun);
					break;
				}
			}

		}

	}

	return scauneDisponibile;
}

void Rand::setNumarScaune(int nrScaune) {
	if (nrScaune > 0) {
		if (this->scaune != nullptr) {
			delete[] this->scaune;
			this->scaune = nullptr;
		}

		this->numarScaune = nrScaune;
		this->scaune = new Scaun[numarScaune];

		this->numarScauneLibere = nrScaune;
	}
	else {
		cout << "Numarul de scaune pe rand trebuie sa fie mai mare decat 0" << endl;
	}
}

void Rand::setScaun(int codificare, bool ocupat) {
	bool stareModificata = false;

	for (int i = 0; i < this->numarScaune; i++) {
		if (codificare == i + 1 && this->scaune[i].getOcupat() != ocupat) {
			this->scaune[i].setOcupat(ocupat);

			stareModificata = true;

			if (ocupat == true) {
				this->numarScauneLibere -= 1;
			}
			else {
				this->numarScauneLibere += 1;
			}
		}
	}

	if (codificare > this->numarScaune || codificare <= 0) {
		cout << "Nu exista scaunul cu codificarea " << codificare << endl;
	}

	if (stareModificata) {
		cout << "Starea scaunului " << codificare << " a fost schimbata din " << !(this->scaune[codificare - 1].getOcupat()) << " in " << ocupat << "   (0 - neocupat, 1 - ocupat)" << endl;
	}
	else {
		cout << "Starea scaunului " << codificare <<" nu a fost schimbata deoarece are deja starea " << ocupat << "   (0 - neocupat, 1 - ocupat)" << endl;
	}
}

Rand& Rand::operator=(const Rand& r) {
	if (this != &r) {
		if (r.numarScaune > 0 && r.scaune != nullptr) {

			if (this->scaune != nullptr) {
				delete[] this->scaune;
				this->scaune = nullptr;
			}

			this->numarRand = r.numarRand;
			this->numarScaune = r.numarScaune;
			this->scaune = new Scaun[numarScaune];
			this->numarScauneLibere = r.numarScauneLibere;

			for (int i = 0; i < this->numarScaune; i++) {
				this->scaune[i] = r.scaune[i];
			}
		}
	}

	return *this;
}

Scaun Rand::operator[](int index) {
	if (index >= 0 && index < this->numarScaune) {
		if (this->scaune != nullptr) {
			Scaun copie = this->scaune[index];

			return copie;
		}
	}

	cout << "Nu exista scaunul de index " << index << endl;

	Scaun s;
	return s;
}

Scaun* Rand::operator!() {
	if (this->numarScaune > 0) {
		int scauneOcupate = this->numarScaune - this->numarScauneLibere;
		
		if (scauneOcupate > 0) {
			Scaun* copie = new Scaun[scauneOcupate];


			int j = 0;
			while(j < scauneOcupate){

				for (int i = 0; i < this->numarScaune; i++) {

					if (this->scaune[i].getOcupat() == true) {
						copie[j] = this->scaune[i];
						j++;
					}
				}
			}

			return copie;
		}
		else {
			cout << "Nu exista scaune ocupate";
			return nullptr;
		}
		
	}
	else {
		cout << "Nu exista scaune pentru a le verifica starea de ocupat/neocupat" << endl;
		return nullptr;
	}
}

istream& operator>>(istream& in, Rand& r){

	int nrScauneCitit = 0;

	while (nrScauneCitit <= 0) {
		cout << "Introduce numar scaune:\n";
		in >> nrScauneCitit;

		if (nrScauneCitit <= 0) {
			cout << "Introduce un numar valid de scaune" << endl;
			cout << "---------------------------------" << endl;
		}
		else {
			r.numarScaune = nrScauneCitit;

			if (r.scaune != nullptr) {
				delete[] r.scaune;
				r.scaune = nullptr;
			}

			r.scaune = new Scaun[r.numarScaune];

			r.numarScauneLibere = r.numarScaune;

			for (int i = 0; i < r.numarScaune; i++) {
				cout << "Adauga informatii pentru scaunul " << i + 1 << endl;
				in >> r.scaune[i];

				if (r.scaune[i].getOcupat() == true) {
					r.numarScauneLibere -= 1;
				}
			}
		}
	}
	

	

	return in;
}

ostream& operator<<(ostream& out, Rand& r) {
	out << endl << "Numar rand: \n" << r.numarRand << endl;
	out << "Numar scaune pe rand:\n" << r.numarScaune << endl;
	out << "Numar scaune libere pe rand:\n" << r.numarScauneLibere << endl;

	if (r.numarScauneLibere > 0) {
		out << "Codurile scaunelor disponibile pe rand sunt: \n";

		Scaun* scauneDisponibile = r.getScauneDisponibile();

		for (int i = 0; i < r.numarScauneLibere; i++) {
			out << scauneDisponibile[i].getCodificare() << "   ";
		}

		delete[] scauneDisponibile;
		scauneDisponibile = nullptr;
	}
	else {
		out << "Nu exista scaune disponibile pe rand\n";
	}
	
	out << endl;

	return out;
}