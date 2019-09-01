
#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
using namespace std;

class Path {

	vector<int> path;
	int n, length, cost;

public:

	Path(int n) {
		path.resize(n);
		this->n = n;
		length = cost = 0;
	}

	Path(const Path &op) = delete;
	Path& operator=(const Path &op) = delete;

	int get(int i) const {
		if (i < 0 || i >= n)
			return -1;
		else
			return path[i];
	}

	Path& add(int vertex, int cost = 0);

	int getCost() const {
		return cost;
	}

	vector<int> getPath() const {
		return path;
	}

	friend ostream& operator<<(ostream &, const Path &);

};

#endif

