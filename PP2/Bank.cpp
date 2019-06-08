#include "Bank.h"

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}

void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << totalBalance + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance + value > 0)
	{
		SetTotalBalance(totalBalance + value);
		std::cout << "Total Balance = " << GetTotalBalance() << std::endl;
	}
	if (totalBalance != GetTotalBalance() - value) {
		std::cout << "! ERROR !" << std::endl;
	}
}

int CBank::GetTotalBalance()
{
	return m_totalBalance;
}

void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(2000);
}

std::vector<CBankClient> CBank::GetAllClients()
{
	return m_clients;
}
