
#include "Utility.h"

void Utility::printSpace(int howManyTimes) {
	for (int i = 0; i < howManyTimes; i++)
		cout << " ";
}

int Utility::numberOfDigits(int a) {
	int num = 0;
	while (a > 0) {
		a /= 10;
		num++;
	}
	return num;
}

