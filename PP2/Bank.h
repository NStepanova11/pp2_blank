#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "KeyType.h"
#include "BankClient.h"

class CBank
{
public:
	CBank(KeyTypes keyType);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	int GetTotalBalance();
	int GetClientCount();
	HANDLE * GetClientHandles();

	//for client balance
	void SetClientBalance(int clientId, int newValue);
	int GetClientBalance(int clientId);
	std::vector<CBankClient> GetAllClients();

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	void SetTotalBalance(int value);
	void SomeLongOperations();

	//for synchronization
	CRITICAL_SECTION m_criticalSection;
	std::mutex m_mutex;
	void ActivateSynchronization();
	void DeactivateSynchronization();
	KeyTypes m_keyType;

	//for client balance
	std::map<int, int> clientBalanceMap;

};