#include "stdafx.h"
#include "guesser.h"
#include "utilities.h"
#include "bignumber.h"
#include "locksystem.h"
#include "lock.h"

Guesser::Guesser(int total, unsigned int minN1, unsigned int maxN1, unsigned int minN2, unsigned int maxN2, unsigned int minN3, unsigned int maxN3)
 : NumberLocks(total),MinN1(minN1),MaxN1(maxN1), MinN2(minN2), MaxN2(maxN2), MinN3(minN3), MaxN3(maxN3)
{
}

Guesser::~Guesser()
{
}

void Guesser::HackIt(const LockSystem &sys)
{
	bool match = false;
	setLock(sys.getRoot());
	for (const Lock* lock : sys.getLocks())
		addLN(lock->getLN());
	do {
			match = false;
			for (unsigned int i = MinN1; i < MaxN1; i++) {
				guess(i, 0);
				for (unsigned int j = MinN2; j < MaxN2; j++) {
					guess(j, 1);
					for (unsigned int k = MinN3; k < MaxN3; k++) {
						guess(k, 2);
						std::vector<std::vector<unsigned int>> tries = tryGuess();
						for (unsigned int l = 0; l < tries.size(); l++) {
							const std::vector<unsigned int>& tryAttempt = tries[l];
							const Lock* lock = sys.getLocks()[l];
							match = lock->isMatch(tryAttempt);
							if (match == false)
								break;
						}
						if (match == true) {
							Solution = tries;
							std::cout << "success\n";
							return;
						}
					}
				}
			}
	} while (!match);
}

bool Guesser::HasSolution() const
{
	return (Solution.size() > 0);
}

std::vector<int> Guesser::extractDigitsForHash(unsigned int Value)
{
	//19*19*19
	//extract 4 digits from number;
	std::vector<int> digitsResult;
	int result;
	digitsResult.push_back(Value / (RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS));
	result = Value % (RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS);
	digitsResult.push_back(result / (RANGE_NUMBERS*RANGE_NUMBERS));
	result = result % (RANGE_NUMBERS*RANGE_NUMBERS);
	digitsResult.push_back(result / (RANGE_NUMBERS));
	result = result % (RANGE_NUMBERS);
	digitsResult.push_back(result);
	for (unsigned int i = 0; i < digitsResult.size(); i++) {
		digitsResult[i] = digitsResult[i] - 9;
	}
	return digitsResult;
}

void Guesser::guess(BigNumber& Number)
{
	PHF = Number.convertToNumber4Digits(0);
	UHF = Number.convertToNumber4Digits(1);
	LHF = Number.convertToNumber4Digits(2);
}

void Guesser::guess(unsigned int Number, int IndexHash)
{
	if (IndexHash < 0 || IndexHash>2)return;
	if (IndexHash == 0) {
		UHF = extractDigitsForHash(Number);
	}
	else if (IndexHash == 1) {
		LHF = extractDigitsForHash(Number);
	}
	else if (IndexHash == 2) {
		PHF = extractDigitsForHash(Number);
	}
}

void Guesser::resetGuess()
{
	UHF.clear();
	LHF.clear();
	PHF.clear();
}

std::vector<std::vector<unsigned int>> Guesser::tryGuess()
{
	std::vector<std::vector<unsigned int>> Tries;
	std::vector<unsigned int> newTry;
	newTry = unlockHashFunction( Root);
	for (unsigned int i = 0; i < LNs.size(); i++) {
		newTry = lockHashFunction( newTry);
		Tries.push_back(newTry);
		newTry = passHashFunction( newTry);
		newTry = unlockHashFunction( newTry);
		
	}
	return Tries;
}


std::vector<unsigned int> Guesser::unlockHashFunction(const std::vector<unsigned int>& Guess)
{
	std::vector<unsigned int> CNTry;
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = Guess[i] + UHF[i];
		adjustNumber(&value);
		CNTry.push_back(value);
	}
	return CNTry;
}

std::vector<unsigned int> Guesser::lockHashFunction(const std::vector<unsigned int>& Guess)
{
	std::vector<unsigned int> LNTry;
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = Guess[i] + LHF[i];
		adjustNumber(&value);
		LNTry.push_back(value);
	}
	return LNTry;
}

std::vector<unsigned int> Guesser::passHashFunction(const std::vector<unsigned int>& Guess)
{
	std::vector<unsigned int> HNTry;
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = Guess[i] + PHF[i];
		adjustNumber(&value);
		HNTry.push_back(value);
	}
	return HNTry;
}

GuesserFactory::GuesserFactory()
{
}

std::vector<std::unique_ptr<Guesser>> GuesserFactory::CreateGuesserPool()
{
	std::vector<std::unique_ptr<Guesser>> guessers;
	unsigned int minN1 = 0;
	unsigned int maxN1 = 0;
	unsigned int minN2 = 0;
	unsigned int maxN2 = 0;
	unsigned int minN3 = 0;
	unsigned int maxN3 = 0;
	for (int i = 0; i < 8; i++) {
		
		if (i == 0) {
			minN1 = 0;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS/2;
			minN2 = 0;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN3 = 0;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
		}
		if (i == 1) {
			minN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN1 = RANGE_NUMBERS* RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN2 = 0;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN3 = 0;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
		}
		if (i == 2) {
			minN1 = 0;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN3 = 0;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
		}
		if (i == 3) {
			minN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN3 = 0;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
		}
		if (i == 4) {
			minN1 = 0;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN2 = 0;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2 ;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
		}
		if (i == 5) {
			minN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN2 = 0;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
		}
		if (i == 6) {
			minN1 = 0;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			minN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
		}
		if (i == 7) {
			minN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN1 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN2 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
			minN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS / 2;
			maxN3 = RANGE_NUMBERS * RANGE_NUMBERS*RANGE_NUMBERS*RANGE_NUMBERS;
		}
		std::unique_ptr<Guesser> guesser(new Guesser(NUMBER_LOCKS, minN1, maxN1, minN2, maxN2, minN3, maxN3));
		guessers.push_back(std::move(guesser));
	}
	return guessers;
}
