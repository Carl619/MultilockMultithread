#include "stdafx.h"
#include "lock.h"
#include "binarytree.h"
#include "utilities.h"

using namespace std;

Lock::Lock()
	:Locked(true)
{
}

bool Lock::checkCN()
{
	tree * checker = new tree(CN[0]);
	for (int i = 1; i < NUMBER_DIGITS;i++)
		if (!checker->insert_integer(CN[i]))
			return false;
	delete checker;
	return true;
}

void Lock::unlockHashFunction(const std::vector<int>& UHF, const std::vector<unsigned int>& Root)
{
	if (CN.size() > 0)CN.clear();
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = Root[i] + UHF[i];
		adjustNumber(&value);
		CN.push_back(value);
	}
}

void Lock::lockHashFunction(const std::vector<int>& LHF)
{
	if (LN.size() > 0)LN.clear();
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = CN[i] + LHF[i];
		adjustNumber(&value);
		LN.push_back(value);
	}
}

void Lock::passHashFunction(const std::vector<int>& PHF)
{
	if (HN.size() > 0)HN.clear();
	int value = 0;
	for (int i = 0; i < NUMBER_DIGITS;i++) {
		value = LN[i] + PHF[i];
		adjustNumber(&value);
		HN.push_back(value);
	}
}

void Lock::lock()
{
	Locked = true;
}

void Lock::unlock()
{
	Locked = false;
}

unsigned int Lock::sumCN()
{
	unsigned int result = 0;
	for (unsigned int Number : CN) {
		result += Number;
	}
	return result;
}

bool Lock::isMatch(const std::vector<unsigned int>& guessTry) const
{
	if (guessTry.size() == 0)
		return false;
	if (guessTry.size() != LN.size())
		return false;

	int lnSize = LN.size();
	for (int i = 0; i < lnSize; ++i) {
		if (guessTry[i] != LN[i])
			return false;
	}
	return true;
}
