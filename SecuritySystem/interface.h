#pragma once
#include <fstream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class LockSystem;
class Lock;
class Guesser;
class Interface {
public:
	static LockSystem * generateSystem(int size);
	static void writeGuessSolution(const char* NameFile, const std::vector<std::shared_ptr<Guesser>>& GuessSolution);
	static void writeKeyFile(const char* NameFile, const std::vector<std::shared_ptr<LockSystem>>& LockSysVector);
	static void writeMultiSafeFile(const char* NameFile, const std::vector<std::shared_ptr<LockSystem>>& LockSysVector);
	static void readLockSystem(const char* NameFile, const char * NameFileLock, std::vector<std::shared_ptr<LockSystem>>& LockSysVector);
	static void showLockSystem(const LockSystem& LockSys);
	static void showLocks(const Lock& lock);
};