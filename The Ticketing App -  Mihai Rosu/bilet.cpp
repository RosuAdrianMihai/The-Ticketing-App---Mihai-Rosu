#include "bilet.h"

#include <string>

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

Bilet::Bilet():unique_id(generate_id(nrSecvente, counter_bilete, nrStart)) {
	this->pretBilet = 0;
	this->nume_participant = "Anonim";
	this->locatie = Locatie();
	this->eveniment = Eveniment();

	counter_bilete += 1;
}

Bilet::Bilet(int pretBilet, string nume_participant, Locatie& l, Eveniment& ev, string denumireZona, int randAles, int locAles) : unique_id(generate_id(nrSecvente, counter_bilete, nrStart)) {
	if (pretBilet > 0) {
		this->pretBilet = pretBilet;
	}
	else {
		this->pretBilet = 0;
	}

	this->nume_participant = nume_participant;
	this->locatie = l;
	this->eveniment = ev;

	Zona* zoneLocatie = l.getZone();

	int indexZona = 0;
	bool existaZona = false;
	int nrRanduriZona = 0;
	int nrLocuriRand = 0;
	bool existaScaunLiber = false;

	for (int i = 0; i < l.getNumarZone(); i++) {
		if (zoneLocatie[i].getDenumire() == denumireZona) {
			existaZona = true;
			indexZona = i;

			this->denumireZona = zoneLocatie[i].getDenumire();
			nrRanduriZona = zoneLocatie[i].getNumarRanduri();

			Rand randSelectat = zoneLocatie[i].getRand(randAles - 1);

			Scaun* scauneLibere = randSelectat.getScauneDisponibile();
			for (int j = 0; j < randSelectat.getNumarScauneLibere(); j++) {
				if (scauneLibere[j].getCodificare() == locAles) {
					existaScaunLiber = true;
				}
			}

			delete[] scauneLibere;
		}
	}

	if (existaZona) {
		if (randAles > 0 && randAles <= nrRanduriZona) {
			this->numarRand = randAles;

			if (existaScaunLiber) {
				this->codificareScaun = locAles;

				cout << "----------------------------------" << endl;
				cout << "Bilet generat cu succes" << endl;
				cout << "----------------------------------" << endl;

				l.setScaunOcupat(indexZona, randAles - 1, locAles, true);

				ev.setSumaBani(this->pretBilet);
				ev.setNumarBilete();

				this->eveniment.setSumaBani(this->pretBilet);
				this->eveniment.setNumarBilete();
			}
			else {
				this->codificareScaun = -404;
				cout << "Nu exista scaunul " << locAles << " liber pe randul " << randAles << endl;
			}
		}
		else {
			this->numarRand = -404;
			this->codificareScaun = -404;
			cout << "Nu exista randul" << randAles << " in zona selectata" << endl;
		}
	}
	else {
		this->denumireZona = "INVALID";
		this->numarRand = -404;
		this->codificareScaun = -404;
		cout << "Zona " << denumireZona << " nu exista in locatia " << l.getDenumireLocatie() << endl;
	}

	delete[] zoneLocatie;

	counter_bilete += 1;
}

Bilet::Bilet(int pretBilet, string nume_participant, Locatie& l, Eveniment& ev, int zonaAleasa, int randAles, int locAles) : unique_id(generate_id(nrSecvente, counter_bilete, nrStart)) {
	if (pretBilet > 0) {
		this->pretBilet = pretBilet;
	}
	else {
		this->pretBilet = 0;
	}

	this->nume_participant = nume_participant;
	this->locatie = l;
	this->eveniment = ev;

	if (zonaAleasa > 0 && zonaAleasa <= l.getNumarZone()) {
		Zona* zoneLibere;
		zoneLibere = l.getZoneCuScauneLibere();

		int nrZoneLibere = l.getNumarZoneLibere();

		if (zoneLibere != nullptr && zonaAleasa <= nrZoneLibere) {
			Zona zonaSelectata;
			zonaSelectata = zoneLibere[zonaAleasa - 1];

			this->denumireZona = zonaSelectata.getDenumire();

			int indexZona = l.getIndexZona(zonaSelectata);

			Rand* randuriLibere;
			randuriLibere = zonaSelectata.getRanduriCuScauneLibere();

			int nrRanduriLibere = zonaSelectata.getNumarRanduriLibere();
			
			if (randAles > 0 && randAles <= nrRanduriLibere) {
				Rand randSelectat;
				randSelectat = randuriLibere[randAles - 1];

				this->numarRand = randSelectat.getNumarRand();
				int indexRand = zonaSelectata.getIndexRand(randSelectat);

				Scaun* scauneLibere = randSelectat.getScauneDisponibile();

				int nrScauneLibere = randSelectat.getNumarScauneLibere();

				if (locAles > 0 && locAles <= nrScauneLibere) {
					Scaun scaunSelectat;
					scaunSelectat = scauneLibere[locAles - 1];

					int codificareScaun = scaunSelectat.getCodificare();
					this->codificareScaun = codificareScaun;

					l.setScaunOcupat(indexZona, indexRand, codificareScaun, true);

					ev.setSumaBani(this->pretBilet);
					ev.setNumarBilete();

					this->eveniment.setSumaBani(this->pretBilet);
					this->eveniment.setNumarBilete();

					cout << "---------------------------------" << endl;

					cout << "Bilet generat cu succes!" << endl;

					cout << "---------------------------------" << endl;
				}
				else {
					cout << "Nu exista locul liber cu numarul " << locAles << endl;
				}
				delete[] scauneLibere;
			}
			else {
				cout << "Nu exista randul liber cu numarul " << randAles << endl;
			}
			delete[] randuriLibere;
		}
		else {
			cout << "Nu exista zona libera cu numarul " << zonaAleasa << endl;
		}

		delete[] zoneLibere;
	}
	else {
		cout << "Zona aleasa nu exista" << endl;
	}

	counter_bilete += 1;
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

void Bilet::scriereInFisierText(fstream& fisier) {
	fisier << this->unique_id << endl;
	fisier << this->pretBilet << endl;
	fisier << this->nume_participant << endl;

	Fisier* f;
	f = &(this->locatie);
	f->scriereInFisierText(fisier);

	fisier << this->denumireZona << endl;
	fisier << this->numarRand << endl;
	fisier << this->codificareScaun << endl;

	f = &(this->eveniment);
	f->scriereInFisierText(fisier);
}

void Bilet::citireDinFisierText(fstream& fisier) {
	fisier >> this->unique_id;
	fisier >> this->pretBilet;

	fisier.ignore();
	getline(fisier, this->nume_participant);

	Fisier* f;
	f = &(this->locatie);
	f->citireDinFisierText(fisier);

	fisier.ignore();
	getline(fisier, this->denumireZona);

	fisier >> this->numarRand;
	fisier >> this->codificareScaun;

	f = &(this->eveniment);
	f->citireDinFisierText(fisier);
}

void Bilet::scriereInFisierBinar(fstream& fisier) {
	int nrCaractereID = this->unique_id.length();

	fisier.write((char*)&nrCaractereID, sizeof(nrCaractereID));
	fisier.write(unique_id.c_str(), nrCaractereID + 1);

	fisier.write((char*)&pretBilet, sizeof(pretBilet));

	int nrCaractereNumeParticipant = this->nume_participant.length();

	fisier.write((char*)&nrCaractereNumeParticipant, sizeof(nrCaractereNumeParticipant));
	fisier.write(nume_participant.c_str(), nrCaractereNumeParticipant + 1);

	Fisier* f;

	f = &(this->locatie);
	f->scriereInFisierBinar(fisier);

	int nrCaractereDenumireZona = this->denumireZona.length();

	fisier.write((char*)&nrCaractereDenumireZona, sizeof(nrCaractereDenumireZona));
	fisier.write(denumireZona.c_str(), nrCaractereDenumireZona + 1);

	fisier.write((char*)&numarRand, sizeof(numarRand));
	fisier.write((char*)&codificareScaun, sizeof(codificareScaun));

	f = &(this->eveniment);
	f->scriereInFisierBinar(fisier);
}

void Bilet::citireDinFisierBinar(fstream& fisier) {
	int nrCaractereID = 0;

	fisier.read((char*)&nrCaractereID, sizeof(nrCaractereID));
	char* sirID = new char[nrCaractereID + 1];

	fisier.read(sirID, nrCaractereID + 1);
	this->unique_id = sirID;

	delete[] sirID;

	fisier.read((char*)&pretBilet, sizeof(pretBilet));

	int nrCaractereNumeParticipant = 0;

	fisier.read((char*)&nrCaractereNumeParticipant, sizeof(nrCaractereNumeParticipant));
	char* sirNumeParticipant = new char[nrCaractereNumeParticipant + 1];

	fisier.read(sirNumeParticipant, nrCaractereNumeParticipant + 1);
	this->nume_participant = sirNumeParticipant;

	delete[] sirNumeParticipant;

	Fisier* f;

	f = &(this->locatie);
	f->citireDinFisierBinar(fisier);

	int nrCaractereDenumireZona = 0;

	fisier.read((char*)&nrCaractereDenumireZona, sizeof(nrCaractereDenumireZona));
	char* sirDenumireZona = new char[nrCaractereDenumireZona + 1];

	fisier.read(sirDenumireZona, nrCaractereDenumireZona + 1);
	this->denumireZona = sirDenumireZona;

	delete[] sirDenumireZona;

	fisier.read((char*)&numarRand, sizeof(numarRand));
	fisier.read((char*)&codificareScaun, sizeof(codificareScaun));

	f = &(this->eveniment);
	f->citireDinFisierBinar(fisier);
}

ostream& operator<<(ostream& out, const Bilet& b) {
	cout << "---------------------------------" << endl;

	out << "ID: " << b.unique_id << endl;
	out << "Pret bilet: " << b.pretBilet << endl;
	out << "Nume participant:  " << b.nume_participant << endl;

	cout << "---------------------------------" << endl;
	out << "Eveniment\n" << b.eveniment << endl;
	cout << "---------------------------------" << endl;

	cout << "---------------------------------" << endl;
	cout << "Zona: " << b.denumireZona << endl;
	cout << "Numar rand: " << b.numarRand << endl;
	cout << "Codificare scaun: " << b.codificareScaun << endl;

	cout << "---------------------------------" << endl;

	return out;
}