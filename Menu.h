
#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

class Menu {
public:

	Menu() = default;
	Menu(const Menu &) = delete;
	Menu& operator=(const Menu &) = delete;

	friend ostream& operator<<(ostream &, const Menu &);
	static void printWaysToSolve();
	static void inputForMatrix();

};

#endif
