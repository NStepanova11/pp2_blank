#include "stdafx.h"
#include "Bank.h"
//#include "BankClient.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{ 
		cout << "Error. Usage <prog_name.exe> <client_number>" << endl;
	}

	int clientCount = atoi(argv[1]);
	CBank* bank = new CBank();
	vector <CBankClient*> bankClients;

	for (size_t i = 0; i < clientCount; i++)
	{
		bankClients.push_back(bank->CreateClient());
	}

	// TODO: WaitForMultipleObjects
	while (true)
	{
	}
    return 0;
}
