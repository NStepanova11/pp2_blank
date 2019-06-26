#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include "KeyType.h"
#include <sstream>

using namespace std;

void Help()
{
	cout << "Use program with key:" << endl;
	cout << "\"mutex\" - for using program with mutex synchronization." << endl;
	cout << "\"critical_section\" - for using program with critical_section synchronization." << endl;
	cout << "\"not_sync\" - for using program without synchronization." << endl;
	cout << "\"\?\" - for show help." << endl;
}

KeyTypes GetProgramKey(string keyType)
{
	if (keyType == "mutex")
	{
		return KeyTypes::mutex;
	}
	else if (keyType == "critical_section")
	{
		return KeyTypes::critical_section;
	}
	else if (keyType == "not_sync")
	{
		return KeyTypes::not_sync;
	}
	else if (keyType == "?")
	{
		return KeyTypes::help;
	}
	else
	{
		cout << "Incorrect key value" << endl;
		return KeyTypes::bad_key;
	}
}

int GetClientCount(string value)
{
	int clientCount = 0;
	stringstream ss(value);
	ss >> clientCount;
	return clientCount;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Error. Usage <prog_name.exe> <client_number> <sync_type>" << endl;
		Help();
	}
	else
	{
		int clientCount = GetClientCount(argv[1]);
		string keyType = argv[2];
		KeyTypes key = GetProgramKey(keyType);

		if (key != KeyTypes::bad_key && key != KeyTypes::help)
		{
			vector<CBankClient*> clients;
			CBank* bank = new CBank(key);

			for (size_t i = 0; i < clientCount; i++)
			{
				CBankClient *client = bank->CreateClient();
				clients.push_back(client);
			}

			// TODO: WaitForMultipleObjects
			while (true)
			{
				string exitCommand;
				WaitForMultipleObjects(bank->GetClientCount(), bank->GetClientHandles(), TRUE, 4000);
				cin >> exitCommand;
				if (exitCommand == "exit" || exitCommand == "quit")
					break;
			}
			int clientsTotalBalance = 0;
			for (CBankClient client : bank->GetAllClients())
			{
				auto clientBalance = bank->GetClientBalance(client.GetId());
				std::cout << "Client # " << client.GetId() << " balance: " << clientBalance << std::endl;
				clientsTotalBalance += clientBalance;
			}
			std::cout << "Clients total balance " << clientsTotalBalance << std::endl;
			std::cout << "Bank total balance: " << bank->GetTotalBalance() << endl;

		}
		else if (key = KeyTypes::help)
		{
			Help();
		}

	}
	return 0;
}