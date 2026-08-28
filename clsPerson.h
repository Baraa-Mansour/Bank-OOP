#pragma once
#include <iostream>
using namespace std;


class clsPerson
{
private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		this->_FirstName = FirstName;
		this->_LastName = LastName;
		this->_Email = Email;
		this->_Phone = Phone;
	}

	void SetFirstName(string FirstNmae)
	{
		this->_FirstName = FirstNmae;
	}
	string GetFirstName()
	{
		return this->_FirstName;
	}
	__declspec(property(put = SetFirstName, get = GetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		this->_LastName = LastName;
	}
	string GetLastName()
	{
		return this->_LastName;
	}
	__declspec(property(put = SetLastName, get = GetLastName)) string LastName;

	void SetEmail(string Email)
	{
		this->_Email = Email;
	}
	string GetEmail()
	{
		return this->_Email;
	}
	__declspec(property(put = SetEmail, get = GetEmail)) string Email;

	void SetPhone(string Phone)
	{
		this->_Phone = Phone;
	}
	string GetPhone(string Phone)
	{
		return this->_Phone;
	}
	__declspec(property(put = SetPhone, get = GetPhone)) string Phone;
};
