#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsFile.h"
using namespace std;


class clsBankClient : public clsPerson
{
private:
	static const string _ClientsFilePath;
	enum enMode 
	{ 
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enMode _Mode;
	bool _MarkedForDelete = false;

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double Balance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_Balance = Balance;

		this->_Mode = Mode;
	}

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}
	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.Balance);

		return stClientRecord;
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveClientToFile(clsBankClient Client)
	{
		string Line = _ConverClientObjectToLine(Client);

		clsFile::SaveLine(Line, _ClientsFilePath);
	}
	static void _SaveClientsVectorToFile(vector<clsBankClient> vClients)
	{
		vector<string> vLines;
		string Line = "";

		for (const clsBankClient& Client : vClients)
		{
			if (!Client._MarkedForDelete)
			{
				Line = _ConverClientObjectToLine(Client);
				vLines.push_back(Line);
			}
		}

		clsFile::SaveLineVector(vLines, _ClientsFilePath);
	}

	void _Update()
	{
		bool IsFound = false;

		vector<clsBankClient> vClients = GetAllClients();

		for (clsBankClient& Client : vClients)
		{
			if (this->AccountNumber == Client.AccountNumber)
			{
				Client = *this;
				IsFound = true;
				break;
			}
		}

		if (IsFound)
		{
			_SaveClientsVectorToFile(vClients);
		}
	}
	void _AddNew()
	{
		_SaveClientToFile(*this);
	}

public:
	enum enSaveResults
	{
		svFaildEmptyObject = 0,
		svSucceeded = 1,
		svFaildAccountNumberExists = 2
	};

	// Properties
	string GetAccountNumber()
	{
		return this->_AccountNumber;
	}
	__declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode(string PinCode)
	{
		this->_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return this->_PinCode;
	}
	__declspec(property(put = SetPinCode, get = GetPinCode)) string PinCode;

	void SetBalance(double Balance)
	{
		this->_Balance = Balance;
	}
	double GetBalance()
	{
		return this->_Balance;
	}
	__declspec(property(put = SetBalance, get = GetBalance)) double Balance;
	// ---------------

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> GetAllClients()
	{
		vector<clsBankClient> vClients;
		vector<string> vLines = clsFile::GetAllLines(_ClientsFilePath);

		for (string& Line : vLines)
		{
			clsBankClient Client = _ConvertLinetoClientObject(Line);
			vClients.push_back(Client);
		}

		return vClients;
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetAllClients();
		double Sum = 0;

		for (clsBankClient& Client : vClients)
		{
			Sum += Client.Balance;
		}

		return Sum;
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream File;
		File.open(_ClientsFilePath, ios::in);

		if (File.is_open())
		{
			string Line = "";
			while (getline(File, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber == AccountNumber)
				{
					File.close();
					return Client;
				}
			}
			File.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		clsBankClient Client = Find(AccountNumber);

		if (Client.IsEmpty())
		{
			return Client;
		}

		return Client.PinCode == PinCode ? Client : _GetEmptyClientObject();
	}

	enSaveResults Save()
	{
		switch (this->_Mode)
		{
		case enMode::UpdateMode:
			this->_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(this->AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;

			this->_AddNew();
			this->_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
		default:
			break;
		}
	}

	bool Delete()
	{
		bool IsFound = false;

		vector<clsBankClient> vClients = GetAllClients();

		for (clsBankClient& Client : vClients)
		{
			if (this->AccountNumber == Client.AccountNumber)
			{
				IsFound = true;

				Client._MarkedForDelete = true;
				break;
			}
		}

		if (IsFound)
		{
			_SaveClientsVectorToFile(vClients);
			*this = _GetEmptyClientObject();
		}

		return IsFound;
	}

	static bool IsClientExist(string AccountNumber)
	{
		return !(clsBankClient::Find(AccountNumber).IsEmpty());
	}

	bool IsEmpty()
	{
		return (this->_Mode == enMode::EmptyMode);
	}

	bool Deposit(double Amount)
	{
		if (Amount <= 0)
		{
			return false;
		}

		Balance += Amount;
		this->Save();

		return true;
	}

	bool Withdraw(double Amount)
	{
		if (Amount > this->Balance)
		{
			return false;
		}

		Balance -= Amount;
		this->Save();

		return true;
	}

	bool Transfer(double Amount, clsBankClient& ToClient)
	{
		if (!this->Withdraw(Amount))
			return false;
		if (!ToClient.Deposit(Amount))
			return false;
		return true;
	}
};
const string clsBankClient::_ClientsFilePath = "Clients.txt";