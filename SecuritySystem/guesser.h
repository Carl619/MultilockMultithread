#pragma once
#include <vector>
#include <memory>

const int  NUMBER_LOCKS = 5;
const int  RANGE_NUMBERS = 19;
class Lock;
class LockSystem;
class BigNumber;
class Guesser {

public:
	Guesser(int total, unsigned int MinN1, unsigned int MaxN1, unsigned int MinN2, unsigned int MaxN2, unsigned int MinN3, unsigned int MaxN3);
	~Guesser();

	void HackIt(const LockSystem& sys);
	bool HasSolution() const;
	const std::vector<std::vector<unsigned int>>& GetSolution() const {return Solution;}
	const std::vector<int>& getUHF() const { return UHF; }
	const std::vector<int>& getLHF() const { return LHF; }
	const std::vector<int>& getPHF() const { return PHF; }
	const std::vector<unsigned int>& getRoot() const { return Root; }
	const 	std::vector<std::vector<unsigned int>>& getLNs() const { return LNs; }
private:
	std::vector<int> extractDigitsForHash(unsigned int Value);
	void guess(BigNumber& Number);
	void guess(unsigned int Number, int IndexHash);
	void setLock(const std::vector<unsigned int>& root) { Root = root; }
	void resetGuess();
	std::vector<std::vector<unsigned int>> tryGuess();
	void addLN(const std::vector<unsigned int>& NewLN) { LNs.push_back(NewLN); }
	std::vector<unsigned int> unlockHashFunction(const std::vector<unsigned int>& Guess);
	std::vector<unsigned int> lockHashFunction(const std::vector<unsigned int>& Guess);
	std::vector<unsigned int> passHashFunction(const std::vector<unsigned int>& Guess);
	int NumberLocks;
	std::vector<std::vector<unsigned int>> LNs;
	std::vector<unsigned int> Root;
	std::vector<int> UHF;
	std::vector<int> LHF;
	std::vector<int> PHF;


	unsigned int MinN1;
	unsigned int MaxN1;
	unsigned int MinN2;
	unsigned int MaxN2;
	unsigned int MinN3;
	unsigned int MaxN3;
	std::vector<std::vector<unsigned int>> Solution;
};

class GuesserFactory {

public:
	GuesserFactory();
	std::vector<std::unique_ptr<Guesser>> CreateGuesserPool();
};

