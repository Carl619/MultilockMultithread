#include "stdafx.h"
#include "bignumber.h"

BigNumber::BigNumber(std::string Value)
{
	this->Value = Value;
}

BigNumber::~BigNumber()
{
}

void BigNumber::IncrementNumber(int Index)
{
	switch (Value[Index]) {
	case '0':
		Value[Index] = '1';
		break;
	case '1':
		Value[Index] = '2';
		break;
	case '2':
		Value[Index] = '3';
		break;
	case '3':
		Value[Index] = '4';
		break;
	case '4':
		Value[Index] = '5';
		break;
	case '5':
		Value[Index] = '6';
		break;
	case '6':
		Value[Index] = '7';
		break;
	case '7':
		Value[Index] = '8';
		break;
	case '8':
		Value[Index] = '9';
		break;
	case '9':
		Value[Index] = 'A';
		break;
	case 'A':
		Value[Index] = 'B';
		break;
	case 'B':
		Value[Index] = 'C';
		break;
	case 'C':
		Value[Index] = 'D';
		break;
	case 'D':
		Value[Index] = 'E';
		break;
	case 'E':
		Value[Index] = 'F';
		break;
	case 'F':
		Value[Index] = 'G';
		break;
	case 'G':
		Value[Index] = 'H';
		break;
	case 'H':
		Value[Index] = 'J';
		break;
	case 'J':
		if (Index > 0){
			Value[Index] = '0';
			IncrementNumber(Index - 1);
		}
		break;
	}

}

void BigNumber::replaceNumber(int Index, char Number)
{
	Value[Index] = Number;
}

void BigNumber::replaceNumber(int Index, int Number)
{
	switch (Number) {
	case 0:
		Value[Index] = '0';
		break;
	case 1:
		Value[Index] = '1';
		break;
	case 2:
		Value[Index] = '2';
		break;
	case 3:
		Value[Index] = '3';
		break;
	case 4:
		Value[Index] = '4';
		break;
	case 5:
		Value[Index] = '5';
		break;
	case 6:
		Value[Index] = '6';
		break;
	case 7:
		Value[Index] = '7';
		break;
	case 8:
		Value[Index] = '8';
		break;
	case 9:
		Value[Index] = '9';
		break;
	case 10:
		Value[Index] = 'A';
		break;
	case 11:
		Value[Index] = 'B';
		break;
	case 12:
		Value[Index] = 'C';
		break;
	case 13:
		Value[Index] = 'D';
		break;
	case 14:
		Value[Index] = 'E';
		break;
	case 15:
		Value[Index] = 'F';
		break;
	case 16:
		Value[Index] = 'G';
		break;
	case 17:
		Value[Index] = 'H';
		break;
	case 18:
		Value[Index] = 'J';
		break;
	}
}

int BigNumber::letterToNumber(int Index)
{
	switch (Value[Index]) {
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'A':
		return 10;
		break;
	case 'B':
		return 11;
		break;
	case 'C':
		return 12;
		break;
	case 'D':
		return 13;
		break;
	case 'E':
		return 14;
		break;
	case 'F':
		return 15;
		break;
	case 'G':
		return 16;
		break;
	case 'H':
		return 17;
		break;
	case 'J':
		return 18;
		break;
	}
	return 0;
}

std::vector<int> BigNumber::convertToNumber4Digits(int Index)
{
	std::vector<int> Number;

	for (int i = 0; i < 4; i++) {
		int val = letterToNumber(i + (4 * Index));
		val -= 9;
		Number.push_back(val);

	}
	return Number;
}
