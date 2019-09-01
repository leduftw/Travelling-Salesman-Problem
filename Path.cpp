
#include "Path.h"

Path& Path::add(int vertex, int c) {
	path[length++] = vertex;
	cost += c;
	return *this;
}

ostream& operator<<(ostream &os, const Path &op) {
	os << "Put: (";
	for (int i = 0; i < op.n; i++) {
		if (i != 0)
			cout << " -> ";
		os << op.path[i];
	}
	os << ")" << endl;
	os << "Cena: " << op.cost << endl;
	return os << endl;
}

