#pragma once
#include <string>
#include <vector>

class BigNumber {
public:
	BigNumber(std::string Value = "000000000000");
	~BigNumber();
	void IncrementNumber(int Index);
	const std::string& getValue() const { return Value; }
	void replaceNumber(int Index, char Number);
	void replaceNumber(int Index, int Number);
	int letterToNumber(int Index);
	std::vector<int> convertToNumber4Digits(int Index);
private:
	std::string Value;
	char LastValue;
};