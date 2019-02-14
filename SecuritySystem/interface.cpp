#include "stdafx.h"
#include "interface.h"
#include "locksystem.h"
#include "lock.h"
#include "guesser.h"

using namespace std;

LockSystem * Interface::generateSystem(int size)
{
	LockSystem*sys = new LockSystem();
	sys->createEmptyLocks(size);
	return sys;
}

void Interface::writeGuessSolution(const char * NameFile, const std::vector<std::shared_ptr<Guesser>>& GuessSolution)
{
	if (!NameFile || strlen(NameFile) == 0)
		return;

	ofstream Systemfile;
	Systemfile.open(NameFile);


	Systemfile << "NS " << GuessSolution.size() << "\n";
	for (unsigned  int i = 0; i < GuessSolution.size(); i++) {
		Systemfile << "Root: ";
		for (unsigned int j = 0; j < GuessSolution[i].get()->getRoot().size(); j++)
			Systemfile << GuessSolution[i].get()->getRoot()[j];
		Systemfile << "\n";
		for (unsigned int j = 0; j < GuessSolution[i].get()->getLNs().size(); j++) {
			Systemfile << "LN" << j << ": ";
			for (unsigned int k = 0; k < GuessSolution[i].get()->getLNs()[j].size(); k++)
				Systemfile << GuessSolution[i].get()->getLNs()[j][k];
			Systemfile << "\n";
		}
	}
	Systemfile.close();
}

void Interface::writeKeyFile(const char* NameFile, const std::vector<std::shared_ptr<LockSystem>>& LockSys)
{
	if (!NameFile || strlen(NameFile) == 0)
		return;

	ofstream Systemfile;
	Systemfile.open(NameFile);


	Systemfile << "NS "<< LockSys.size() <<"\n";
	for (unsigned int i = 0; i < LockSys.size(); i++) {
		Systemfile << "ROOT: ";
		for (unsigned int j = 0; j < LockSys[i].get()->getRoot().size();j++)
			Systemfile << LockSys[i].get()->getRoot()[j];
		Systemfile << "\n";
		Systemfile << "UHF: ";
		Systemfile  << LockSys[i].get()->getUHF()[0];
		for (unsigned int j = 1; j < LockSys[i].get()->getUHF().size();j++)
			Systemfile << ", " << LockSys[i].get()->getUHF()[j];
		Systemfile << "\n";
		Systemfile << "LHF: ";
		Systemfile  << LockSys[i].get()->getLHF()[0];
		for (unsigned int j = 1; j < LockSys[i].get()->getLHF().size();j++)
			Systemfile << ", " << LockSys[i].get()->getLHF()[j];
		Systemfile << "\n";
		Systemfile << "PHF: ";
		Systemfile << LockSys[i].get()->getPHF()[0];
		for (unsigned int j = 1; j < LockSys[i].get()->getPHF().size();j++)
			Systemfile << ", " << LockSys[i].get()->getPHF()[j];
		Systemfile << "\n";
	}


	Systemfile.close();
}

void Interface::writeMultiSafeFile(const char* NameFile, const std::vector<std::shared_ptr<LockSystem>>& LockSys)
{
	if (!NameFile || strlen(NameFile) == 0)
		return;

	ofstream Systemfile;
	Systemfile.open(NameFile);

	for (unsigned int i = 0; i < LockSys.size(); i++) {
		Systemfile << "NS " << i << " VALID" << "\n";
		for (unsigned int j = 0; j < LockSys[i].get()->getLocks().size();j++) {
			Systemfile << "CN" << j << ": ";
			for (unsigned int k = 0; k < LockSys[i].get()->getLocks()[j]->getCN().size();k++)
				Systemfile << LockSys[i].get()->getLocks()[j]->getCN()[k];
			Systemfile << ",";
			Systemfile << "LN" << j << ": ";
			for (unsigned int k = 0; k < LockSys[i].get()->getLocks()[j]->getLN().size();k++)
				Systemfile << LockSys[i].get()->getLocks()[j]->getLN()[k];
			Systemfile << ",";
			Systemfile << "HN" << j << ": ";
			for (unsigned int k = 0; k < LockSys[i].get()->getLocks()[j]->getHN().size();k++)
				Systemfile << LockSys[i].get()->getLocks()[j]->getHN()[k];
			Systemfile << "\n";
		}
	}
	Systemfile.close();
}

void Interface::readLockSystem(const char * NameFileLockSystem, const char * NameFileLock, std::vector<std::shared_ptr<LockSystem>>& LockSysVector)
{
	std::shared_ptr<LockSystem> newSystem;
	ifstream myfile(NameFileLockSystem);
	ifstream myotherfile(NameFileLock);
	string line;
	char * pch;
	cout << "reading file"<< '\n';
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
			char *dup = _strdup(line.c_str());
			char* strtokContext;
			pch = strtok_s(dup, " :,", &strtokContext);
			string	strPCH = pch;
			if (strPCH == "ROOT") {
				newSystem = std::make_shared<LockSystem>();
				pch = strtok_s(NULL, " ,;:.-", &strtokContext);
				std::vector<unsigned int> root;
				for (int i = 0; i< 4;i++) {
					root.push_back(pch[i] - '0');
				}
				newSystem->setRoot(root);
			}
			else if (strPCH == "UHF") {
				std::vector<int> uhf;
				for (int i = 0; i< 4;i++) {
					pch = strtok_s(NULL, " ,;:.", &strtokContext);
					if (pch[0] == '-') {
						uhf.push_back((pch[1]  - '0')* -1);
					}
					else
						uhf.push_back(pch[0] - '0');
				}
				newSystem->setUHF(uhf);
			}
			else if (strPCH == "LHF") {
				std::vector<int> lhf;
				for (int i = 0; i< 4;i++) {
					pch = strtok_s(NULL, " ,;:.", &strtokContext);
					if (pch[0] == '-') {
						lhf.push_back((pch[1] - '0')* -1);
					}
					else
						lhf.push_back(pch[0] - '0');
				}
				newSystem->setLHF(lhf);
			}
			else if (strPCH == "PHF") {
				std::vector<int> phf;
				for (int i = 0; i< 4;i++) {
					pch = strtok_s(NULL, " ,;:.", &strtokContext);
					if (pch[0] == '-') {
						phf.push_back((pch[1] - '0')* -1);
					}
					else
						phf.push_back(pch[0]- '0');
				}
				newSystem->setPHF(phf);
				LockSysVector.push_back(newSystem);
			}
			free(dup);
		}
		myfile.close();
	}
	cout << "reading file" << '\n';
	if (myotherfile.is_open())
	{
		int index = 0;
		int numberoflocks = 0;
		Lock * newLock;
		while (getline(myotherfile, line))
		{
			cout << line << '\n';
			char *dup = _strdup(line.c_str());
			char * strtokContext;
			pch = strtok_s(dup, " :,", &strtokContext);
			string	strPCH = pch;
			if (strPCH.find("CN") != std::string::npos) {
				newLock = new Lock();
				pch = strtok_s(NULL, " ,;:.-", &strtokContext);
				std::vector<unsigned int> cn;
				for (int i = 0; i< 4;i++) {
					cn.push_back(pch[i] - '0');
				}
				newLock->setCN(cn);
			
			pch = strtok_s(NULL, " ,;:.-", &strtokContext);
				strPCH = pch;
			 if (strPCH.find("LN") != std::string::npos) {
				pch = strtok_s(NULL, " ,;:.-", &strtokContext);
				std::vector<unsigned int> ln;
				for (int i = 0; i< 4;i++) {
					ln.push_back(pch[i] - '0');
				}
				newLock->setLN(ln);
			}
			 pch = strtok_s(NULL, " ,;:.-", &strtokContext);
			 	strPCH = pch;
			 if (strPCH.find("HN") != std::string::npos) {
				pch = strtok_s(NULL, " ,;:.-", &strtokContext);
				std::vector<unsigned int> hn;
				for (int i = 0; i< 4;i++) {
					hn.push_back(pch[i] - '0');
				}
				newLock->setHN(hn);
				LockSysVector[index]->addLock(newLock);
				numberoflocks++;
				if (numberoflocks == 5) {
					numberoflocks = 0;
					index ++;
				}

			}
			}
			free(dup);
		}
		myotherfile.close();
	}
}

void Interface::showLockSystem(const LockSystem& LockSys)
{

	cout << "Showing Lock System" << "\n";
	cout << "Root: ";
	for (unsigned int i = 0; i < LockSys.getRoot().size();i++)
		cout << LockSys.getRoot()[i];
	cout << "\n";
	cout << "UHF: ";
	for(unsigned int i = 0; i < LockSys.getUHF().size();i++)
		cout << ", " << LockSys.getUHF()[i];
	cout << "\n";
	cout << "LHF: ";
	for (unsigned int i = 0; i < LockSys.getLHF().size();i++)
		cout << ", " << LockSys.getLHF()[i];
	cout << "\n";
	cout << "PHF: ";
	for (unsigned int i = 0; i < LockSys.getPHF().size();i++)
		cout << ", " << LockSys.getPHF()[i];
	cout << "\n";

	for (const Lock* lock : LockSys.getLocks())
		showLocks(*lock);
}

void Interface::showLocks(const Lock& lock)
{
	cout << "Showing Lock" << "\n";
	cout << "CN: ";
	for (unsigned int i = 0; i < lock.getCN().size();i++)
		cout << lock.getCN()[i];
	cout << "\n";
	cout << "LN: ";
	for (unsigned int i = 0; i < lock.getLN().size();i++)
		cout << lock.getLN()[i];
	cout << "\n";
	cout << "HN: ";
	for (unsigned int i = 0; i < lock.getHN().size();i++)
		cout << lock.getHN()[i];
	cout << "\n";
}
