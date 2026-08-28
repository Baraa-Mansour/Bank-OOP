#pragma once
#include <iostream>
#include "clsPerson.h"
using namespace std;


class clsBankClient : clsPerson
{
private:
	const string ClientsFilePath = "Clients.txt";
	enum enMode 
	{ 
		EmptyMode = 0,
		UpdateMode = 1
	};

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enMode _Mode;

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double Balance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_Balance = Balance;

		this->_Mode = Mode;
	}
public:

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
	__declspec(property(put = SetBalance, get = GetBalance)) string Balance;

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << AccountNumber;
		cout << "\nPassword    : " << PinCode;
		cout << "\nBalance     : " << Balance;
		cout << "\n___________________\n";
	}

	bool IsEmpty()
	{
		return (this->_Mode == enMode::EmptyMode);
	}
};