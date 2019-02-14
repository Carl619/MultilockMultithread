#pragma once

#include <vector>
#include <memory>

const int  MAX_NUMBER = 9;
const int  MIN_NUMBER = 0;
const int  NUMBER_DIGITS = 4;
const int  INCREASE_DIGIT = 1;
const int  DECREASE_DIGIT = -1;
class Lock {

public:
	Lock();
	bool checkCN();
	void unlockHashFunction(const std::vector<int>& UHF, const std::vector<unsigned int>& Root);
	void lockHashFunction(const std::vector<int>& LHF);
	void passHashFunction(const std::vector<int>& PHF);
	void lock();
	void unlock();
	const std::vector<unsigned int>& getCN() const { return CN; }
	const std::vector<unsigned int>& getLN() const { return LN; }
	const std::vector<unsigned int>& getHN() const { return HN; }
	void setCN(std::vector<unsigned int> cn) { CN = cn; }
	void setLN(std::vector<unsigned int> ln) { LN = ln; }
	void setHN(std::vector<unsigned int> hn) { HN = hn; }
	unsigned int sumCN();
	bool isMatch(const std::vector<unsigned int>& guessTry) const;
private:
	std::vector<unsigned int> CN;
	std::vector<unsigned int> LN;
	std::vector<unsigned int> HN;
	bool Locked;
};