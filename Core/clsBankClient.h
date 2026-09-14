#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Core/clsPerson.h"

#include "Libs/clsString.h"
#include "Libs/clsFile.h"
#include "Libs/clsDate.h"


using namespace std;


class clsBankClient : public clsPerson
{
public:
	struct stTransferLog
	{
		string UserName = "";
		string DateTime = "";
		double Amount = 0;
		string SrcAccountNumber = "";
		string DestAccountNumber = "";
		double SrcBalance = 0;
		double DestBalance = 0;
	};
private:
	
	static const string _ClientsFilePath;
	static const string _TransferLogPath;
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

	static string _ConvertTransferLogObjectToString(stTransferLog TransferLog, string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += TransferLog.DateTime + Seperator;
		TransferLogRecord += TransferLog.SrcAccountNumber + Seperator;
		TransferLogRecord += TransferLog.DestAccountNumber + Seperator;
		TransferLogRecord += to_string(TransferLog.Amount) + Seperator;
		TransferLogRecord += to_string(TransferLog.SrcBalance) + Seperator;
		TransferLogRecord += to_string(TransferLog.DestBalance) + Seperator;
		TransferLogRecord += TransferLog.UserName;
		return TransferLogRecord;
	}
	static stTransferLog _ConvertLineToTransferLog(string Line, string Seperator = "#//#")
	{
		stTransferLog TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SrcAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.SrcBalance = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.DestBalance = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
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
	static void _SaveTransferLogToFile(stTransferLog TransferLog)
	{
		string stDataLine = _ConvertTransferLogObjectToString(TransferLog);
		clsFile::SaveLine(stDataLine, _TransferLogPath);
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
			return enSaveResults::svFaildEmptyObject;
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
		if (Amount > this->Balance || Amount < 0)
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

	void RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
	{
		stTransferLog TransferLog;
		TransferLog.DateTime = clsDate::GetSystemDateTimeString();
		TransferLog.SrcAccountNumber = this->AccountNumber;
		TransferLog.DestAccountNumber = DestinationClient.AccountNumber;
		TransferLog.Amount = Amount ;
		TransferLog.SrcBalance = this->Balance;
		TransferLog.DestBalance = DestinationClient.Balance;
		TransferLog.UserName = UserName;

		clsBankClient::_SaveTransferLogToFile(TransferLog);
	}

	static vector<stTransferLog> GetAllTransfersLogs()
	{
		vector<string> vLines = clsFile::GetAllLines(_TransferLogPath);
		vector<stTransferLog> Logs;

		for (string& Line : vLines)
		{
			stTransferLog Log = _ConvertLineToTransferLog(Line);

			Logs.push_back(Log);
		}

		return Logs;
	}
};
const string clsBankClient::_ClientsFilePath = "Data\\Clients.txt";
const string clsBankClient::_TransferLogPath = "Data\\TransferLog.txt";