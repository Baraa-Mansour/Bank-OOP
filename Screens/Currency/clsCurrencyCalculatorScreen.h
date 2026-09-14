#pragma once
#include <iostream>

#include "../../Libs/clsInputValidate.h"

#include "../../Core/clsCurrency.h"

#include "../clsScreen.h"


class clsCurrencyCalculatorScreen :protected clsScreen

{
private:

    static double _ReadAmount()
    {
        double NewRate = 0;

        NewRate = clsInputValidate::ReadNumberBetween<double>(0, std::numeric_limits<double>::max(), "\nEnter Amount: ", "Enter Positive Number !");
        return NewRate;
    }

    static string _ReadExistCurrencyCode(string Message)
    {
        string CurrencyCode = "";

        CurrencyCode = clsInputValidate::ReadString(Message);

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            CurrencyCode = clsInputValidate::ReadString("\nCurrency is not found, choose another one: ");
        }

        return CurrencyCode;
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode = _ReadExistCurrencyCode(Message);

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country;
        cout << "\nCode          : " << Currency.CurrencyCode;
        cout << "\nName          : " << Currency.CurrencyName;
        cout << "\nRate(1$) =    : " << Currency.Rate;
        cout << "\n_____________________________\n\n";
    }

    static void _PrintCalculationsResults(double Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");

        double AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        double AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode;
    }

public:

    static void ShowCurrencyCalculatorScreen()
    {
        do
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            double Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
        } while (clsInputValidate::ReadYorN("\n\nDo you want to perform another calculation? y/n ? "));

        Pause("Enter Any Key To Back To Currncies Exchange Menu ...");
    }
};
