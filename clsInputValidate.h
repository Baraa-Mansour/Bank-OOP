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

	template<typename T>
	static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	template<typename T>
	static T ReadNumber(string InputMessage = "Enter Number :", string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		cout << InputMessage;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	template<typename T>
	static T ReadNumberBetween(T From, T To,
		string InputMessage = "Enter Number In Range :", string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber<T>(InputMessage);

		while (!IsNumberBetween<T>(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>(InputMessage);
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
};

