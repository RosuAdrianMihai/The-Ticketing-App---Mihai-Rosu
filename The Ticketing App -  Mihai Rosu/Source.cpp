#include <iostream>
#include <string>

#include "bilet.h"

using namespace std;

int main() {
	Locatie l;
	Eveniment ev;

	cin >> l;
	cin >> ev;

	// biletul primeste ca parametrii: pretul, numele participantului, obiectul Locatie, obiectul Eveniment, nrZona, nrRand, nrLocAles (din cele libere)

	Bilet b(20, "Rosu Mihai", l, ev, 1, 1, 1);

	cout << b;

	return 0;
}