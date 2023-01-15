#include <iostream>
#include <string>

#include "meniu.h"

using namespace std;

int main() {
	Meniu meniu;

	string mod_functionare;

	cout << "Selecteaza modul de functionare: ('consola' sau 'fisiere')" << endl;
	cin >> mod_functionare;

	if (mod_functionare == "consola") {
		string den_fisier;

		cout << "Introduce denumirea fisierlui (fara extensie [.txt, .bin])" << endl;
		cin >> den_fisier;

		meniu.meniuNavigareConsola(den_fisier);
	}
	else if (mod_functionare == "fisiere") {
		string den_fisier;

		cout << "Introduce denumirea fisierlui" << endl;
		cin >> den_fisier;

		Bilet* bilete = meniu.initializareBilete(den_fisier);
		int nrBilete = meniu.getNumarBilete();

		if (bilete != nullptr && nrBilete > 0) {
			for (int i = 0; i < nrBilete; i++) {
				cout << "Biletul " << i + 1 << endl;
				cout << bilete[i] << endl;
			}

			delete[] bilete;
		}
	}
	else {
		cout << "Mod de functionare invalid";
		exit (3);
	}

	return 0;
}