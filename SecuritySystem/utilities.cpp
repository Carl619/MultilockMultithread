#include "stdafx.h"
#include "utilities.h"
using namespace std;

void adjustNumber(int *CurrentKey)
{
	if (*CurrentKey > MAX_NUMBER) {
		*CurrentKey -= 10;
	}
	else if (*CurrentKey < MIN_NUMBER) {
		*CurrentKey += 10;
	}
}

