#include "meniu.h"

#include<stdio.h>
#include <string>

Meniu::Meniu() :detinatorAplicatie("Mihai Rosu") {
	this->locatii = nullptr;
	this->bilete = nullptr;
	this->numarLocatii = 0;
	this->numarBilete = 0;
}

Meniu::~Meniu() {
	if (this->locatii != nullptr) {
		delete[] this->locatii;
	}

	if (this->bilete != nullptr) {
		delete[] this->bilete;
	}
}

int Meniu::getNumarBilete() {
	return this->numarBilete;
}

int Meniu::getNumarLocatii() {
	return this->numarLocatii;
}

int Meniu::getNumarEvenimente() {
	return this->evenimente.size();
}

Bilet* Meniu::initializareBilete(string den_fisier) {
	Bilet* initializareBilete = nullptr;

	if (den_fisier.find(".bin") != -1) {

		fstream fisier;
		fisier.open(den_fisier, ios::in | ios::binary);

		if (fisier) {
			fisier.read((char*)&numarBilete, sizeof(numarBilete));
			fisier.read((char*)&numarLocatii, sizeof(numarLocatii));

			if (numarBilete > 0) {
				initializareBilete = new Bilet[numarBilete];
				for (int i = 0; i < numarBilete; i++) {
					initializareBilete[i].citireDinFisierBinar(fisier);
				}
			}

			return initializareBilete;
		}
		else {
			cout << "Fisierul " << den_fisier << " nu exista" << endl;
		}

		fisier.close();
	}
	else if(den_fisier.find(".txt") != -1){
		fstream fisier;
		fisier.open(den_fisier, ios::in);

		if (fisier) {
			fisier >> this->numarBilete;
			fisier >> this->numarLocatii;

			if (numarBilete > 0) {
				initializareBilete = new Bilet[numarBilete];
				for (int i = 0; i < numarBilete; i++) {
					initializareBilete[i].citireDinFisierText(fisier);
				}
			}

			return initializareBilete;
		}
		else {
			cout << "Fisierul " << den_fisier << " nu exista" << endl;
		}

		fisier.close();
	}
	else {
		cout << "Fisierul nu are forma valida. (.txt pt fisier de tip text, .bin pt fisier binar)" << endl;
	}


	return nullptr;
}

void Meniu::meniuNavigareConsola(string den_fisier) {
	string nume_fisier_text;
	string nume_fisier_binar;

	int nrLocatii = 0;
	int nrEvenimente = 0;
	int nrBilete = 0;

	nume_fisier_text = den_fisier + ".txt";
	nume_fisier_binar = den_fisier + ".bin";

	fstream fisier_text;
	fisier_text.open(nume_fisier_text, ios::app);

	fstream fisier_binar;
	fisier_binar.open(nume_fisier_binar, ios::app | ios::binary);

	cout << "Introduce numarul de locatii: ";
	cin >> nrLocatii;

	while (nrLocatii <= 0) {
		cout << "Numarul de locatii trebuie sa fie mai mare decat 0!!!" << endl;
		cout << "Introduce numarul de locatii: ";

		cin >> nrLocatii;
	}

	this->numarLocatii = nrLocatii;

	cout << "Introduce numarul de evenimente: ";
	cin >> nrEvenimente;

	while (nrEvenimente <= 0) {
		cout << "Numarul de evenimente trebuie sa fie mai mare decat 0!!!" << endl;
		cout << "Introduce numarul de evenimente: ";

		cin >> nrEvenimente;
	}

	cout << "Introduce numarul de bilete: ";
	cin >> nrBilete;

	this->numarBilete = nrBilete;

	if (this->bilete != nullptr) {
		delete[] this->bilete;
	}

	this->bilete = new Bilet[numarBilete];

	while (nrBilete <= 0) {
		cout << "Numarul de bilete trebuie sa fie mai mare decat 0!!!" << endl;
		cout << "Introduce numarul de bilete: ";

		cin >> nrBilete;
	}

	if (this->locatii != nullptr) {
		delete[] this->locatii;
	}

	this->locatii = new Locatie[nrLocatii];
	for (int i = 0; i < nrLocatii; i++) {
		cin >> locatii[i];
	}

	for (int i = 0; i < nrEvenimente; i++) {
		Eveniment ev;
		cin >> ev;

		this->evenimente.push_back(ev);
	}

	for (int i = 0; i < nrBilete; i++) {
		int pretBilet;
		string nume_participant;
		int numarLocatie;
		string denumireZona;
		int numarRand;
		int codificareScaun;
		int numarEveniment;

		Fisier* f;

		fisier_text << nrBilete << endl;
		fisier_binar.write((char*)&nrBilete, sizeof(nrBilete));

		fisier_text << nrLocatii << endl;
		fisier_binar.write((char*)&nrLocatii, sizeof(nrLocatii));

		for (int i = 0; i < nrBilete; i++) {
			cout << "Introduce pretul biletului: ";
			cin >> pretBilet;

			while (pretBilet <= 0) {
				cout << "Pretul biletului trebuie sa fie mai mare decat 0";
				cout << "Introduce pretul biletului: ";

				cin >> pretBilet;
			}

			cout << "Introduce numele participantului: ";
			cin >> ws;
			getline(cin, nume_participant);

			cout << "Introduce numarul locatiei la care biletul se va genera: ";
			cin >> numarLocatie;

			while (numarLocatie <= 0 || numarLocatie > nrLocatii) {
				cout << "Nu exista locatia cu numarul " << numarLocatie << endl;
				cout << "Introduce numarul locatiei la care biletul se va genera: ";

				cin >> numarLocatie;
			}

			Locatie locatieAleasa;
			locatieAleasa = this->locatii[numarLocatie - 1];

			cout << "Introduce denumirea zonei la care se va face rezervarea: ";
			cin >> ws;
			getline(cin, denumireZona);

			cout << denumireZona << endl;

			cout << "Introduce numarul randului: ";
			cin >> numarRand;

			cout << "Introduce codificarea scaunului: ";
			cin >> codificareScaun;

			int numarEvenimente = this->evenimente.size();

			cout << "Introduce numarul evenimentului la care biletul se va genera: ";
			cin >> numarEveniment;

			while (numarEveniment <= 0 || numarEveniment > numarEvenimente) {
				cout << "Nu exista locatia cu numarul " << numarEveniment << endl;
				cout << "Introduce numarul evenimentului la care biletul se va genera: ";

				cin >> numarEveniment;
			}

			Eveniment evenimentAles;
			evenimentAles = this->evenimente[numarEveniment - 1];

			Bilet b(pretBilet, nume_participant, locatieAleasa, evenimentAles, denumireZona, numarRand, codificareScaun);
			this->bilete[i] = b;

			f = &(this->bilete[i]);
			f->scriereInFisierText(fisier_text);
			f->scriereInFisierBinar(fisier_binar);
		}
	}

	fisier_text.close();
	fisier_binar.close();

	for (int i = 0; i < nrBilete; i++) {
		cout << "Biletul " << i + 1 << endl;
		cout << this->bilete[i] << endl;
	}
}

void Meniu::afiseazaBilet(Bilet *biletePrimite, int nrBilet) {
	if (nrBilet > 0 && nrBilet <= this->numarBilete && biletePrimite != nullptr) {
		cout << biletePrimite[nrBilet - 1];
	}
	else {
		cout << "Numarul biletului este invalid" << endl;
	}
}