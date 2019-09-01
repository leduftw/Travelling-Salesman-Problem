
#ifndef COMPLETE_GRAPH_H
#define COMPLETE_GRAPH_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <random>
#include "Path.h"
#include "Utility.h"
using namespace std;

const int INF = 0x3f3f3f3f;

class CompleteGraph {

	int n, maxNumOfDigits;
	int **d;

	void copy(const CompleteGraph &);

	void move(CompleteGraph &g) {
		n = g.n;
		maxNumOfDigits = g.maxNumOfDigits;
		d = g.d;
		g.d = nullptr;
	}

	void del();

public:

	CompleteGraph(int numOfVertices) {
		n = numOfVertices;
		d = new int*[n];
		for (int i = 0; i < n; i++)
			d[i] = new int[n];
	}

	CompleteGraph(const CompleteGraph &g) {
		copy(g);
	}

	CompleteGraph(CompleteGraph &&g) {
		move(g);
	}

	~CompleteGraph() {
		del();
	}

	CompleteGraph& operator=(const CompleteGraph &g) {
		if (this != &g) {
			del();
			copy(g);
		}
		return *this;
	}

	CompleteGraph& operator=(CompleteGraph &&g) {
		if (this != &g) {
			del();
			move(g);
		}
		return *this;
	}

	friend istream& operator>>(istream &, CompleteGraph &);

	int getN() const {
		return n;
	}

	void setMaxNumOfDigits(int max) {
		maxNumOfDigits = max;
	}

	void randomWeights(int low, int high);
	void printWeightMatrix() const;

	Path* optimalPath() const;
	Path* randomPath() const;
	Path* nearestNeighbour(int startingVertex = 1) const;
	Path* furthestNeighbour(int startingVertex = 1) const;
	Path* kNearestNeighbour(int startingVertex = 1, int k = 1) const;
	Path* opt3(int L) const;

};

#endif
