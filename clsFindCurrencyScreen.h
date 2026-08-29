#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : public clsScreen
{
private:
	enum enFindBy
	{
		CODE = 1,
		COUNTRY = 2
	};

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country;
		cout << "\nCode       : " << Currency.CurrencyCode;
		cout << "\nName       : " << Currency.CurrencyName;
		cout << "\nRate(1$) = : " << Currency.Rate;

		cout << "\n_____________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		enFindBy Option = (enFindBy)clsInputValidate::ReadIntNumberBetween(1, 2, "Find By: [1]Code [2]Country: ", "");
		
		clsCurrency Currency;
		string Name = "";

		switch (Option)
		{
		case clsFindCurrencyScreen::CODE:
			Name = clsInputValidate::ReadString("Enter Code: ");
			Currency = clsCurrency::FindByCode(Name);
			break;

		case clsFindCurrencyScreen::COUNTRY:
			Name = clsInputValidate::ReadString("Enter Country: ");
			Currency = clsCurrency::FindByCountry(Name);
			break;

		default:
			break;
		}

		_ShowResults(Currency);

		Pause("Enter Any Key To Back To Currncies Exchange Menu ...");
	}
};
