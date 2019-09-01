
#include "CompleteGraph.h"

istream& operator>>(istream &is, CompleteGraph &g) {
	int high = -1;
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++) {
			is >> g.d[i][j];
			if (g.d[i][j] > high)
				high = g.d[i][j];
		}

	g.maxNumOfDigits = Utility::numberOfDigits(high) + 1;
	return is;
}

void CompleteGraph::copy(const CompleteGraph &g) {
	n = g.n;
	maxNumOfDigits = g.maxNumOfDigits;
	d = new int*[n];
	for (int i = 0; i < n; i++) {
		d[i] = new int[n];
		for (int j = 0; j < n; j++)
			d[i][j] = g.d[i][j];
	}
}

void CompleteGraph::del() {
	for (int i = 0; i < n; i++)
		delete[] d[i];
	delete[] d;
}

void CompleteGraph::randomWeights(int low, int high) {
	for (int i = 0; i < n; i++) {
		d[i][i] = 0;
		for (int j = i + 1; j < n; j++)
			d[i][j] = d[j][i] = (rand() / (double)RAND_MAX) * (high - low) + low;
	}
}

void CompleteGraph::printWeightMatrix() const {
	cout << "Matrica tezina:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << d[i][j];
			int currNumOfDigits = Utility::numberOfDigits(d[i][j]);
			Utility::printSpace(maxNumOfDigits - ((currNumOfDigits == 0) ? 1 : currNumOfDigits));
		}
		cout << endl;
	}
	cout << "\n\n";
}

Path* CompleteGraph::optimalPath() const {
	//Heap's algorithm
	int tmp = 0, min;

	vector<int> min1(n);
	vector<int> temp(n);
	vector<int> temp1(n);

	for (int i = 0; i < n; i++)
		temp1[i] = i;

	//for (int i = 0; i < n; i++) cout << temp1[i] << " ";
	//cout << endl;
	min1 = temp1;
	for (int i = 0; i < n - 1; i++) tmp += this->d[min1[i]][min1[i + 1]];
	tmp += this->d[min1[0]][min1[n - 1]];
	min = tmp;

	int i = 0;
	while (i < n) {
		if (temp[i] < i) {
			if (i % 2 == 0)
				swap(temp1[0], temp1[i]);
			else
				swap(temp1[temp[i]], temp1[i]);

			tmp = 0;

			for (int i = 0; i < n - 1; i++)
				tmp += this->d[temp1[i]][temp1[i + 1]];

			tmp += this->d[temp1[0]][temp1[n - 1]];

			if (tmp < min) {
				min = tmp;
				min1 = temp1;
			}

			/*for (int i = 0; i < n; i++) cout << temp1[i] << " ";
			cout << endl;*/
			temp[i]++;
			i = 0;
		}
		else
			temp[i++] = 0;
	}

	Path* path = new Path(n + 1);
	path->add(min1[0] + 1);
	for (int i = 1; i < n; i++)
		path->add(min1[i] + 1, d[min1[i - 1]][min1[i]]);
	path->add(min1[0] + 1, d[min1[n - 1]][min1[0]]);

	return path;
}

Path* CompleteGraph::randomPath() const {
	vector<int> path(n);
	for (int i = 1; i <= n; i++)
		path[i - 1] = i;

	/*
	// Fisher-Yates shuffle algorithm
	default_random_engine generator;
	for (int i = n - 1; i > 0; i--) {
		uniform_int_distribution<int> distribution(0, i);
		int j;
		for (int k = 0; k < 4; k++)
			j = distribution(generator);
		if(i != j)
			swap(path[i], path[j]);
	}
	*/

	random_shuffle(path.begin(), path.end());

	Path *rndPath = new Path(n + 1);
	rndPath->add(path[0]);
	for (int i = 1; i < n; i++)
		rndPath->add(path[i], d[path[i - 1] - 1][path[i] - 1]);
	rndPath->add(path[0], d[path[n - 1] - 1][path[0] - 1]);

	return rndPath;
}

Path* CompleteGraph::nearestNeighbour(int startingVertex) const {
	set<int> s;
	s.insert(startingVertex);
	int *path = new int[n];
	path[0] = startingVertex;

	for (int i = 1; i < n; i++) {
		int min = INF;
		int pos = -1;

		for (int j = 0; j < n; j++)
			if (s.count(j + 1) == 0 && d[startingVertex - 1][j] < min) {
				min = d[startingVertex - 1][j];
				pos = j;
			}

		path[i] = pos + 1;
		startingVertex = pos + 1;
		s.insert(startingVertex);
	}

	Path *nearPath = new Path(n + 1);
	nearPath->add(path[0]);
	for (int i = 1; i < n; i++)
		nearPath->add(path[i], d[path[i - 1] - 1][path[i] - 1]);
	nearPath->add(path[0], d[path[n - 1] - 1][path[0] - 1]);

	delete[] path;
	return nearPath;
}

Path* CompleteGraph::furthestNeighbour(int startingVertex) const {
	set<int> s;
	s.insert(startingVertex);
	int *path = new int[n];
	path[0] = startingVertex;

	for (int i = 1; i < n; i++) {
		int max = -1;
		int pos = -1;

		for (int j = 0; j < n; j++)
			if (s.count(j + 1) == 0 && d[startingVertex - 1][j] > max) {
				max = d[startingVertex - 1][j];
				pos = j;
			}

		path[i] = pos + 1;
		startingVertex = pos + 1;
		s.insert(startingVertex);
	}

	Path *furPath = new Path(n + 1);
	furPath->add(path[0]);
	for (int i = 1; i < n; i++)
		furPath->add(path[i], d[path[i - 1] - 1][path[i] - 1]);
	furPath->add(path[0], d[path[n - 1] - 1][path[0] - 1]);

	delete[] path;
	return furPath;
}

Path* CompleteGraph::kNearestNeighbour(int startingVertex, int k) const {
	set<int> s;
	s.insert(startingVertex);

	vector<int> path(n);
	path[0] = startingVertex;
	vector<pair<int, int>> potential; // first - potential next hop, second - distance from current node

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (s.count(j + 1) == 0 && j != (path[i - 1] - 1))
				potential.emplace_back(make_pair(j, d[j][(path[i - 1] - 1)]));

		sort(potential.begin(), potential.end(), [](pair<int, int> a, pair<int, int> b) {return (a.second < b.second) ? 1 : 0; });
		int pos;
		if (potential.size() < k)
			pos = potential[potential.size() - 1].first;
		else
			pos = potential[k - 1].first;

		path[i] = pos + 1;
		startingVertex = pos + 1;
		s.insert(startingVertex);
		potential.clear();
	}

	Path *kNearPath = new Path(n + 1);
	kNearPath->add(path[0]);
	for (int i = 1; i < n; i++)
		kNearPath->add(path[i], d[path[i - 1] - 1][path[i] - 1]);
	kNearPath->add(path[0], d[path[n - 1] - 1][path[0] - 1]);

	return kNearPath;
}

Path* CompleteGraph::opt3(int L) const {

	int limit = 100000; // Modify this if you want to play around

	vector<int> pathArr(n);
	vector<int> nonadjacentEdges(3);
	int totalCost, localCost;
	int iterationWithoutAnyChange = 1, totalNumberOfIterations = 1;
	bool breakNatural = true;

	for (int i = 1; i <= n; i++)
		pathArr[i - 1] = i;
	random_shuffle(pathArr.begin(), pathArr.end());

	Path *path = new Path(n + 1);
	path->add(pathArr[0]);
	for (int i = 1; i < n; i++)
		path->add(pathArr[i], d[pathArr[i - 1] - 1][pathArr[i] - 1]);
	path->add(pathArr[0], d[pathArr[n - 1] - 1][pathArr[0] - 1]);
	totalCost = path->getCost();

	cout << "Pocetna Hamiltonova kontura:" << endl;
	cout << *path << endl;

	do {

		pathArr = path->getPath();
		pathArr.resize(n);

		do {
			nonadjacentEdges[0] = rand() % (n - 1) + 1;
			nonadjacentEdges[1] = rand() % (n - 1) + 1;
			nonadjacentEdges[2] = rand() % (n - 1) + 1;
		} while (abs(nonadjacentEdges[0] - nonadjacentEdges[1]) <= 1 || abs(nonadjacentEdges[0] - nonadjacentEdges[2]) <= 1 || abs(nonadjacentEdges[1] - nonadjacentEdges[2]) <= 1);

		sort(nonadjacentEdges.begin(), nonadjacentEdges.end(), [](int a, int b) {return (a < b) ? 1 : 0; });
		localCost = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[0]] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[1]] - 1] + d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[2]] - 1];

		vector<int> part1(nonadjacentEdges[1] - nonadjacentEdges[0]);
		vector<int>part2(nonadjacentEdges[2] - nonadjacentEdges[1]);
		vector<int> part3(n - nonadjacentEdges[2] + nonadjacentEdges[0]);

		for (int i = nonadjacentEdges[0]; i < nonadjacentEdges[1]; i++)
			part1[i - nonadjacentEdges[0]] = pathArr[i];

		for (int i = nonadjacentEdges[1]; i < nonadjacentEdges[2]; i++)
			part2[i - nonadjacentEdges[1]] = pathArr[i];

		for (int i = nonadjacentEdges[2]; i < n; i++)
			part3[i - nonadjacentEdges[2]] = pathArr[i];

		for (int i = 0; i < nonadjacentEdges[0]; i++)
			part3[i + n - nonadjacentEdges[2]] = pathArr[i];

		// H1: (1 -> 2), (3 -> 4), (5 -> 6)
		// Hamiltonove konture H2, H3, H4, H5, H6, H7, H8
		int cost2 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[0]] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[2] - 1] - 1] + d[pathArr[nonadjacentEdges[1]] - 1][pathArr[nonadjacentEdges[2]] - 1]; // (1 -> 2), (3 -> 5), (4 -> 6)
		int cost3 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[1] - 1] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[1]] - 1] + d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[2]] - 1]; // (1 -> 3), (2 -> 4), (5 -> 6)
		int cost4 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[1] - 1] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[2] - 1] - 1] + d[pathArr[nonadjacentEdges[1]] - 1][pathArr[nonadjacentEdges[2]] - 1]; // (1 -> 3), (2 -> 5), (4 -> 6)
		int cost5 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[1]] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[2] - 1] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[2]] - 1]; // (1 -> 4), (2 -> 5), (3 -> 6)
		int cost6 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[1]] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[2]] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[2] - 1] - 1]; // (1 -> 4), (2 -> 6), (3 -> 5)  
		int cost7 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[2] - 1] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[1]] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[2]] - 1]; // (1 -> 5), (2 -> 4), (3 -> 6)
		int cost8 = d[pathArr[nonadjacentEdges[0] - 1] - 1][pathArr[nonadjacentEdges[2] - 1] - 1] + d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[2]] - 1] + d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[1]] - 1]; // (1 -> 5), (2 -> 6), (3 -> 4)

		if (localCost > cost2) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[0]], d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = 1; i < part1.size(); i++)
				path->add(part1[i], d[part1[i - 1] - 1][part1[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2] - 1], d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[1] - 1] - 1]);

			for (int i = part2.size() - 2; 0 <= i; i--)
				path->add(part2[i], d[part2[i] - 1][part2[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[1]] - 1]);

			localCost = cost2;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost3) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[1] - 1], d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = part1.size() - 2; 0 <= i; i--)
				path->add(part1[i], d[part1[i] - 1][part1[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[1]], d[pathArr[nonadjacentEdges[1]] - 1][pathArr[nonadjacentEdges[0]] - 1]);

			for (int i = 1; i < part2.size(); i++)
				path->add(part2[i], d[part2[i - 1] - 1][part2[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[2] - 1] - 1]);

			localCost = cost3;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost4) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[1] - 1], d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = part1.size() - 2; 0 <= i; i--)
				path->add(part1[i], d[part1[i] - 1][part1[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[2] - 1], d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[0]] - 1]);

			for (int i = part2.size() - 2; 0 <= i; i--)
				path->add(part2[i], d[part2[i] - 1][part2[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[1]] - 1]);

			localCost = cost4;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost5) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[1]], d[pathArr[nonadjacentEdges[1]] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = 1; i < part2.size(); i++)
				path->add(part2[i], d[part2[i - 1] - 1][part2[i] - 1]);
			path->add(pathArr[nonadjacentEdges[0]], d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[2] - 1] - 1]);

			for (int i = 1; i < part1.size(); i++)
				path->add(part1[i], d[part1[i - 1] - 1][part1[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[1] - 1] - 1]);

			localCost = cost5;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost6) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[1]], d[pathArr[nonadjacentEdges[1]] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = 1; i < part2.size(); i++)
				path->add(part2[i], d[part2[i - 1] - 1][part2[i] - 1]);
			path->add(pathArr[nonadjacentEdges[1] - 1], d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[2] - 1] - 1]);

			for (int i = part1.size() - 2; 0 <= i; i--)
				path->add(part1[i], d[part1[i] - 1][part1[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[0]] - 1]);

			localCost = cost6;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost7) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2] - 1], d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = part2.size() - 2; 0 <= i; i--)
				path->add(part2[i], d[part2[i] - 1][part2[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[0]], d[pathArr[nonadjacentEdges[0]] - 1][pathArr[nonadjacentEdges[1]] - 1]);

			for (int i = 1; i < part1.size(); i++)
				path->add(part1[i], d[part1[i - 1] - 1][part1[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[1] - 1] - 1]);

			localCost = cost7;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/

		if (localCost > cost8) {
			delete path;

			path = new Path(n + 1);
			path->add(part3[0]);

			for (int i = 1; i < part3.size(); i++)
				path->add(part3[i], d[part3[i - 1] - 1][part3[i] - 1]);
			path->add(pathArr[nonadjacentEdges[2] - 1], d[pathArr[nonadjacentEdges[2] - 1] - 1][pathArr[nonadjacentEdges[0] - 1] - 1]);

			for (int i = part2.size() - 2; 0 <= i; i--)
				path->add(part2[i], d[part2[i] - 1][part2[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[1] - 1], d[pathArr[nonadjacentEdges[1] - 1] - 1][pathArr[nonadjacentEdges[1]] - 1]);

			for (int i = part1.size() - 2; 0 <= i; i--)
				path->add(part1[i], d[part1[i] - 1][part1[i + 1] - 1]);
			path->add(pathArr[nonadjacentEdges[2]], d[pathArr[nonadjacentEdges[2]] - 1][pathArr[nonadjacentEdges[0]] - 1]);

			localCost = cost8;
			totalCost = path->getCost();

			iterationWithoutAnyChange = 1;
		}

		/*cout << "Iteracija #" << totalNumberOfIterations << ": " << endl;
		cout << *path << endl;*/
		iterationWithoutAnyChange++;
		totalNumberOfIterations++;

		if (iterationWithoutAnyChange > limit) {
			breakNatural = false;
			break;
		}

	} while (totalCost > L);

	if (breakNatural)
		return path;
	else
		return nullptr;
}
