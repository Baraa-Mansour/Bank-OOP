#pragma once
#include <iostream>

#include "../../Libs/clsInputValidate.h"

#include "../../Core/clsCurrency.h"

#include "../clsScreen.h"


class clsUpdateCurrencyRateScreen : public clsScreen

{
private:

    static double _ReadRate()
    {
        double NewRate = 0;

        NewRate = clsInputValidate::ReadNumberBetween<double>(0, std::numeric_limits<double>::max(), "\nEnter New Rate: ", "Enter Positive Number !");
        return NewRate;
    }

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

    static string _ReadExistCurrencyCode()
    {
        string CurrencyCode = "";

        CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            CurrencyCode = clsInputValidate::ReadString("\nCurrency is not found, choose another one: ");
        }

        return CurrencyCode;
    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = _ReadExistCurrencyCode();

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);


        if (clsInputValidate::ReadYorN("\nAre you sure you want to update the rate of this Currency y/n? "))
        {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }

        Pause("Enter Any Key To Back To Currncies Exchange Menu ...");
    }
};
