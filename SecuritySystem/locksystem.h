#pragma once
#include <vector>
#include <memory>
#include "lock.h"
const int  MIN_RAND_VALUE = 9;
const int  MAX_RAND_VALUE = 18;
const int  MAX_ROOT_DIGIT = 9;

class LockSystem {

public:
	LockSystem();
	~LockSystem();
	bool init();
	void createLock();
	void generateRoot();
	void generateHashFunctions();
	bool checkSumEven();
	bool multiSafeValidation();
	void createEmptyLocks(int size);
	const std::vector<int>& getUHF() const { return UHF; }
	const std::vector<int>& getLHF() const { return LHF; }
	const std::vector<int>& getPHF() const { return PHF; }
	const std::vector<unsigned int>& getRoot() const { return Root; }
	const std::vector<Lock*>& getLocks() const { return Locks; }
	void setRoot(std::vector<unsigned int> root) { Root = root; }
	void setUHF(std::vector< int> uhf) { UHF = uhf; }
	void setLHF(std::vector< int> lhf) { LHF = lhf; }
	void setPHF(std::vector< int> phf) { PHF = phf; }
	void addLock(Lock* Lock) { Locks.push_back(Lock); }

private:
	bool checkSumCombination();
	bool prepareLock(int i);
	std::vector<Lock*> Locks;
	std::vector<int> UHF;
	std::vector<int> LHF;
	std::vector<int> PHF;
	std::vector<unsigned int> Root;
	bool Locked;
};