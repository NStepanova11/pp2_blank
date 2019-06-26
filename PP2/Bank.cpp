#include "Bank.h"

CBank::CBank(KeyTypes keyType)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_keyType = keyType;
	InitializeCriticalSection(&m_criticalSection);
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
	ActivateSynchronization();

	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();
	totalBalance += value;
	SetClientBalance(client.GetId(), value);

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
	DeactivateSynchronization();
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
	Sleep(1000);
	// TODO
}

void CBank::ActivateSynchronization()
{
	if (m_keyType == KeyTypes::mutex)
	{
		m_mutex.lock();
	}
	else if (m_keyType == KeyTypes::critical_section)
	{
		EnterCriticalSection(&m_criticalSection);
	}
}

void CBank::DeactivateSynchronization()
{
	if (m_keyType == KeyTypes::mutex)
	{
		m_mutex.unlock();
	}
	else if (m_keyType == KeyTypes::critical_section)
	{
		LeaveCriticalSection(&m_criticalSection);
	}
}

void CBank::SetClientBalance(int clientId, int newValue)
{
	auto it = clientBalanceMap.find(clientId);
	if (it != clientBalanceMap.end())
	{
		it->second += newValue;
	}
	else
	{
		clientBalanceMap.insert(std::pair<int, int>(clientId, newValue));
	}
}


int CBank::GetClientCount()
{
	return m_clients.size();
}

HANDLE * CBank::GetClientHandles()
{
	std::vector<HANDLE> handles;
	for (auto &client : m_clients)
	{
		handles.push_back(client.m_handle);
	}
	return handles.data();
}

int CBank::GetClientBalance(int clientId)
{
	auto it = clientBalanceMap.find(clientId);
	return it->second;
}

std::vector<CBankClient> CBank::GetAllClients()
{
	return m_clients;
}