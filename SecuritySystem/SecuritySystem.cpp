// SecuritySystem.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "interface.h"
#include "locksystem.h"
#include "guesser.h"
#include "bignumber.h"
#include "lock.h"
#include "utilities.h"
#include <ctime>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>          // std::mutex

const int THREAD_MAX = 8;
using namespace std;

void callFromThreadExtractDigistsFromHash(const LockSystem* sys, Guesser* guesser) {
	guesser->HackIt(*sys);
}

int main()
{
	std::thread t[THREAD_MAX];
	std::vector< std::shared_ptr<LockSystem>> systems;
	Interface::readLockSystem("keyfile.txt","multisafefile.txt",systems);

	GuesserFactory *factory = new GuesserFactory();
	std::vector<std::unique_ptr<Guesser>> guessers = factory->CreateGuesserPool();

	for (int i = 0; i < THREAD_MAX; ++i) {
		            t[i] = std::thread(callFromThreadExtractDigistsFromHash, systems[0].get(), guessers[i].get());
		
	}

	//Join the threads with the main thread
	         for (int i = 0; i < THREAD_MAX; ++i) {
		             t[i].join();
	
	}

	cout << "finish\n";
	for (const std::unique_ptr<Guesser>& guesser : guessers)
	{
		const Guesser* guesserPtr = guesser.get();
		if (guesserPtr->HasSolution())
		{
			cout << "Found solution:\n";
			for (const std::vector<unsigned int>& solution: guesserPtr->GetSolution())
			{
				for (unsigned int i: solution)
					cout << i << " ";
				cout << "\n";
			}
		}
	}
	return 0;
}

