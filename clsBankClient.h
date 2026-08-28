#pragma once
#include <iostream>
#include "clsPerson.h"
using namespace std;


class clsBankClient : clsPerson
{
private:
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
		this->_PinCode;
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

	bool IsEmpty()
	{
		return (this->_Mode == enMode::EmptyMode);
	}
};
