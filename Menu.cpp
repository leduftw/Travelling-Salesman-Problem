
#include "Menu.h"

ostream& operator<<(ostream &os, const Menu &m) {
	os << "Izaberite jednu od sledecih opcija:\n";
	os << "1. Unesite parametre problema\n";
	os << "2. Prikazi matricu tezina\n";
	os << "3. Izaberite metodu za resavanje\n";
	os << "4. Kraj rada\n\n";
	return os;
}

void Menu::printWaysToSolve() {
	cout << "1. Pronalazenje optimalnog resenja generisanjem svih permutacija\n";
	cout << "2. Izbor slucajnog puta\n";
	cout << "3. Biranje najblizeg cvora iz tekuceg cvora\n";
	cout << "4. Biranje najdaljeg cvora iz tekuceg cvora\n";
	cout << "5. Biranje k-tog najblizeg cvora iz tekuceg cvora\n";
	cout << "6. 3-optimalna heuristika\n\n";
}

void Menu::inputForMatrix() {
	cout << "Izaberite jednu od sledecih opcija:\n";
	cout << "1. Automatsko stvaranje matrice tezina sa slucajnim vrednostima\n";
	cout << "2. Unos matrice tezina\n";
	cout << "3. Ucitavanje matrice tezina iz fajla\n\n";
}

