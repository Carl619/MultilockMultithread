// locks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "interface.h"
#include "locksystem.h"

using namespace std;
int main()
{
	LockSystem*sys = new LockSystem();
	Interface * interfaz = new Interface();
	sys->generateRoot();
	sys->generateHashFunctions();
	interfaz->showLockSystem(sys);
    return 0;
}

