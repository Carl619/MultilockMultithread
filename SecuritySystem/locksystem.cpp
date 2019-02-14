#include "stdafx.h"
#include "locksystem.h"
#include "lock.h"

LockSystem::LockSystem()
: Locked(true)
{
}

LockSystem::~LockSystem()
{
	for (Lock* lock:Locks)
		delete lock;
	Locks.clear();
}

bool LockSystem::init()
{
	generateRoot();
	generateHashFunctions();
	const int lockCount = Locks.size();
	for (int i = 0; i < lockCount; ++i)
	{
		if (!prepareLock(i))
			return false;
	}
	return checkSumCombination();
}

void LockSystem::createLock()
{
	Lock* lock = new Lock();
	Locks.push_back(lock);
}

void LockSystem::generateRoot()
{
	for (int i = 0;i<NUMBER_DIGITS;i++) {
		Root.push_back(rand() % MAX_ROOT_DIGIT);
	}
}

void LockSystem::generateHashFunctions()
{
	for (int i = 0;i<4;i++) {
		UHF.push_back(rand() % MAX_RAND_VALUE - MIN_RAND_VALUE);
		LHF.push_back(rand() % MAX_RAND_VALUE - MIN_RAND_VALUE);
		PHF.push_back(rand() % MAX_RAND_VALUE - MIN_RAND_VALUE);
	}
}

bool LockSystem::prepareLock(int i)
{
	if (i < 0 || static_cast<unsigned int>(i) >= Locks.size()) return false;
	Lock* lock = Locks[i];
	if (i > 0)
		lock->unlockHashFunction(UHF, Locks[i-1]->getHN());
	else
		lock->unlockHashFunction(UHF, Root);
	if (!lock->checkCN()) {
		return false;
	}
	lock->lockHashFunction(LHF);
	lock->passHashFunction(PHF);
	lock->lock();
	return true;
}

bool LockSystem::checkSumEven()
{
	unsigned int result = 0;
	for (Lock * l : Locks) {
		result += l->sumCN();
	}
	if (result % 2 != 0) return false;
	else return true;
}

bool LockSystem::checkSumCombination()
{
	for (unsigned int i = 0; i < Locks.size() - 1;i++) {
		if (Locks[i]->sumCN()>= Locks[i + 1]->sumCN())
			return false;
	}
	return true;
}

bool LockSystem::multiSafeValidation()
{
	if (checkSumCombination() == false)return false;
	return checkSumEven();
}

void LockSystem::createEmptyLocks(int size)
{
	for (int i = 0; i< size;i++)
		createLock();
}

