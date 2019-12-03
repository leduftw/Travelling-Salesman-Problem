
#include "Utility.h"

int Utility::numberOfDigits(int number) {
	int numOfDigits = 0;
	while (number > 0) {
		number /= 10;
		numOfDigits++;
	}
	return numOfDigits;
}

