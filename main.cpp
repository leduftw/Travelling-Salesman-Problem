
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "CompleteGraph.h"
#include "Menu.h"
#include "Utility.h"
using namespace std;

int main() {

	srand(time(NULL));

	Menu menu;
	CompleteGraph *graph = nullptr;
	Path *path = nullptr;
	bool end = false;
	int n = 0;

	while (!end) {

		int startingVertex, L;
		
		cout << menu;
		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			do {
				cout << "\nBroj cvorova? ";
				cin >> n;
				if (n <= 0)
					cout << "Nedozvoljen broj cvorova. Pokusajte ponovo." << endl;
			} while (n <= 0);

			cout << endl;

			if (graph)
				delete graph;
			graph = new CompleteGraph(n);

			int choice;

			do {
				Menu::inputForMatrix();
				cin >> choice;

				if (choice == 1) {
					int low, high;
					do {
						cout << endl << "Unesite opseg tezina koji moze da se nadje u matrici: ";
						cin >> low >> high;
						if (low > high || low < 0 || high < 0)
							cout << "Uneti su nedozvoljeni parametri. Pokusajte ponovo." << endl;
					} while (low > high || low < 0 || high < 0);

					graph->setMaxNumOfDigits(Utility::numberOfDigits(high) + 1);
					graph->randomWeights(low, high);
					cout << endl;
					//graph->printWeightMatrix();
				}
				else if (choice == 2) {
					cout << endl << "Unesite matricu tezina:\n";
					cin >> *graph;
					cout << endl;
				}
				else if (choice == 3) {
					string name;
					cout << endl << "Unesite ime fajla: ";
					cin >> name;

					ifstream file1;
					// file1.open(name + ".txt");
					file1.open(name); // Korisnik ce intuitivno uneti nazivFajla.txt
				
					if (file1.good()) {
						file1 >> *graph;
						cout << "Matrica je ucitana.\n\n";
					}
					else
						cout << "Greska pri otvaranju fajla! Stavite fajl u isti folder kao i program ili navedite apsolutnu putanju do fajla.\n\n";

				}
				else
					cout << "Nepoznata komanda. Pokusajte ponovo.\n\n";
			} while (choice != 1 && choice != 2 && choice != 3);

			break;

		case 2:
			if (!graph)
				cout << "\nMorate prvo napraviti graf\n\n";
			else {
				cout << endl;
				graph->printWeightMatrix();
			}

			break;

		case 3:
			if (!graph)
				cout << "\nMorate prvo napraviti graf\n\n";
			else {
				int choice;

				do {
					cout << endl;
					Menu::printWaysToSolve();
					cin >> choice;
					cout << endl;

					switch (choice) {
					case 1:
						if (path)
							delete path;
						path = graph->optimalPath();
						cout << *path;

						break;

					case 2:
						if (path)
							delete path;
						path = graph->randomPath();
						cout << *path;

						break;

					case 3: case 4:
						if (path)
							delete path;
						do {
							cout << "Pocetni cvor? ";
							cin >> startingVertex;
							if (startingVertex < 1 || startingVertex > n)
								cout << "Pocetni cvor mora biti u opsegu [1, " << n << "]. Pokusajte ponovo.\n";
						} while (startingVertex < 1 || startingVertex > n);

						cout << endl;

						if (choice == 3)
							path = graph->nearestNeighbour(startingVertex);
						else
							path = graph->furthestNeighbour(startingVertex);

						cout << *path;

						break;

					case 5:
						if (path)
							delete path;
						int k;
						do {
							cout << "Unesite pocetni cvor i vrednost za k: ";
							cin >> startingVertex >> k;
							if (startingVertex < 1 || startingVertex > n)
								cout << "Pocetni cvor mora biti u opsegu [1, " << n << "]. Pokusajte ponovo.\n";
							else if (k < 1 || k > n)
								cout << "Vrednost k mora biti u opsegu [1, " << n << "]. Pokusajte ponovo.\n";
						} while (startingVertex < 1 || startingVertex > n || k < 1 || k > n);

						cout << endl;

						path = graph->kNearestNeighbour(startingVertex, k);
						cout << *path;

						break;

					case 6:

						if (graph->getN() < 6)
							cout << "U grafu mora biti vise od 5 cvorova!\n\n";
						else {
							cout << "Unesite gornju granicu cene puta: ";
							cin >> L;
							cout << endl;

							if (path)
								delete path;
							path = graph->opt3(L);
							if (path)
								cout << *path;
							else
								cout  << "Nije pronadjen put sa zadatim kriterijumom\n" << endl;
						}

						break;

					default:
						cout << "Nepoznata komanda. Pokusajte ponovo.\n";
						break;
					}
				} while (choice < 1 || choice > 6);
			}

			break;

		case 4:
			end = true;
			break;

		default:
			cout << "Nepoznata komanda. Pokusajte ponovo.\n\n";
			break;
		}

	}

	delete graph;
	delete path;

}