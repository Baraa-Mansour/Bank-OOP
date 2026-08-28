#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{

public:
	static string ReadString(string InputMessage = "Enter String :")
	{
		string Value = "";

		cout << InputMessage;
		getline(cin >> ws, Value);

		return Value;
	}

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	static int ReadIntNumber(string InputMessage = "Enter Integer Number :", string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		cout << InputMessage;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To,
		string InputMessage = "Enter Integer Number In Range :", string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber(InputMessage);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber(InputMessage);
		}
		return Number;
	}

	static double ReadDblNumber(string InputMessage = "Enter Double Number :", string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		cout << InputMessage;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To,
		string InputMessage = "Enter Double Number In Range :", string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber(InputMessage);

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber(InputMessage);
		}
		return Number;
	}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static bool ReadYorN(string Message)
	{
		char Choice = 'y';
		do
		{
			cout << Message;
			cin >> Choice;
		} while (tolower(Choice) != 'y' && tolower(Choice) != 'n');

		return tolower(Choice) == 'y';
	}
};

